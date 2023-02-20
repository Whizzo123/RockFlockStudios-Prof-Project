// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
class AActor;
struct FAkUniqueID;
class UAkEffectShareSet;
class UAkAuxBus;
struct FAkOutputDeviceID;
class UAkAudioType;
class UObject;
struct FLatentActionInfo;
struct FAkOutputSettings;
enum class PanningRule : uint8;
enum class AkChannelConfiguration : uint8;
class UAkPortalComponent;
class UAkComponent;
struct FAkChannelMask;
enum class AkMultiPositionType : uint8;
class UAkSwitchValue;
class UAkTrigger;
class UAkStateValue;
class UAkRtpc;
enum class ERTPCValueType : uint8;
class UAkAudioEvent;
enum class AkActionOnEventType : uint8;
enum class EAkCurveInterpolation : uint8;
class USceneComponent;
#ifdef AKAUDIO_AkGameplayStatics_generated_h
#error "AkGameplayStatics.generated.h already included, missing '#pragma once' in AkGameplayStatics.h"
#endif
#define AKAUDIO_AkGameplayStatics_generated_h

#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_SPARSE_DATA
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execSetDistanceProbe); \
	DECLARE_FUNCTION(execSetActorMixerEffect); \
	DECLARE_FUNCTION(execSetAuxBusEffect); \
	DECLARE_FUNCTION(execSetBusEffectByID); \
	DECLARE_FUNCTION(execSetBusEffectByName); \
	DECLARE_FUNCTION(execSetOutputDeviceEffect); \
	DECLARE_FUNCTION(execGetAkAudioTypeUserData); \
	DECLARE_FUNCTION(execSetCurrentAudioCultureAsync); \
	DECLARE_FUNCTION(execSetCurrentAudioCulture); \
	DECLARE_FUNCTION(execGetAvailableAudioCultures); \
	DECLARE_FUNCTION(execGetCurrentAudioCulture); \
	DECLARE_FUNCTION(execStopProfilerCapture); \
	DECLARE_FUNCTION(execStartProfilerCapture); \
	DECLARE_FUNCTION(execStopOutputCapture); \
	DECLARE_FUNCTION(execAddOutputCaptureMarker); \
	DECLARE_FUNCTION(execStartOutputCapture); \
	DECLARE_FUNCTION(execUnloadBankByName); \
	DECLARE_FUNCTION(execLoadBankByName); \
	DECLARE_FUNCTION(execUnloadInitBank); \
	DECLARE_FUNCTION(execLoadInitBank); \
	DECLARE_FUNCTION(execClearSoundBanksAndMedia); \
	DECLARE_FUNCTION(execClearBanks); \
	DECLARE_FUNCTION(execStopAllAmbientSounds); \
	DECLARE_FUNCTION(execStartAllAmbientSounds); \
	DECLARE_FUNCTION(execCancelEventCallback); \
	DECLARE_FUNCTION(execStopAll); \
	DECLARE_FUNCTION(execStopActor); \
	DECLARE_FUNCTION(execSetOcclusionRefreshInterval); \
	DECLARE_FUNCTION(execSetSpeakerAngles); \
	DECLARE_FUNCTION(execGetSpeakerAngles); \
	DECLARE_FUNCTION(execReplaceMainOutput); \
	DECLARE_FUNCTION(execSetPanningRule); \
	DECLARE_FUNCTION(execSetBusConfig); \
	DECLARE_FUNCTION(execSetOutputBusVolume); \
	DECLARE_FUNCTION(execSetPortalToPortalObstruction); \
	DECLARE_FUNCTION(execSetGameObjectToPortalObstruction); \
	DECLARE_FUNCTION(execSetPortalObstructionAndOcclusion); \
	DECLARE_FUNCTION(execSetReflectionsOrder); \
	DECLARE_FUNCTION(execUseEarlyReflections); \
	DECLARE_FUNCTION(execUseReverbVolumes); \
	DECLARE_FUNCTION(execSetMultipleChannelMaskEmitterPositions); \
	DECLARE_FUNCTION(execSetMultipleChannelEmitterPositions); \
	DECLARE_FUNCTION(execSetMultiplePositions); \
	DECLARE_FUNCTION(execSetSwitch); \
	DECLARE_FUNCTION(execPostTrigger); \
	DECLARE_FUNCTION(execSetState); \
	DECLARE_FUNCTION(execResetRTPCValue); \
	DECLARE_FUNCTION(execGetRTPCValue); \
	DECLARE_FUNCTION(execSetRTPCValue); \
	DECLARE_FUNCTION(execSpawnAkComponentAtLocation); \
	DECLARE_FUNCTION(execExecuteActionOnPlayingID); \
	DECLARE_FUNCTION(execExecuteActionOnEvent); \
	DECLARE_FUNCTION(execPostEventAtLocationByName); \
	DECLARE_FUNCTION(execPostEventAtLocation); \
	DECLARE_FUNCTION(execPostEventByName); \
	DECLARE_FUNCTION(execPostAndWaitForEndOfEventAsync); \
	DECLARE_FUNCTION(execPostAndWaitForEndOfEvent); \
	DECLARE_FUNCTION(execPostEvent); \
	DECLARE_FUNCTION(execIsGame); \
	DECLARE_FUNCTION(execIsEditor); \
	DECLARE_FUNCTION(execGetAkComponent);


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execSetDistanceProbe); \
	DECLARE_FUNCTION(execSetActorMixerEffect); \
	DECLARE_FUNCTION(execSetAuxBusEffect); \
	DECLARE_FUNCTION(execSetBusEffectByID); \
	DECLARE_FUNCTION(execSetBusEffectByName); \
	DECLARE_FUNCTION(execSetOutputDeviceEffect); \
	DECLARE_FUNCTION(execGetAkAudioTypeUserData); \
	DECLARE_FUNCTION(execSetCurrentAudioCultureAsync); \
	DECLARE_FUNCTION(execSetCurrentAudioCulture); \
	DECLARE_FUNCTION(execGetAvailableAudioCultures); \
	DECLARE_FUNCTION(execGetCurrentAudioCulture); \
	DECLARE_FUNCTION(execStopProfilerCapture); \
	DECLARE_FUNCTION(execStartProfilerCapture); \
	DECLARE_FUNCTION(execStopOutputCapture); \
	DECLARE_FUNCTION(execAddOutputCaptureMarker); \
	DECLARE_FUNCTION(execStartOutputCapture); \
	DECLARE_FUNCTION(execUnloadBankByName); \
	DECLARE_FUNCTION(execLoadBankByName); \
	DECLARE_FUNCTION(execUnloadInitBank); \
	DECLARE_FUNCTION(execLoadInitBank); \
	DECLARE_FUNCTION(execClearSoundBanksAndMedia); \
	DECLARE_FUNCTION(execClearBanks); \
	DECLARE_FUNCTION(execStopAllAmbientSounds); \
	DECLARE_FUNCTION(execStartAllAmbientSounds); \
	DECLARE_FUNCTION(execCancelEventCallback); \
	DECLARE_FUNCTION(execStopAll); \
	DECLARE_FUNCTION(execStopActor); \
	DECLARE_FUNCTION(execSetOcclusionRefreshInterval); \
	DECLARE_FUNCTION(execSetSpeakerAngles); \
	DECLARE_FUNCTION(execGetSpeakerAngles); \
	DECLARE_FUNCTION(execReplaceMainOutput); \
	DECLARE_FUNCTION(execSetPanningRule); \
	DECLARE_FUNCTION(execSetBusConfig); \
	DECLARE_FUNCTION(execSetOutputBusVolume); \
	DECLARE_FUNCTION(execSetPortalToPortalObstruction); \
	DECLARE_FUNCTION(execSetGameObjectToPortalObstruction); \
	DECLARE_FUNCTION(execSetPortalObstructionAndOcclusion); \
	DECLARE_FUNCTION(execSetReflectionsOrder); \
	DECLARE_FUNCTION(execUseEarlyReflections); \
	DECLARE_FUNCTION(execUseReverbVolumes); \
	DECLARE_FUNCTION(execSetMultipleChannelMaskEmitterPositions); \
	DECLARE_FUNCTION(execSetMultipleChannelEmitterPositions); \
	DECLARE_FUNCTION(execSetMultiplePositions); \
	DECLARE_FUNCTION(execSetSwitch); \
	DECLARE_FUNCTION(execPostTrigger); \
	DECLARE_FUNCTION(execSetState); \
	DECLARE_FUNCTION(execResetRTPCValue); \
	DECLARE_FUNCTION(execGetRTPCValue); \
	DECLARE_FUNCTION(execSetRTPCValue); \
	DECLARE_FUNCTION(execSpawnAkComponentAtLocation); \
	DECLARE_FUNCTION(execExecuteActionOnPlayingID); \
	DECLARE_FUNCTION(execExecuteActionOnEvent); \
	DECLARE_FUNCTION(execPostEventAtLocationByName); \
	DECLARE_FUNCTION(execPostEventAtLocation); \
	DECLARE_FUNCTION(execPostEventByName); \
	DECLARE_FUNCTION(execPostAndWaitForEndOfEventAsync); \
	DECLARE_FUNCTION(execPostAndWaitForEndOfEvent); \
	DECLARE_FUNCTION(execPostEvent); \
	DECLARE_FUNCTION(execIsGame); \
	DECLARE_FUNCTION(execIsEditor); \
	DECLARE_FUNCTION(execGetAkComponent);


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAkGameplayStatics(); \
	friend struct Z_Construct_UClass_UAkGameplayStatics_Statics; \
public: \
	DECLARE_CLASS(UAkGameplayStatics, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkGameplayStatics)


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_INCLASS \
private: \
	static void StaticRegisterNativesUAkGameplayStatics(); \
	friend struct Z_Construct_UClass_UAkGameplayStatics_Statics; \
public: \
	DECLARE_CLASS(UAkGameplayStatics, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AkAudio"), NO_API) \
	DECLARE_SERIALIZER(UAkGameplayStatics)


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAkGameplayStatics(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkGameplayStatics) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkGameplayStatics); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkGameplayStatics); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkGameplayStatics(UAkGameplayStatics&&); \
	NO_API UAkGameplayStatics(const UAkGameplayStatics&); \
public:


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UAkGameplayStatics(UAkGameplayStatics&&); \
	NO_API UAkGameplayStatics(const UAkGameplayStatics&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAkGameplayStatics); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAkGameplayStatics); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAkGameplayStatics)


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_34_PROLOG
#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_SPARSE_DATA \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_RPC_WRAPPERS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_INCLASS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_SPARSE_DATA \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_INCLASS_NO_PURE_DECLS \
	FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h_37_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> AKAUDIO_API UClass* StaticClass<class UAkGameplayStatics>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGameplayStatics_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
