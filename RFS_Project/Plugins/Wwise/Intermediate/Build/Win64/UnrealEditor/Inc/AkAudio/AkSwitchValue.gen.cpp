// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AkAudio/Classes/AkSwitchValue.h"
#include "Serialization/ArchiveUObjectFromStructuredArchive.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeAkSwitchValue() {}
// Cross Module References
	AKAUDIO_API UClass* Z_Construct_UClass_UAkSwitchValue_NoRegister();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkSwitchValue();
	AKAUDIO_API UClass* Z_Construct_UClass_UAkGroupValue();
	UPackage* Z_Construct_UPackage__Script_AkAudio();
// End Cross Module References
	void UAkSwitchValue::StaticRegisterNativesUAkSwitchValue()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UAkSwitchValue);
	UClass* Z_Construct_UClass_UAkSwitchValue_NoRegister()
	{
		return UAkSwitchValue::StaticClass();
	}
	struct Z_Construct_UClass_UAkSwitchValue_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UAkSwitchValue_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UAkGroupValue,
		(UObject* (*)())Z_Construct_UPackage__Script_AkAudio,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UAkSwitchValue_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "AkSwitchValue.h" },
		{ "ModuleRelativePath", "Classes/AkSwitchValue.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UAkSwitchValue_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAkSwitchValue>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UAkSwitchValue_Statics::ClassParams = {
		&UAkSwitchValue::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UAkSwitchValue_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UAkSwitchValue_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UAkSwitchValue()
	{
		if (!Z_Registration_Info_UClass_UAkSwitchValue.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAkSwitchValue.OuterSingleton, Z_Construct_UClass_UAkSwitchValue_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UAkSwitchValue.OuterSingleton;
	}
	template<> AKAUDIO_API UClass* StaticClass<UAkSwitchValue>()
	{
		return UAkSwitchValue::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UAkSwitchValue);
	IMPLEMENT_FSTRUCTUREDARCHIVE_SERIALIZER(UAkSwitchValue)
	struct Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSwitchValue_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSwitchValue_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UAkSwitchValue, UAkSwitchValue::StaticClass, TEXT("UAkSwitchValue"), &Z_Registration_Info_UClass_UAkSwitchValue, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAkSwitchValue), 1361132749U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSwitchValue_h_2773286399(TEXT("/Script/AkAudio"),
		Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSwitchValue_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_AkAudio_Classes_AkSwitchValue_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
