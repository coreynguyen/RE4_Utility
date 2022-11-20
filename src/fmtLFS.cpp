#include "fmtLFS.h"


HMODULE XCompressHandle = NULL;

XMemCreateCompressionContext_fn* XMemCreateCompressionContext = nullptr;
XMemDestroyCompressionContext_fn* XMemDestroyCompressionContext = nullptr;
XMemCompress_fn* XMemCompress = nullptr;

XMemCreateDecompressionContext_fn* XMemCreateDecompressionContext = nullptr;
XMemDestroyDecompressionContext_fn* XMemDestroyDecompressionContext = nullptr;
XMemDecompress_fn* XMemDecompress = nullptr;


inline bool ends_with(std::string const& value, std::string const& ending) {
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
	}

int LFSDecompress(FILE* in_file, FILE* out_file) {

    XMEMDECOMPRESSION_CONTEXT ctx = NULL;
    HRESULT ret = XMemCreateDecompressionContext(XMEMCODEC_DEFAULT, NULL, 0, &ctx);
    printf("\nDecompressing input file...\n");
    if (ret != S_OK) {
        printf("Error: failed to create decompression context?\n");
        return 1;
		}

    _fseeki64(in_file, 0, SEEK_END);
    uint64_t file_size = ftell(in_file);
    _fseeki64(in_file, 0, SEEK_SET);

    printf("Input file length: 0x%llX\n", file_size);

    auto data_in = std::make_unique<uint8_t[]>(file_size);
    fread(data_in.get(), 1, file_size, in_file);
    fclose(in_file);

    LFSHeader* header = (LFSHeader*)data_in.get();
    LFSChunk* chunks = (LFSChunk*)&header[1];

    if (header->Magic1 != 0x584C4452) { // game only checks Magic1, so guess we'll do the same
        printf("Error: LFS uses invalid Magic1 0x%X (expected 0x584C4452), aborting.\n", header->Magic1);
        return 1;
		}

    printf("LFS chunk count: %d\n", header->NumChunks);
    printf("Writing out decompressed file...\n");


    char* buf[LFS_CHUNK_SIZE];

    auto dec_buf = std::make_unique<uint8_t[]>(LFS_CHUNK_SIZE);
    for (uint32_t i = 0; i < header->NumChunks; i++) {
        LFSChunk* chunk = &chunks[i];

        uint8_t* comp_data = (uint8_t*)chunks + (chunk->Offset & ~1); // & with ~1 to remove any 1/compressed bit
        long unsigned int comp_data_size = LFS_CHUNK_SIZE;
        if (chunk->SizeCompressed > 0) {
			comp_data_size = chunk->SizeCompressed;
			}

        long unsigned int expected_size = LFS_CHUNK_SIZE;
        if (chunk->SizeDecompressed > 0) {
			expected_size = chunk->SizeDecompressed;
			}

        long unsigned int output_size = LFS_CHUNK_SIZE;

        if ((chunk->Offset & 1) != 0) {
            // compressed bit is set, run XMemDecompress


//    __in    XMEMDECOMPRESSION_CONTEXT       Context,
//    __out_bcount( *pDestSize ) VOID*        pDestination,
//    __inout SIZE_T*                         pDestSize,
//    __in_bcount( SrcSize) CONST VOID*       pSource,
//    __in    SIZE_T                          SrcSize


            ret = XMemDecompress(ctx, &buf, &output_size, comp_data, comp_data_size);
            if (ret != S_OK) {
                printf("Error: chunk %d failed to decompress data, output file is incomplete!\n", i);
                //return 1;
				}
            if (output_size != expected_size) {
                printf("Error: chunk %d failed to fully decompress data (got 0x%llX bytes, expected 0x%llX), output file is incomplete!\n", i, (unsigned long long)output_size, (unsigned long long)expected_size);
                //return 1;
				}
            fwrite(buf, 1, output_size, out_file);
			}
        else {
            // compressed bit not set, copy bytes to new file
            fwrite(comp_data, 1, comp_data_size, out_file);
			}
		}
    fclose(out_file);

    XMemDestroyDecompressionContext(ctx);

    printf("\nLFS decompression complete, have a nice day!\n");
    return 0;
	}

int LFSCompress(FILE* in_file, FILE* out_file) {
    printf("\nCompressing input file...\n");

    XMEMCOMPRESSION_CONTEXT ctx;
    auto ret = XMemCreateCompressionContext(1, 0, 0, &ctx);
    if (ret < 0) {
        printf("Error: failed to create compression context?\n");
        return 1;
		}

    _fseeki64(in_file, 0, SEEK_END);
    uint64_t file_size = ftell(in_file);
    _fseeki64(in_file, 0, SEEK_SET);

    printf("Input file length: 0x%llX\n", file_size);

    int num_chunks = (file_size + (LFS_CHUNK_SIZE - 1)) / LFS_CHUNK_SIZE;
    printf("LFS chunk count: %d\n", num_chunks);

    int header_size = sizeof(LFSHeader) + (sizeof(LFSChunk) * num_chunks);

    LFSHeader header;
    auto chunks = std::make_unique<LFSChunk[]>(num_chunks);

    header.Magic1 = 0x584C4452;
    header.Magic2 = 0xFEEEBAAA;
    header.NumChunks = num_chunks;
    header.SizeDecompressed = (uint32_t)file_size;
    header.SizeCompressed = 0;

    printf("Writing out compressed LFS...\n");

    auto dec_buf = std::make_unique<uint8_t[]>(LFS_CHUNK_SIZE);
    auto comp_buf = std::make_unique<uint8_t[]>(LFS_CHUNK_SIZE);

    uint64_t data_offset = header_size;
    uint64_t data_remaining = file_size;
    for (int i = 0; i < num_chunks; i++) {
        uint64_t chunk_size = LFS_CHUNK_SIZE;
        if (chunk_size > data_remaining) {
			chunk_size = data_remaining;
			}

        LFSChunk* chunk = &chunks[i];

        fread(dec_buf.get(), 1, chunk_size, in_file);

        SIZE_T output_size = LFS_CHUNK_SIZE;
        ret = XMemCompress(ctx, comp_buf.get(), &output_size, dec_buf.get(), chunk_size);
        if (ret < 0) {
            printf("Error: failed to compress data, output file is incomplete!\n");
            return 1;
			}

        uint64_t data_offset_aligned = ((((data_offset - 4) + 0xF) / 0x10) * 0x10) + 4; // weird ass alignment based on offset being -4 of actual offset?
        _fseeki64(out_file, data_offset_aligned, SEEK_SET);
        fwrite(comp_buf.get(), 1, output_size, out_file);

        chunk->SizeDecompressed = chunk_size == LFS_CHUNK_SIZE ? 0 : chunk_size;
        chunk->SizeCompressed = output_size == LFS_CHUNK_SIZE ? 0 : output_size;

        chunk->Offset = (data_offset_aligned - 0x14);
        chunk->Offset |= 1; // set compressed bit - game won't bother with XMemDecompress if this isn't set!

        header.SizeCompressed += (uint32_t)output_size;

        data_offset = data_offset_aligned + output_size;
        data_remaining -= chunk_size;
		}

    fclose(in_file);

    XMemDestroyCompressionContext(ctx);

    // Write headers and finish up
    _fseeki64(out_file, 0, SEEK_SET);
    fwrite(&header, sizeof(LFSHeader), 1, out_file);
    fwrite(chunks.get(), sizeof(LFSChunk), num_chunks, out_file);
    fclose(out_file);

    printf("\nLFS compression complete, have a nice day!\n");
    return 0;
	}

int LFSDecompressFile(std::string fileIn, std::string fileOut) {
	FILE* in_file;
	if (fopen_s(&in_file, fileIn.c_str(), "rb") == 0) {
		FILE* out_file;
		if (fopen_s(&out_file, fileOut.c_str(), "wb+") == 0) {
			XCompressHandle = LoadLibrary(L"xcompress32.dll");
			if (XCompressHandle != 0) {
				XMemCreateCompressionContext = (XMemCreateCompressionContext_fn*)GetProcAddress(XCompressHandle, "XMemCreateCompressionContext");
				XMemDestroyCompressionContext = (XMemDestroyCompressionContext_fn*)GetProcAddress(XCompressHandle, "XMemDestroyCompressionContext");
				XMemCompress = (XMemCompress_fn*)GetProcAddress(XCompressHandle, "XMemCompress");
				XMemCreateDecompressionContext = (XMemCreateDecompressionContext_fn*)GetProcAddress(XCompressHandle, "XMemCreateDecompressionContext");
				XMemDestroyDecompressionContext = (XMemDestroyDecompressionContext_fn*)GetProcAddress(XCompressHandle, "XMemDestroyDecompressionContext");
				XMemDecompress = (XMemDecompress_fn*)GetProcAddress(XCompressHandle, "XMemDecompress");
				if (LFSDecompress(in_file, out_file) != 0) {
					std::cout << "Error: failed decompress lfs file!\n"; return 4;
					}
				} else {std::cout << "Error: failed to load xcompress64.dll library! \t" << GetLastError() << std::endl; return 3;}
			} else {std::cout << "Error: failed to open output file for writing!\n"; return 2;}
		} else {std::cout << "Error: failed to open input file for reading!\n"; return 1;}
	return 0;
	}

