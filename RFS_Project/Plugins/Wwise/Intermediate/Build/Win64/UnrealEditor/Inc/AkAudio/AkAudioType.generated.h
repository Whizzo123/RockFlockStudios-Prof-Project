// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef AKAUDIO_AkAudioType_generated_h
#error "AkAudioType.generated.h already included, missing '#pragma once' in AkAudioType.h"
#endif
#define AKAUDIO_AkAudioType_generated_h

#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_SPARSE_DATA
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetWwiseShortID); \
	DECLARE_FUNCTION(execUnloadData); \
	DECLARE_FUNCTION(execLoadData);


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetWwiseShortID); \
	DECLARE_FUNCTION(execUnloadData); \
	DECLARE_FUNCTION(execLoadData);


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_ARCHIVESERIALIZER \
	DECLARE_FSTRUCTUREDARCHIVE_SERIALIZER(UAkAudioType, NO_API)


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAkAudioType(); \
	friend struct Z_Construct_UClass_UAkAudioType_Statics; \
public: \
	DECLARE_CLASS(UAkAudioType, UObject, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkAudioType) \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_ARCHIVESERIALIZER


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_INCLASS \
private: \
	static void StaticRegisterNativesUAkAudioType(); \
	friend struct Z_Construct_UClass_UAkAudioType_Statics; \
public: \
	DECLARE_CLASS(UAkAudioType, UObject, COMPILED_IN_FLAGS(CLASS_Abstract), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkAudioType) \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_ARCHIVESERIALIZER


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkAudioType(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkAudioType) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkAudioType); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkAudioType); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkAudioType(UAkAudioType&&); \
	NO_API UAkAudioType(const UAkAudioType&); \
public:


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkAudioType(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkAudioType(UAkAudioType&&); \
	NO_API UAkAudioType(const UAkAudioType&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkAudioType); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkAudioType); \
	DEFINE_ABSTRACT_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkAudioType)


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_29_PROLOG
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_SPARSE_DATA \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_RPC_WRAPPERS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_INCLASS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_SPARSE_DATA \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_INCLASS_NO_PURE_DECLS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h_32_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AKAUDIO_API UClass* StaticClass<class UAkAudioType>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkAudioType_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
