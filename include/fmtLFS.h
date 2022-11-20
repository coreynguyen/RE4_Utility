#ifndef FMTLFS_H
#define FMTLFS_H


#include <iostream>
#include <memory>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
//#include "xcompress.h"


typedef VOID* XMEMDECOMPRESSION_CONTEXT;

typedef enum _XMEMCODEC_TYPE {
    XMEMCODEC_DEFAULT =             0,
    XMEMCODEC_LZX =                 1
    } XMEMCODEC_TYPE;

typedef struct _XMEMCODEC_PARAMETERS_LZX {
    DWORD Flags;
    DWORD WindowSize;
    DWORD CompressionPartitionSize;
    } XMEMCODEC_PARAMETERS_LZX;

//HRESULT WINAPI XMemCreateDecompressionContext(
//    XMEMCODEC_TYPE                  CodecType,
//    CONST VOID*                     pCodecParams,
//    DWORD                           Flags,
//    XMEMDECOMPRESSION_CONTEXT*      pContext
//    );
//
//HRESULT WINAPI XMemDecompress(
//    XMEMDECOMPRESSION_CONTEXT       Context,
//    VOID*                           pDestination,
//    SIZE_T*                         pDestSize,
//    CONST VOID*                     pSource,
//    SIZE_T                          SrcSize
//    );
//
//HRESULT WINAPI XMemDecompressSegmentTD(
//    XMEMDECOMPRESSION_CONTEXT       Context,
//    VOID*                           pDestination,
//    SIZE_T*                         pDestSize,
//    CONST VOID*                     pSource,
//    SIZE_T                          SrcSize,
//    SIZE_T                          DestSize,
//    SIZE_T                          Offset
//    );
//
//VOID WINAPI XMemDestroyDecompressionContext(
//    XMEMDECOMPRESSION_CONTEXT       Context
//    );


typedef VOID* XMEMCOMPRESSION_CONTEXT;
typedef VOID* XMEMDECOMPRESSION_CONTEXT;

using XMemCreateCompressionContext_fn = DWORD(int CodecType, const void* pCodecParams, DWORD Flags, XMEMCOMPRESSION_CONTEXT* pContext);
using XMemDestroyCompressionContext_fn = void(XMEMCOMPRESSION_CONTEXT Context);
using XMemCompress_fn = DWORD(XMEMCOMPRESSION_CONTEXT Context, void* pDestination, SIZE_T* pDestSize, const void* pSource, SIZE_T SrcSize);

using XMemCreateDecompressionContext_fn = DWORD(int CodecType, const void* pCodecParams, DWORD Flags, XMEMDECOMPRESSION_CONTEXT* pContext);
using XMemDestroyDecompressionContext_fn = void(XMEMDECOMPRESSION_CONTEXT Context);
using XMemDecompress_fn = DWORD(XMEMDECOMPRESSION_CONTEXT Context, void* pDestination, SIZE_T* pDestSize, const void* pSource, SIZE_T SrcSize);

extern HMODULE XCompressHandle;

extern XMemCreateCompressionContext_fn* XMemCreateCompressionContext;
extern XMemDestroyCompressionContext_fn* XMemDestroyCompressionContext;
extern XMemCompress_fn* XMemCompress;

extern XMemCreateDecompressionContext_fn* XMemCreateDecompressionContext;
extern XMemDestroyDecompressionContext_fn* XMemDestroyDecompressionContext;
extern XMemDecompress_fn* XMemDecompress;


struct LFSHeader {
    uint32_t Magic1;
    uint32_t Magic2;
    uint32_t SizeDecompressed;
    uint32_t SizeCompressed;
    uint32_t NumChunks;
	};

struct LFSChunk {
    uint16_t SizeCompressed;
    uint16_t SizeDecompressed;
    uint32_t Offset;
	};

const int LFS_CHUNK_SIZE = 0x10000; // size of each decompressed chunk

void usage();

int LFSCompress(FILE* in_file, FILE* out_file);
int LFSDecompress(FILE* in_file, FILE* out_file);
int LFSDecompressFile(std::string fileIn, std::string fileOut);


#endif // FMTLFS_H
