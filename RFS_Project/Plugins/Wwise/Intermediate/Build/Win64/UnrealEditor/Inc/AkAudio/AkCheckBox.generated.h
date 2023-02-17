// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
struct FGuid;
enum class ECheckBoxState : uint8;
#ifdef AKAUDIO_AkCheckBox_generated_h
#error "AkCheckBox.generated.h already included, missing '#pragma once' in AkCheckBox.h"
#endif
#define AKAUDIO_AkCheckBox_generated_h

#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_34_DELEGATE \
struct _Script_AkAudio_eventAkOnCheckBoxComponentStateChanged_Parms \
{ \
	bool bIsChecked; \
}; \
static inline void FAkOnCheckBoxComponentStateChanged_DelegateWrapper(const FMulticastScriptDelegate& AkOnCheckBoxComponentStateChanged, bool bIsChecked) \
{ \
	_Script_AkAudio_eventAkOnCheckBoxComponentStateChanged_Parms Parms; \
	Parms.bIsChecked=bIsChecked ? true : false; \
	AkOnCheckBoxComponentStateChanged.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_37_DELEGATE \
struct _Script_AkAudio_eventOnWwiseItemDropDetected_Parms \
{ \
	FGuid ItemDroppedID; \
}; \
static inline void FOnWwiseItemDropDetected_DelegateWrapper(const FMulticastScriptDelegate& OnWwiseItemDropDetected, FGuid ItemDroppedID) \
{ \
	_Script_AkAudio_eventOnWwiseItemDropDetected_Parms Parms; \
	Parms.ItemDroppedID=ItemDroppedID; \
	OnWwiseItemDropDetected.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_40_DELEGATE \
struct _Script_AkAudio_eventOnBoolPropertyDropDetected_Parms \
{ \
	FString PropertyDropped; \
}; \
static inline void FOnBoolPropertyDropDetected_DelegateWrapper(const FMulticastScriptDelegate& OnBoolPropertyDropDetected, const FString& PropertyDropped) \
{ \
	_Script_AkAudio_eventOnBoolPropertyDropDetected_Parms Parms; \
	Parms.PropertyDropped=PropertyDropped; \
	OnBoolPropertyDropDetected.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_SPARSE_DATA
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execGetAkProperty); \
	DECLARE_FUNCTION(execSetAkBoolProperty); \
	DECLARE_FUNCTION(execGetAkItemId); \
	DECLARE_FUNCTION(execSetAkItemId); \
	DECLARE_FUNCTION(execSetCheckedState); \
	DECLARE_FUNCTION(execSetIsChecked); \
	DECLARE_FUNCTION(execGetCheckedState); \
	DECLARE_FUNCTION(execIsChecked); \
	DECLARE_FUNCTION(execIsPressed);


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execGetAkProperty); \
	DECLARE_FUNCTION(execSetAkBoolProperty); \
	DECLARE_FUNCTION(execGetAkItemId); \
	DECLARE_FUNCTION(execSetAkItemId); \
	DECLARE_FUNCTION(execSetCheckedState); \
	DECLARE_FUNCTION(execSetIsChecked); \
	DECLARE_FUNCTION(execGetCheckedState); \
	DECLARE_FUNCTION(execIsChecked); \
	DECLARE_FUNCTION(execIsPressed);


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAkCheckBox(); \
	friend struct Z_Construct_UClass_UAkCheckBox_Statics; \
public: \
	DECLARE_CLASS(UAkCheckBox, UContentWidget, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkCheckBox) \
	static const TCHAR* StaticConfigName() {return TEXT("Editor");} \



#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_INCLASS \
private: \
	static void StaticRegisterNativesUAkCheckBox(); \
	friend struct Z_Construct_UClass_UAkCheckBox_Statics; \
public: \
	DECLARE_CLASS(UAkCheckBox, UContentWidget, COMPILED_IN_FLAGS(0 | CLASS_DefaultConfig | CLASS_Config), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkCheckBox) \
	static const TCHAR* StaticConfigName() {return TEXT("Editor");} \



#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkCheckBox(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkCheckBox) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkCheckBox); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkCheckBox); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkCheckBox(UAkCheckBox&&); \
	NO_API UAkCheckBox(const UAkCheckBox&); \
public:


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkCheckBox(UAkCheckBox&&); \
	NO_API UAkCheckBox(const UAkCheckBox&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkCheckBox); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkCheckBox); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkCheckBox)


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_50_PROLOG
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_SPARSE_DATA \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_RPC_WRAPPERS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_INCLASS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_SPARSE_DATA \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_INCLASS_NO_PURE_DECLS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h_53_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AKAUDIO_API UClass* StaticClass<class UAkCheckBox>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkWaapiUMG_Components_AkCheckBox_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
