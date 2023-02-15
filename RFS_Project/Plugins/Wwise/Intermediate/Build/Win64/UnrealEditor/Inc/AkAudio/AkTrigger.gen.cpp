// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AkAudio/Classes/AkTrigger.h"
#include "Serialization/ArchiveUObjectFromStructuredArchive.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAkTrigger() {}
// Cross Module References
	AKAUDIO_API UClass* Z_Construct_UClass_UAkTrigger_NoRegister();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkTrigger();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkAudioType();
	UPackage* Z_Construct_UPackage__Script_AkAudio();
	WWISERESOURCELOADER_API UScriptStruct* Z_Construct_UScriptStruct_FWwiseTriggerCookedData();
	WWISERESOURCELOADER_API UScriptStruct* Z_Construct_UScriptStruct_FWwiseObjectInfo();
// End Cross Module References
	void UAkTrigger::StaticRegisterNativesUAkTrigger()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAkTrigger);
	UClass* Z_Construct_UClass_UAkTrigger_NoRegister()
	{
		return UAkTrigger::StaticClass();
	}
	struct Z_Construct_UClass_UAkTrigger_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TriggerCookedData_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_TriggerCookedData;
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_TriggerInfo_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_TriggerInfo;
#endif // WITH_EDITORONLY_DATA
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_EDITORONLY_DATA
#endif // WITH_EDITORONLY_DATA
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAkTrigger_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAkAudioType,
		(UObject* (*)())Z_Construct_UPackage__Script_AkAudio,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkTrigger_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "AkTrigger.h" },
		{ "ModuleRelativePath", "Classes/AkTrigger.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkTrigger_Statics::NewProp_TriggerCookedData_MetaData[] = {
		{ "Category", "AkTexture" },
		{ "ModuleRelativePath", "Classes/AkTrigger.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAkTrigger_Statics::NewProp_TriggerCookedData = { "TriggerCookedData", nullptr, (EPropertyFlags)0x0010000000022001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkTrigger, TriggerCookedData), Z_Construct_UScriptStruct_FWwiseTriggerCookedData, METADATA_PARAMS(Z_Construct_UClass_UAkTrigger_Statics::NewProp_TriggerCookedData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAkTrigger_Statics::NewProp_TriggerCookedData_MetaData)) }; // 2089552064
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkTrigger_Statics::NewProp_TriggerInfo_MetaData[] = {
		{ "Category", "AkTexture" },
		{ "ModuleRelativePath", "Classes/AkTrigger.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAkTrigger_Statics::NewProp_TriggerInfo = { "TriggerInfo", nullptr, (EPropertyFlags)0x0010000800000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkTrigger, TriggerInfo), Z_Construct_UScriptStruct_FWwiseObjectInfo, METADATA_PARAMS(Z_Construct_UClass_UAkTrigger_Statics::NewProp_TriggerInfo_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAkTrigger_Statics::NewProp_TriggerInfo_MetaData)) }; // 2053370781
#endif // WITH_EDITORONLY_DATA
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAkTrigger_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkTrigger_Statics::NewProp_TriggerCookedData,
#if WITH_EDITORONLY_DATA
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkTrigger_Statics::NewProp_TriggerInfo,
#endif // WITH_EDITORONLY_DATA
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAkTrigger_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAkTrigger>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UAkTrigger_Statics::ClassParams = {
		&UAkTrigger::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UAkTrigger_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UAkTrigger_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAkTrigger_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAkTrigger_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAkTrigger()
	{
		if (!Z_Registration_Info_UClass_UAkTrigger.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAkTrigger.OuterSingleton, Z_Construct_UClass_UAkTrigger_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UAkTrigger.OuterSingleton;
	}
	template<> AKAUDIO_API UClass* StaticClass<UAkTrigger>()
	{
		return UAkTrigger::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAkTrigger);
	IMPLEMENT_FSTRUCTUREDARCHIVE_SERIALIZER(UAkTrigger)
	struct Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkTrigger_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkTrigger_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UAkTrigger, UAkTrigger::StaticClass, TEXT("UAkTrigger"), &Z_Registration_Info_UClass_UAkTrigger, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAkTrigger), 3700397974U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkTrigger_h_4173740831(TEXT("/Script/AkAudio"),
		Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkTrigger_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkTrigger_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
