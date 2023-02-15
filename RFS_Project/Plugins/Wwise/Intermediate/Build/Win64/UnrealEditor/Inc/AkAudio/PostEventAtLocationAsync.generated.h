// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class UObject;
class UAkAudioEvent;
class UPostEventAtLocationAsync;
#ifdef AKAUDIO_PostEventAtLocationAsync_generated_h
#error "PostEventAtLocationAsync.generated.h already included, missing '#pragma once' in PostEventAtLocationAsync.h"
#endif
#define AKAUDIO_PostEventAtLocationAsync_generated_h

#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_24_DELEGATE \
struct _Script_AkAudio_eventPostEventAtLocationAsyncOutputPin_Parms \
{ \
	int32 PlayingID; \
}; \
static inline void FPostEventAtLocationAsyncOutputPin_DelegateWrapper(const FMulticastScriptDelegate& PostEventAtLocationAsyncOutputPin, int32 PlayingID) \
{ \
	_Script_AkAudio_eventPostEventAtLocationAsyncOutputPin_Parms Parms; \
	Parms.PlayingID=PlayingID; \
	PostEventAtLocationAsyncOutputPin.ProcessMulticastDelegate<UObject>(&Parms); \
}


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_SPARSE_DATA
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execPollPostEventFuture); \
	DECLARE_FUNCTION(execPostEventAtLocationAsync);


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execPollPostEventFuture); \
	DECLARE_FUNCTION(execPostEventAtLocationAsync);


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUPostEventAtLocationAsync(); \
	friend struct Z_Construct_UClass_UPostEventAtLocationAsync_Statics; \
public: \
	DECLARE_CLASS(UPostEventAtLocationAsync, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UPostEventAtLocationAsync)


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_INCLASS \
private: \
	static void StaticRegisterNativesUPostEventAtLocationAsync(); \
	friend struct Z_Construct_UClass_UPostEventAtLocationAsync_Statics; \
public: \
	DECLARE_CLASS(UPostEventAtLocationAsync, UBlueprintAsyncActionBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UPostEventAtLocationAsync)


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UPostEventAtLocationAsync(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPostEventAtLocationAsync) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPostEventAtLocationAsync); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPostEventAtLocationAsync); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UPostEventAtLocationAsync(UPostEventAtLocationAsync&&); \
	NO_API UPostEventAtLocationAsync(const UPostEventAtLocationAsync&); \
public:


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UPostEventAtLocationAsync(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }; \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UPostEventAtLocationAsync(UPostEventAtLocationAsync&&); \
	NO_API UPostEventAtLocationAsync(const UPostEventAtLocationAsync&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UPostEventAtLocationAsync); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UPostEventAtLocationAsync); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UPostEventAtLocationAsync)


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_26_PROLOG
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_SPARSE_DATA \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_RPC_WRAPPERS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_INCLASS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_SPARSE_DATA \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_INCLASS_NO_PURE_DECLS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AKAUDIO_API UClass* StaticClass<class UPostEventAtLocationAsync>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_BlueprintNodes_PostEventAtLocationAsync_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
