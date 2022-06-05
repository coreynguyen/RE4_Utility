#ifndef FMTFBX_H
#define FMTFBX_H

#include <iostream>
#include <cstdint>		// needed for types such as uint8_t, uint16_t, uint32_t
#include <sstream>
#include <string>
#include <vector>

#include "bytestream.h"
#include "stringext.h"
#include "filesystem.h"


/*


need to write empty scenes, that are compliant for each version


-models

1.) add an entry to the connections list
2.) update counts int Definitions
3.) store mesh data in Objects

-textures

are stored in the media block as a video lol



?
Seems fbx does not supports splines so i'll need to use obj for that lol
im not even sure if it supports vertex colors, probably 3dsmax hacks it
and stores them to the UV channels, since they state that they reserve
channel0 for colors.

what it does show as supported is
- geometry
- animation
- morphs
- skin (weights)

clearly it is an asset for animation, really sucks

need to test vertex colours and the material systems


 * I should create a complex scene in the oldest version of 3dsmax
   then I can carry it through a newer max and see how they re-organize
   the data. since so far the fbx format seems all over the place

	actually its so shit it makes blenders blend format look god tier

 - Mesh
 - Materials
 - Textures
 - Cameras
 - Lights
 - Animations
 - Bones
 - Parented Meshes
 - Vertex Colors
 - weird transforms
 - Morphs
 - Different Objects (Mesh, Poly, Shape)


*/

struct fmtFBX_Video {
	std::string Name;
	std::string Type;
	std::string Filename;
	std::string RelativeFilename;
	bytestream Content;
	fmtFBX_Video () {
		Type = "Clip";
		}
	};

struct fmtFBX_Media {
	bool hasVideo;
	std::vector<fmtFBX_Video> Video;
	};

struct fmtFBX_Limits {
	int32_t TAuto;
	int32_t RAuto;
	int32_t SAuto;
	fmtFBX_Limits () {
		TAuto = 1;
		RAuto = 1;
		SAuto = 1;
		}
	};

struct fmtFBX_Layer {
	int32_t Version;
	std::string Hidden;
	int32_t MultiLayer;
	int32_t MultiTake;
	char Shading;
	std::string Culling;
	bool hasLimits;
	fmtFBX_Limits Limits;
	// insert dummy

	fmtFBX_AnimatedProperty AnimatedProperty;
	fmtFBX_Animated Animated;

	fmtFBX_Layer () {
		Version = 194;
		Hidden = "True";
		MultiLayer = 0;
		MultiTake = 1;
		Shading = 'W';
		Culling = "CullingOff";
		hasLimits = true;
		}
	};

struct fmtFBX_Switcher {
	Layer fmtFBX_Layer;
	std::string AnimationMode;
	uint32_t Version;
	std::string Name;
	uint32_t CameraId;
	uint32_t CameraName;
	std::string CameraIndexName;

	fmtFBX_Switcher () {
		AnimationMode = "Global";
		Version = 100;
		Name = "Camera Switcher";
		CameraId = 1;
		CameraName = 100;
		CameraIndexName = "Camera01";

		}
	};

struct fmtFBX_Take {
	std::string Name;
	std::string FileName;
	int64_t LocalTime[2];
	int64_t ReferenceTime[2];
	fmtFBX_Take () {
		Name = "Take 001";
		FileName = "Take_001.tak";
		LocalTime[0] = 0;
		LocalTime[1] = 0x00000AC0E8D7B04C;
		ReferenceTime[0] = 0;
		ReferenceTime[1] = 0x00000AC0E8D7B04C;
		}
	};

struct fmtFBX_Takes {
	std::string Current;
	fmtFBX_Takes () {
		Current = "Take 001";
		fmtFBX_Take Take;
		}
	};

struct fmtFBX_MetaData {
	int32_t Version;
	std::string Title;
	std::string Subject;
	std::string Author;
	std::string Keywords;
	std::string Revision;
	std::string Comment;
	fmtFBX_MetaData () {
		Version = 100;
		Title = "";
		Subject = "";
		Author = "";
		Keywords = "";
		Revision = "";
		Comment = "";
		}
	};

struct fmtFBX_Properties60_Value {
	/*
		they have Property70 which in turns users the 50 style
		of defining a byte as a type rather then a full on string

		i'm just gonna hack this to do both 50, 60, 70 whatever
		properties

		if anything I now know the names of all the type codes
	*/
	std::string DataType;       // used on 60, c style names, such as double, int, bool, etc
	std::string DataName;       // used on 70, like a fuller naming of the type lol

	bool        valBool;        // bool     |
	double      valVector3D[3]; //
	double      valDouble;      // double   |   Number
	uint32_t    valEnum;
	int32_t     valInt;         // int      |   Integer
	double      valColor[3];    // ColorRGB |   Color
	float       valReal;
	time_t      valKTime;       // KTime    |   Time
	std::string valKString;     // KString  |   Url
	std::string valDateTime;    // DateTime |
	fmtFBX_Properties60_Value (std::string d = "KString", std::string v = "") {
		DataType = d;
		valKString = v;
		}
	};

struct fmtFBX_Properties60 {
	std::string Variable;
	std::vector<fmtFBX_Properties60_Value> Value;
	fmtFBX_Properties60 (std::string n = "", fmtFBX_Properties60_Value v = fmtFBX_Properties60_Value()) {
		Variable = "";
		}
	};


struct fmtFBX_Channel_Property_Value {
	std::string Name;
	double Default;
	fmtFBX_Channel_Property_Value () {
		Name = "";
		Default = 0.0f;
		}
	};

struct fmtFBX_Channel_Property {
	std::string Name;
	fmtFBX_Channel_Property_Value Value;
	fmtFBX_Channel_Property () {
		Name = "";
		}
	};

struct fmtFBX_Channel {
	/*
		they seem to have 3 major versions of expressing generic properties
		Channel
		Properties60
		Properties70

		all they do is define generic variables
	*/
	std::string Name;
	std::vector<fmtFBX_Channel_Property> Property;
	int32_t LayerType;
	};


struct fmtFBX_SceneInfo {
	std::string Type;
	int32_t Version;
	fmtFBX_MetaData MetaData;
	std::vector<fmtFBX_Properties60> Property;
	fmtFBX_SceneInfo () {
		Type = "UserData";
		Version = 100;
		Property = std::vector<fmtFBX_Properties60>(14);
		Property.at( 0) = fmtFBX_Properties60("DocumentUrl", fmtFBX_Properties60_Value("file.fbx"));
		Property.at( 1) = fmtFBX_Properties60("SrcDocumentUrl", fmtFBX_Properties60_Value("file.fbx"));
		Property.at( 2) = fmtFBX_Properties60("Original");
		Property.at( 3) = fmtFBX_Properties60("Original|ApplicationVendor", fmtFBX_Properties60_Value("Autodesk"));
		Property.at( 4) = fmtFBX_Properties60("Original|ApplicationName", fmtFBX_Properties60_Value("3ds Max"));
		Property.at( 5) = fmtFBX_Properties60("Original|ApplicationVersion", fmtFBX_Properties60_Value("2009.0"));
		Property.at( 6) = fmtFBX_Properties60("Original|DateTime_GMTS", fmtFBX_Properties60_Value("23/05/2022 21:28:30.261"));
		Property.at( 7) = fmtFBX_Properties60("Original|FileNameS", fmtFBX_Properties60_Value("file.fbx"));
		Property.at( 8) = fmtFBX_Properties60("LastSaved");
		Property.at( 9) = fmtFBX_Properties60("LastSaved|ApplicationVendor", fmtFBX_Properties60_Value("Autodesk"));
		Property.at(10) = fmtFBX_Properties60("LastSaved|ApplicationName", fmtFBX_Properties60_Value("3ds Max"));
		Property.at(11) = fmtFBX_Properties60("LastSaved|ApplicationVersion", fmtFBX_Properties60_Value("2009.0"));
		Property.at(12) = fmtFBX_Properties60("LastSaved|DateTime_GMTS", fmtFBX_Properties60_Value("23/05/2022 21:28:30.261"));
		Property.at(13) = fmtFBX_Properties60("Original|ApplicationActiveProject", fmtFBX_Properties60_Value("Documents"));


		}
	};

struct fmtFBX_SceneGenericPersistence {
	std::string Name;
	fmtFBX_SceneInfo SceneInfo;
	fmtFBX_SceneGenericPersistence () {
		Name = "GlobalInfo";
		}
	};

struct fmtFBX_AmbientRenderSettings {
	uint32_t Version;
	double AmbientLightColor[4];
	fmtFBX_AmbientRenderSettings () {
		Version = 101;
		AmbientLightColor[0] = 0.0f;
		AmbientLightColor[1] = 0.0f;
		AmbientLightColor[2] = 0.0f;
		AmbientLightColor[3] = 1.0f;
		}
	};

struct fmtFBX_FogOptions {
	uint32_t FlogEnable;
	uint32_t FogMode;
	double FogDensity;
    double FogStart;
    double FogEnd;
    double FogColor[4];
    fmtFBX_FogOptions () {
		FlogEnable = 0;
		FogMode = 0;
		FogDensity = 0.002f;
		FogStart = 0.3f;
		FogEnd = 1000;
		FogColor[0] = 1.0f;
		FogColor[1] = 1.0f;
		FogColor[2] = 1.0f;
		FogColor[3] = 1.0f;
		}
	};

struct fmtFBX_RendererSetting {
	std::string DefaultCamera;
	uint32_t DefaultViewingMode;
	fmtFBX_RendererSetting () {
		DefaultCamera = "Producer Perspective";
		DefaultViewingMode = 0;
		}
	};

struct fmtFBX_Antialiasing {
	int32_t AntialiasingMethod;
	int32_t SamplingType;
	double FocusDistanceSource;
	fmtFBX_Antialiasing () {
		AntialiasingMethod = 0;
		SamplingType = 0;
		FocusDistanceSource = 0.77777;
		}
	};

struct fmtFBX_DepthOfField {
	int32_t UseRealTimeDOFAndAA;
	int32_t KFbxTypedProperty;
	double FocusAngle;
	double FocusDistance;

	fmtFBX_DepthOfField () {
		UseRealTimeDOFAndAA = 0;
		KFbxTypedProperty = 0;
		FocusAngle = 3.5;
		FocusDistance = 200;
		}

	};

struct fmtFBX_CameraAndLens {
	fmtFBX_DepthOfField DepthOfField;
	fmtFBX_Antialiasing Antialiasing;
	int32_t OverSampling[3];
	int32_t UseOverSamplingTime;
	fmtFBX_CameraAndLens () {
		OverSampling[0] = 7;
		OverSampling[1] = 1;
		OverSampling[2] = 0;
		UseOverSamplingTime = 77;
		}
	};

struct fmtFBX_AnimatedProperty {
	bool AnimatedProperty;
	bool mTranslationProperty;
	bool mRotationProperty;
	bool mScalingProperty;
	fmtFBX_AnimatedProperty () {
		AnimatedProperty = true;
		mTranslationProperty = true;
		mRotationProperty = true;
		mScalingProperty = true;
		}
	};

struct fmtFBX_Animated {
	bool Translation;
	bool Rotation;
	bool Scaling;
	fmtFBX_Animated () {
		Translation = true;
		Rotation = true;
		Scaling = true;
		}
	};

struct fmtFBX_Camera {
	fmtFBX_Layer Layer;
	// insert dummy
	std::string Camera;
	std::string TypeFlags;
	int32_t Version;
	std::string Name;

	int32_t GeometryVersion;
	double Position[3];
	double Up[3];
	double LookAt[3];
	double Roll;
	int32_t Type;
	std::string FormatName;
	int32_t AspectType;
	double AspectW;
	double AspectH;
	double PixelRatio;
	double NearPlane;
	double FarPlane;
	int32_t CameraLock;
	std::string ApertureFormat;
	int32_t ApertureMode;
	double CameraAperture[2];
	double SqueezeRatio;
	double FocalLength;
	double Aperture;
	int32_t ViewFrustumPlane;
	int32_t BackgroundMode;
	int32_t ForegroundTransparent;
	double BackgroundTreshold;
	int32_t DisplayMode;
	double ViewFrustumPlaneDistance;
	int32_t ViewFrustumPlaneDistanceMode;
	int32_t ViewLookAt;
	int32_t ViewFrustum;
	int32_t ShowGrid;
	int32_t ShowAzimut;
	int32_t ShowName;
	int32_t ShowInfoOnMoving;
	int32_t ShowTimeCode;
	int32_t DisplaySafeArea;
	int32_t SafeAreaStyle;
	int32_t ShowAudio;
	double BackGroundColor[3];
	double AudioColor[3];
	int32_t UseFrameColor;
	double FrameColor[3];
	bool hasCameraAndLens ;
	fmtFBX_CameraAndLens CameraAndLens;
	fmtFBX_Camera () {
		TypeFlags = "Camera";
		Version = 210;
		Name = "Producer Perspective";

		GeometryVersion = 124;
		Position[0] = 0.0f;
		Position[1] = 71.3;
		Position[2] = 287.5f;
		Up[0] = 0.0f;
		Up[1] = 1.0f;
		Up[2] = 0.0f;
		LookAt[0] = 0.0f;
		LookAt[1] = 0.0f;
		LookAt[2] = 0.0f;
		Roll = 0.0f;
		Type = 0;
		FormatName = "Custom";
		AspectType = 0;
		AspectW = 320.0f;
		AspectH = 200.0f;
		PixelRatio = 1.0f;
		NearPlane = 10.0f;
		FarPlane = 4000.0f;
		CameraLock = 0;
		ApertureFormat = "35mm TV Projection";
		ApertureMode = 2;
		CameraAperture[0] = 0.816f;
		CameraAperture[1] = 0.612f;
		SqueezeRatio = 1.0f;
		FocalLength = 21.3545f;
		Aperture = 40.0f;
		ViewFrustumPlane = 2;
		BackgroundMode = 0;
		ForegroundTransparent = 1;
		BackgroundTreshold = 0.5f;
		DisplayMode = 6;
		ViewFrustumPlaneDistance = 100.0f;
		ViewFrustumPlaneDistanceMode = 0;
		ViewLookAt = 1;
		ViewFrustum = 0;
		ShowGrid = 1;
		ShowAzimut = 1;
		ShowName = 1;
		ShowInfoOnMoving = 1;
		ShowTimeCode = 0;
		DisplaySafeArea = 0;
		SafeAreaStyle = 1;
		ShowAudio = 0;
		BackGroundColor[0] = 0.0f;
		BackGroundColor[1] = 0.0f;
		BackGroundColor[2] = 0.0f;
		AudioColor[0] = 0.0f;
		AudioColor[1] = 1.0f;
		AudioColor[2] = 0.0f;
		UseFrameColor = 0;
		FrameColor[0] = 0.3f;
		FrameColor[1] = 0.3f;
		FrameColor[2] = 0.3f;
		hasCameraAndLens = true;

		}
	};

struct fmtFBX_Settings {
	std::vector<fmtFBX_Camera> Camera;
	int32_t TimeMode;
	int32_t TimeFormat;
	int32_t SnapOnFrames;
	int32_t ReferenceTimeIndex;
	fmtFBX_Settings () {
		TimeMode = 3;
		TimeFormat = 1;
		SnapOnFrames = 0;
		ReferenceTimeIndex = -1;
		}
	};

struct fmtFBX_CreationTimeStamp {
	int32_t Version;
	int32_t Year;
	int32_t Month;
	int32_t Day;
	int32_t Hour;
	int32_t Minute;
	int32_t Second;
	int32_t Millisecond;

	fmtFBX_CreationTimeStamp () {
		Version = 1000;
		Year = 2022;
		Month = 5;
		Day = 23;
		Hour = 17;
		Minute = 24;
		Second = 17;
		Millisecond = 244;

		}
	};

struct fmtFBX_OtherFlags {
	bool FlagPLE;
	int32_t TCDefinition;
	fmtFBX_OtherFlags () {
		FlagPLE = 0;
		TCDefinition = 127;
		}
	};

struct fmtFBX_FBXHeaderExtension {
	int32_t FBXHeaderVersion;
	int32_t FBXVersion;
	int32_t EncryptionType;

	bool hasCreationTimeStamp;
	fmtFBX_CreationTimeStamp CreationTimeStamp;

	bool hasCreator;
	std::string Creator;
	bool hasOtherFlags;
	fmtFBX_OtherFlags OtherFlags;

	fmtFBX_FBXHeaderExtension () {
		FBXHeaderVersion = 1000;
		FBXVersion = 5000;
		EncryptionType = 0;

		hasCreationTimeStamp = true;

		hasCreator = true;
		Creator = "FBX SDK/FBX Plugins build 20080212";

		hasOtherFlags = true;
		}
	};

struct fmtFBX_Properties {
	int32_t Version;
	double Size;
	fmtFBX_Properties () {
		Version = 100;
		Size = 100.0f;
		}
	};

struct fmtFBX_LayerElement {
	int32_t Index;
	int32_t Version;
	std::string Name;
	std::string MappingInformationType;
	std::string ReferenceInformationType;
	fmtFBX_LayerElement () {
		Index = -1;
		Version = 101;
		Name = "";
		MappingInformationType = "ByPolygonVertex";
		ReferenceInformationType = "Direct";

		}
	};

struct fmtFBX_ModelElementLayer_Info {
	std::string Type;
	int32_t TypedIndex;
	};

struct fmtFBX_ModelElementLayer {
	int32_t Version;
	std::string<fmtFBX_ModelElementLayer_Info> LayerElement;
	};

struct fmtFBX_LayerElementUV {
	fmtFBX_LayerElement Layer;
	std::vector<double> UV;
	std::vector<int32_t> UVIndex;
	};

struct fmtFBX_LayerElementUV {
	fmtFBX_LayerElement Layer;
	std::vector<double> Normals;
	};

struct fmtFBX_Material {
	std::string Name;
	int32_t Version;
	std::string ShadingModel;
	double Ambient[3];
	double Diffuse[3];
	double Specular[3];
	double Emissive[3];
	double Shininess;
	double Reflectivity;
	double Alpha;
	fmtFBX_Material () {
		Name = "Material #1 ( Standard )";
		Version = 100;
		ShadingModel = "Blinn";
		Ambient[0] = 0.0f;
		Ambient[1] = 0.0f;
		Ambient[2] = 0.0f;
		Diffuse[0] = 0.0f;
		Diffuse[1] = 0.0f;
		Diffuse[2] = 0.0f;
		Specular[0] = 0.045f;
		Specular[1] = 0.045f;
		Specular[2] = 0.045f;
		Emissive[0] = 0.0f;
		Emissive[1] = 0.0f;
		Emissive[2] = 0.0f;
		Shininess = 75.0f;
		Reflectivity = 0.3f;
		Alpha = 1.0f;
		}
	};

struct fmtFBX_Texture {
	std::string Name;
	std::string Type;
	int32_t Version;
	std::string TextureName;
	std::string Media;
	double Translation[2];
	double Scaling[2];
	double ModelUVTranslation[2];
	double ModelUVScaling[2];
	double Rotation[3];
	std::string Texture_Alpha_Source;
	int32_t Cropping[4];
	std::string Texture_Mapping_Type;
	std::string Texture_Planar_Mapping_Normal;
	int32_t SwapUV;
	int32_t MaterialMode;
	std::string TextureUse;
	double TextureAlpha;
	fmtFBX_Texture () {
		Name = "Map #0";
		Type = "TextureVideoClip";
		Version = 202;
		TextureName = "Map #0";
		Media = "";

		Translation[0] = 0.0f;
		Translation[1] = 0.0f;
		Scaling[0] = 1.0f;
		Scaling[1] = 1.0f;
		ModelUVTranslation[0] = 0.0f;
		ModelUVTranslation[1] = 0.0f;
		ModelUVScaling[0] = 1.0f;
		ModelUVScaling[1] = 1.0f;
		Rotation[0] = 0.0f;
		Rotation[1] = 0.0f;
		Rotation[2] = 0.0f;
		Texture_Alpha_Source = "None";
		Cropping[0] = 0;
		Cropping[1] = 0;
		Cropping[2] = 0;
		Cropping[3] = 0;
		Texture_Mapping_Type = "UV";
		Texture_Planar_Mapping_Normal = "X";
		SwapUV = 0;
		MaterialMode = 1;
		TextureUse = "Standard";
		TextureAlpha = 1.0f;
		}
	};

struct fmtFBX_Link {
	std::vector<std::string> UserData;
	std::vector<int32_t> Indexes;
	std::vector<double> Weights;
	std::vector<double> Transform;
	std::vector<double> TransformLink;

	};

struct fmtFBX_Shape {
	std::string Name;
	std::vector<int32_t> Indexes;
	std::vector<double> Vertices;
	std::vector<double> Normals;

	};

struct fmtFBX_GeometryUVInfo {
	int32_t Version;
	std::string MappingInformationType;
	std::vector<double> TextureUV;
	std::vector<int32_t> TextureUVVerticeIndex;
	fmtFBX_GeometryUVInfo () {
		Version = 240;
		MappingInformationType = "ByPolygon";
		}
	};

struct fmtFBX_Relation { // Object
	std::string Name;
	int32_t Version;
	std::vector<fmtFBX_Properties60> Property;
	fmtFBX_Layer Layer;


	std::string Type;
	std::string TypeFlags;
	fmtFBX_Properties Properties;

	// dynamic properties
	// used in 3000 to provide properties, is replaced with Properties60 in 6000
	std::vector <fmtFBX_Channel> Channel;
	std::vector <fmtFBX_Properties60> Properties60;


	std::vector<std::string> Children;

	std::vector<fmtFBX_Material> Material;
	std::vector<fmtFBX_Texture> Texture;

	// Mesh Specific Properies
	std::vector<fmtFBX_Link> Link; // bones
	std::vector<fmtFBX_Shape> Shape; // meshes

	std::vector<double> Vertices;
	std::string MaterialAssignation;
	int32_t Materials;
	std::vector<int32_t> PolygonVertexIndex;
	std::vector<int32_t> Edges;

	int32_t GeometryVersion;
	bool hasLayerElementNormal;
	std::vector<fmtFBX_LayerElementNormal> LayerElementNormal
	bool hasLayerElementUV;
	std::vector<fmtFBX_LayerElementUV> LayerElementUV;
	std::vector<fmtFBX_ModelElementLayer> Layer;
	std::string NodeAttributeName;








	fmtFBX_Relation () {
		Name = "Fbx_Root";
		Type = "Null";
		TypeFlags = "Null";
		GeometryVersion = 123;
		MaterialAssignation = "AllSame";
		Materials = 0;
		}
	};

struct fmtFBX_Definitions_Object {
	std::string Name;
	int32_t Count;
	fmtFBX_Definitions_Object () {
		Name = "Model";
		Count = 0;
		}
	};

struct fmtFBX_Definitions {
	int32_t Version;
	int32_t Count;
	std::vector<fmtFBX_Definitions_Object> ObjectType;
	};

struct fmtFBX_Version5 {
	bool hasAmbientRenderSettings;
	fmtFBX_AmbientRenderSettings AmbientRenderSettings;
	};


struct fmtFBX_Object {


};

struct fmtFBX_Binary {

	bool hasFBXHeaderExtension;
	fmtFBX_FBXHeaderExtension FBXHeaderExtension;

	uint8_t FileID[16]; // no idea what this is, but it changes each time I export from 3dsmax
	std::string CreationTime;

	// govern under as aswell
	bool hasCreator;
	std::string Creator;
	bool hasDocument;
	std::string Document;


	// References

	bool hasDefinitions;
	fmtFBX_Definitions Definitions;

	hasObjects;


	bool hasMedia;
	fmtFBX_Media Media;
	// insert dummy

	// insert dummy

	bool hasRelations;
	std::vector<fmtFBX_Relation> Relations;
	std::vector<fmtFBX_Relation> Connections;



	bool hasTakes;
	fmtFBX_Takes Takes;
	// insert dummy

	bool hasGoboManager;
	// insert dummy

	bool hasfmtFBX_Version5; // replaces 'hasAmbientRenderSettings'
	fmtFBX_Version5 Version5;
	// insert dummy

	bool hasFogOptions;
	fmtFBX_FogOptions FogOptions;
	// insert dummy

	bool hasRendererSetting;
	fmtFBX_RendererSetting RendererSetting;
	// insert dummy

	bool hasSettings;
	fmtFBX_Settings Settings;
	// insert dummy
	// insert dummy

	int32_t TimeMode;
	std::string FrameRate;
	int32_t TimeFormat;
	int32_t SnapOnFrames;
	int32_t ReferenceTimeIndex;
	int64_t TimeLineStartTime;
	int64_t TimeLineStopTime;
    // insert dummy
    // insert dummy


	fmtFBX_Binary () {
		hasFBXHeaderExtension = true;

		CreationTime = "";
		hasMedia = true;
		hasTakes = true;
		hasGoboManager = true;
		hasFogOptions = true;
		hasRendererSetting = true;
		hasSettings = true;
		hasfmtFBX_Version5 = true;
		TimeMode = 3;
		TimeFormat = 1;
		SnapOnFrames = 0;
		ReferenceTimeIndex = -1;
		TimeLineStartTime = 0;
		TimeLineStopTime = 0x000000001C09BC00;
		}
	};

struct fmtFBX_Block {
	uint64_t addr_end; // absolute
	uint64_t num_prop;
	uint64_t prop_size;
	uint64_t name_len;
	std::string name;
	bytestream buffer;

	size_t addr;
	size_t size;
	size_t prop_addr;

	fmtFBX_Block () {
		addr = 0;
		size = 0;
		addr_end = 0;
		num_prop = 0;
		prop_size = 0;
		name_len = 0;
		name = "";
		}
	~fmtFBX_Block () {
		buffer.close();
		}
	bool read (bytestream &f, uint32_t version, uint32_t level, int32_t par, int index, bool storeData = true, bool verbose = true) {
		bool isGood = false;
		addr = f.tell();
		if (addr + 13 < f.size) {

			if (version < 7500) {
				addr_end = f.readUlong();
				num_prop = f.readUlong();
				prop_size = f.readUlong();
				}
			else {
				addr_end = f.readUlonglong();
				num_prop = f.readUlonglong();
				prop_size = f.readUlonglong();
				}

			name_len = f.readUbyte();
			if (addr_end > 0) {
				isGood = true;
				}

			std::string pad;
			if (name_len > 0 && f.tell() + name_len < f.size) {
				name = f.readstring(name_len);
				if (verbose) {
					pad = "";
					for (unsigned int i = 0; i < level; i++) {
						pad += "    ";
						}
					std::cout << pad << par << " " << name << " (";

					}
				unsigned char dt;
				prop_addr = f.tell();

				if (num_prop > 0 && prop_size > 0 && prop_addr + prop_size < f.size) {



					if (storeData) {
						buffer.copy(f.stream, prop_size, prop_addr);

						buffer.seek(0);
						for (unsigned int i = 0; i < num_prop; i++) {
							dt = buffer.readUbyte();
							std::cout << dt << ":: ";
							switch (dt) {
								case 'Y': std::cout << "\t " << buffer.readshort(); break; // 0x59
								case 'C': std::cout << "\t " << (int)buffer.readbyte(); break; // 0x43 Char
								case 'I': std::cout << "\t " << buffer.readlong(); break; // 0x49 Integer
								case 'F': std::cout << "\t " << buffer.readfloat(); break; // 0x46 Float
								case 'D': std::cout << "\t " << buffer.readdouble(); break; // 0x44 Double
								case 'L': std::cout << "\t " << buffer.readlonglong(); break; // 0x4C LongLong
								case 'f': break; // 0x66
								case 'd': break; // 0x64
								case 'l': break; // 0x6C
								case 'i': break; // 0x69
								case 'b': break; // 0x62
								case 'S': std::cout << "\t " << buffer.readstring(buffer.readUlong()); break; // 0x53 String
								case 'R': break; // 0x52 Raw
								default: {
									std::cout << "\nERROR:\n\tUnknown Data Type [" << (int)dt << "] \t @ " << (f.tell() - 1) << std::endl;;
									isGood = false;
									f.seek(-1, 1);
									}
								}
							}




						}



					/*
					for (unsigned int i = 0; i < num_prop; i++) {
						data_type = f.readUbyte();
						switch (data_type) {
							case 'Y': f.seek(                2, 1); break; // 0x59
							case 'C': f.seek(                1, 1); break; // 0x43 Char
							case 'I': f.seek(                4, 1); break; // 0x49 Integer
							case 'F': f.seek(                4, 1); break; // 0x46 Float
							case 'D': f.seek(                8, 1); break; // 0x44 Double
							case 'L': f.seek(                8, 1); break; // 0x4C LongLong
							case 'f': f.seek(f.readUbyte() * 4, 1); break; // 0x66
							case 'd': f.seek(f.readUbyte() * 8, 1); break; // 0x64
							case 'l': f.seek(f.readUbyte() * 8, 1); break; // 0x6C
							case 'i': f.seek(f.readUbyte() * 4, 1); break; // 0x69
							case 'b': f.seek(f.readUbyte()    , 1); break; // 0x62
							case 'S': f.seek(f.readUlong()    , 1); break; // 0x53 String
							case 'R': f.seek(f.readUlong()    , 1); break; // 0x52 Raw
							default: {
								std::cout << "ERROR:\n\tUnknown Data Type [" << data_type << "] \t @ " << (f.tell() - 1) << std::endl;;
								isGood = false;
								f.seek(-1, 1);
								}
							}
						}
					*/


					f.seek(prop_addr + prop_size);
					}
				if (verbose) {std::cout  << ")    " << index <<  std::endl;;}

				}
			size = addr_end - addr;



			}
		return isGood;
		}

	};

struct fmtFBX_Footer {
	uint32_t unk001; // 0xE0A6B211
	uint32_t unk002; // 0xCBD6C978
	uint32_t unk003; // 0xAE6AE69F
	uint32_t unk004; // 0x02E13765

	// on newer verison
	uint8_t unk005[6];

	uint32_t unk006;
	uint32_t unk007; // size of data, -20 ?
	uint32_t unk008; // version
	uint8_t unk009[120];
	uint32_t unk010; // 0xE2409670
	uint32_t unk011; // 0xC4EFC364
	uint32_t unk012; // 0xF6F316F9
	uint32_t unk013; // 0x6F953311

	fmtFBX_Block* Properties;
	fmtFBX_Footer () {
		unk001 = 0xE0A6B211;
		unk002 = 0xCBD6C978;
		unk003 = 0xAE6AE69F;
		unk004 = 0x02E13765;
		// on newer verison

		for (unsigned int i = 0; i < 6; i++) {unk005[i] = 0;}
		unk005[1] = 0;
		unk005[2] = 0;
		unk005[3] = 0;
		unk005[4] = 0;
		unk005[5] = 0;
		unk006 = 0;
		unk007 = 0; // size of data, -20 ?
		unk008 = 0; // version
		for (unsigned int i = 0; i < 120; i++) {unk009[i] = 0;}
		unk010 = 0xE2409670;
		unk011 = 0xC4EFC364;
		unk012 = 0xF6F316F9;
		unk013 = 0x6F953311;
		Properties = NULL;
		}
	~fmtFBX_Footer () {
		if (Properties != NULL) {delete[] Properties;}
		}

	};

struct fmtFBX {
	// https://code.blender.org/2013/08/fbx-binary-file-format-specification/

	std::string FileType = "Kaydara FBX Binary  ";
	uint8_t unk001; // 0
	uint8_t unk002; // 26
	uint8_t unk003; // 0
	uint32_t FileVersion; // after 7400, the default for ints is 64bit instead of 32bit
	uint32_t FileCount;
	fmtFBX_Block* FileScene;




	fmtFBX () {
		FileType = "Kaydara FBX Binary  ";
		unk001 = 0;
		unk002 = 0;
		unk003 = 0;
		FileVersion = 0;
		FileCount = 0;
		FileScene = NULL;
		}

	~fmtFBX () {
		if (FileScene != NULL) {delete[] FileScene;}
		}

	void read_block (bytestream &f, uint32_t &count, uint32_t level, int32_t par, uint32_t &version, bool storeData = true, bool verbose = true) {

		// Check pointer is in bounds
		if (!f.eos()) {

			if (!storeData) {
				// Read Block
				fmtFBX_Block b;
				bool isGood = b.read(f, version, level, par, count, storeData, verbose);


				if (isGood) {


					// count
					count++;


					// Read Children
					if (f.tell() < b.addr_end) {

						read_block(f, count, level+1, count - 1, version, storeData, verbose);
						}

					// go to next block
					f.seek(b.addr_end);



					// Read Next Bloc
					read_block(f, count, level, par, version, storeData, verbose);


					}
				else {
					if (verbose) {
						std::cout << "------------------------------------------------------\n";
						}

					f.seek(f.size);
					}

				}
			else {

				// Read Block
				bool isGood = FileScene[count].read(f, version, level, par, count, storeData, verbose);


				if (isGood) {



					// count
					size_t endpos = FileScene[count].addr_end;
					count++;


					// Read Children
					if (f.tell() < endpos) {

						read_block(f, count, level+1, count - 1, version, storeData, verbose);
						}

					// go to next block
					f.seek(endpos);



					// Read Next Bloc
					read_block(f, count, level, par, version, storeData, verbose);


					}
				else {
					if (verbose) {
						std::cout << "------------------------------------------------------\n";
						}

					f.seek(f.size);
					}


				}
			}

		}

	void read_binary (bytestream &f) {


		FileType = f.readstring(20);
		unk001 = f.readUbyte();
		unk002 = f.readUbyte();
		unk003 = f.readUbyte();
		FileVersion = f.readUlong();
		FileCount = 0;
		if (FileScene != NULL) {delete[] FileScene; FileScene = NULL;}
		size_t pos = f.tell();
		unsigned int level = 0;

		signed int par = -1;

		read_block(f, FileCount, 0, -1, FileVersion, false);
		std::cout << "LastRead: \t" << f.tell() << std::endl;
		std::cout << "FileCount: \t" << FileCount << std::endl;

		if (FileCount > 0) {
			FileCount++;
			FileScene = new fmtFBX_Block[FileCount];

			f.seek(pos);
			unsigned int index = 0;
			par = -1;
			read_block(f, index, level, par, FileVersion, true);


			}

		}
	void read_ascii (bytestream &f) {
		}
	bool validate (bytestream &f, bool &isAscii) {
		size_t pos = f.tell();
		bool isGood = false;

		if (f.size > 20) {
			FileType = f.readstring(20);
			if (FileType == "Kaydara FBX Binary  ") {
				isGood = true;
				isAscii = false;
				}
			else {
				f.seek(0);
				std::string s = "";
				while (!not f.eos()) {
					s = f.readline();
					if (s.find("FBX") != std::string::npos) {
						isGood = true;
						isAscii = true;
						break;
						}
					}
				}
			} else {std::cout << "Validation Error:\n\tInvalid File Size\n";}
		f.seek(pos);
		return isGood;
		}
	void read (bytestream &f) {
		bool isAscii = false;
		if (validate(f, isAscii)) {
			if (isAscii) {read_ascii(f);}
			else {read_binary(f);}
			} else {std::cout << "Validation Error:\n\tInvalid Filen\n";}
		}

	};

#endif // FMTFBX_H
