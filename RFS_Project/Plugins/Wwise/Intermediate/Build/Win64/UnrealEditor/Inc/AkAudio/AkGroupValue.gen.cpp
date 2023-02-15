// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AkAudio/Classes/AkGroupValue.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAkGroupValue() {}
// Cross Module References
	AKAUDIO_API UClass* Z_Construct_UClass_UAkGroupValue_NoRegister();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkGroupValue();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkAudioType();
	UPackage* Z_Construct_UPackage__Script_AkAudio();
	WWISERESOURCELOADER_API UScriptStruct* Z_Construct_UScriptStruct_FWwiseGroupValueCookedData();
	WWISERESOURCELOADER_API UScriptStruct* Z_Construct_UScriptStruct_FWwiseGroupValueInfo();
// End Cross Module References
	void UAkGroupValue::StaticRegisterNativesUAkGroupValue()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAkGroupValue);
	UClass* Z_Construct_UClass_UAkGroupValue_NoRegister()
	{
		return UAkGroupValue::StaticClass();
	}
	struct Z_Construct_UClass_UAkGroupValue_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GroupValueCookedData_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GroupValueCookedData;
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GroupValueInfo_MetaData[];
#endif
		static const UECodeGen_Private::FStructPropertyParams NewProp_GroupValueInfo;
#endif // WITH_EDITORONLY_DATA
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_GroupShortID_MetaData[];
#endif
		static const UECodeGen_Private::FUInt32PropertyParams NewProp_GroupShortID;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_EDITORONLY_DATA
#endif // WITH_EDITORONLY_DATA
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAkGroupValue_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAkAudioType,
		(UObject* (*)())Z_Construct_UPackage__Script_AkAudio,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkGroupValue_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "AkGroupValue.h" },
		{ "ModuleRelativePath", "Classes/AkGroupValue.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupValueCookedData_MetaData[] = {
		{ "Category", "AkGroupValue" },
		{ "ModuleRelativePath", "Classes/AkGroupValue.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupValueCookedData = { "GroupValueCookedData", nullptr, (EPropertyFlags)0x0010000000022001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkGroupValue, GroupValueCookedData), Z_Construct_UScriptStruct_FWwiseGroupValueCookedData, METADATA_PARAMS(Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupValueCookedData_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupValueCookedData_MetaData)) }; // 731096078
#if WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupValueInfo_MetaData[] = {
		{ "Category", "AkGroupValue" },
		{ "ModuleRelativePath", "Classes/AkGroupValue.h" },
	};
#endif
	const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupValueInfo = { "GroupValueInfo", nullptr, (EPropertyFlags)0x0010000800000001, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkGroupValue, GroupValueInfo), Z_Construct_UScriptStruct_FWwiseGroupValueInfo, METADATA_PARAMS(Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupValueInfo_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupValueInfo_MetaData)) }; // 4159322958
#endif // WITH_EDITORONLY_DATA
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupShortID_MetaData[] = {
		{ "Deprecated", "" },
		{ "DeprecationMessage", "Use Group ID from Load Data. Used for migration from older versions." },
		{ "ModuleRelativePath", "Classes/AkGroupValue.h" },
	};
#endif
	const UECodeGen_Private::FUInt32PropertyParams Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupShortID = { "GroupShortID", nullptr, (EPropertyFlags)0x0010000020000000, UECodeGen_Private::EPropertyGenFlags::UInt32, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(UAkGroupValue, GroupShortID_DEPRECATED), METADATA_PARAMS(Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupShortID_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupShortID_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UAkGroupValue_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupValueCookedData,
#if WITH_EDITORONLY_DATA
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupValueInfo,
#endif // WITH_EDITORONLY_DATA
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UAkGroupValue_Statics::NewProp_GroupShortID,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAkGroupValue_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAkGroupValue>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UAkGroupValue_Statics::ClassParams = {
		&UAkGroupValue::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UAkGroupValue_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UAkGroupValue_Statics::PropPointers),
		0,
		0x001000A1u,
		METADATA_PARAMS(Z_Construct_UClass_UAkGroupValue_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAkGroupValue_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAkGroupValue()
	{
		if (!Z_Registration_Info_UClass_UAkGroupValue.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAkGroupValue.OuterSingleton, Z_Construct_UClass_UAkGroupValue_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UAkGroupValue.OuterSingleton;
	}
	template<> AKAUDIO_API UClass* StaticClass<UAkGroupValue>()
	{
		return UAkGroupValue::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAkGroupValue);
	struct Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGroupValue_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGroupValue_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UAkGroupValue, UAkGroupValue::StaticClass, TEXT("UAkGroupValue"), &Z_Registration_Info_UClass_UAkGroupValue, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAkGroupValue), 4039774958U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGroupValue_h_3060714318(TEXT("/Script/AkAudio"),
		Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGroupValue_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkGroupValue_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
