// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef AKAUDIO_AkSettings_generated_h
#error "AkSettings.generated.h already included, missing '#pragma once' in AkSettings.h"
#endif
#define AKAUDIO_AkSettings_generated_h

#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_63_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FAkGeometrySurfacePropertiesToMap_Statics; \
	AKAUDIO_API static class UScriptStruct* StaticStruct();


template<> AKAUDIO_API UScriptStruct* StaticStruct<struct FAkGeometrySurfacePropertiesToMap>();

#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_98_GENERATED_BODY \
	friend struct Z_Construct_UScriptStruct_FAkAcousticTextureParams_Statics; \
	AKAUDIO_API static class UScriptStruct* StaticStruct();


template<> AKAUDIO_API UScriptStruct* StaticStruct<struct FAkAcousticTextureParams>();

#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_SPARSE_DATA
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_RPC_WRAPPERS
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_RPC_WRAPPERS_NO_PURE_DECLS
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAkSettings(); \
	friend struct Z_Construct_UClass_UAkSettings_Statics; \
public: \
	DECLARE_CLASS(UAkSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_INCLASS \
private: \
	static void StaticRegisterNativesUAkSettings(); \
	friend struct Z_Construct_UClass_UAkSettings_Statics; \
public: \
	DECLARE_CLASS(UAkSettings, UObject, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkSettings) \
	static const TCHAR* StaticConfigName() {return TEXT("Game");} \



#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkSettings(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkSettings) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkSettings); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkSettings(UAkSettings&&); \
	NO_API UAkSettings(const UAkSettings&); \
public:


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkSettings(UAkSettings&&); \
	NO_API UAkSettings(const UAkSettings&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkSettings); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkSettings); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkSettings)


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_121_PROLOG
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_SPARSE_DATA \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_RPC_WRAPPERS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_INCLASS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_SPARSE_DATA \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_INCLASS_NO_PURE_DECLS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h_124_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AKAUDIO_API UClass* StaticClass<class UAkSettings>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSettings_h


#define FOREACH_ENUM_EAKCOLLISIONCHANNEL(op) \
	op(EAKCC_WorldStatic) \
	op(EAKCC_WorldDynamic) \
	op(EAKCC_Pawn) \
	op(EAKCC_Visibility) \
	op(EAKCC_Camera) \
	op(EAKCC_PhysicsBody) \
	op(EAKCC_Vehicle) \
	op(EAKCC_Destructible) \
	op(EAKCC_UseIntegrationSettingsDefault) 
#define FOREACH_ENUM_EAKUNREALAUDIOROUTING(op) \
	op(EAkUnrealAudioRouting::Custom) \
	op(EAkUnrealAudioRouting::Separate) \
	op(EAkUnrealAudioRouting::AudioLink) \
	op(EAkUnrealAudioRouting::AudioMixer) \
	op(EAkUnrealAudioRouting::EnableWwiseOnly) \
	op(EAkUnrealAudioRouting::EnableUnrealOnly) 

enum class EAkUnrealAudioRouting;
template<> AKAUDIO_API UEnum* StaticEnum<EAkUnrealAudioRouting>();

PRAGMA_ENABLE_DEPRECATION_WARNINGS
