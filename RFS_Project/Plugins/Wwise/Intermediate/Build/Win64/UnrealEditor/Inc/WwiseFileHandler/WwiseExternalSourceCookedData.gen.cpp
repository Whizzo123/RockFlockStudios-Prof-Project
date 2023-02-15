// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "WwiseFileHandler/Public/Wwise/CookedData/WwiseExternalSourceCookedData.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWwiseExternalSourceCookedData() {}
// Cross Module References
	WWISEFILEHANDLER_API UScriptStruct* Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData();
	UPackage* Z_Construct_UPackage__Script_WwiseFileHandler();
// End Cross Module References
	static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_WwiseExternalSourceCookedData;
class UScriptStruct* FWwiseExternalSourceCookedData::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_WwiseExternalSourceCookedData.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_WwiseExternalSourceCookedData.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData, Z_Construct_UPackage__Script_WwiseFileHandler(), TEXT("WwiseExternalSourceCookedData"));
	}
	return Z_Registration_Info_UScriptStruct_WwiseExternalSourceCookedData.OuterSingleton;
}
template<> WWISEFILEHANDLER_API UScriptStruct* StaticStruct<FWwiseExternalSourceCookedData>()
{
	return FWwiseExternalSourceCookedData::StaticStruct();
}
	struct Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics
	{
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[];
#endif
		static void* NewStructOps();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Cookie_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Cookie;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_DebugName_MetaData[];
#endif
		static const UECodeGen_Private::FNamePropertyParams NewProp_DebugName;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const UECodeGen_Private::FStructParams ReturnStructParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "ModuleRelativePath", "Public/Wwise/CookedData/WwiseExternalSourceCookedData.h" },
	};
#endif
	void* Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FWwiseExternalSourceCookedData>();
	}
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewProp_Cookie_MetaData[] = {
		{ "Category", "Wwise" },
		{ "Comment", "/**\n\x09 * @brief User-defined Cookie for the External Source\n\x09*/" },
		{ "ModuleRelativePath", "Public/Wwise/CookedData/WwiseExternalSourceCookedData.h" },
		{ "ToolTip", "@brief User-defined Cookie for the External Source" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewProp_Cookie = { "Cookie", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FWwiseExternalSourceCookedData, Cookie), METADATA_PARAMS(Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewProp_Cookie_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewProp_Cookie_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewProp_DebugName_MetaData[] = {
		{ "Category", "Wwise" },
		{ "Comment", "/**\n\x09 * @brief Optional debug name. Can be empty in release, contain the name, or the full path of the asset.\n\x09*/" },
		{ "ModuleRelativePath", "Public/Wwise/CookedData/WwiseExternalSourceCookedData.h" },
		{ "ToolTip", "@brief Optional debug name. Can be empty in release, contain the name, or the full path of the asset." },
	};
#endif
	const UECodeGen_Private::FNamePropertyParams Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewProp_DebugName = { "DebugName", nullptr, (EPropertyFlags)0x0010000000020815, UECodeGen_Private::EPropertyGenFlags::Name, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(FWwiseExternalSourceCookedData, DebugName), METADATA_PARAMS(Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewProp_DebugName_MetaData, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewProp_DebugName_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewProp_Cookie,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewProp_DebugName,
	};
	const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::ReturnStructParams = {
		(UObject* (*)())Z_Construct_UPackage__Script_WwiseFileHandler,
		nullptr,
		&NewStructOps,
		"WwiseExternalSourceCookedData",
		sizeof(FWwiseExternalSourceCookedData),
		alignof(FWwiseExternalSourceCookedData),
		Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::PropPointers,
		UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::PropPointers),
		RF_Public|RF_Transient|RF_MarkAsNative,
		EStructFlags(0x00000201),
		METADATA_PARAMS(Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::Struct_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::Struct_MetaDataParams))
	};
	UScriptStruct* Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData()
	{
		if (!Z_Registration_Info_UScriptStruct_WwiseExternalSourceCookedData.InnerSingleton)
		{
			UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_WwiseExternalSourceCookedData.InnerSingleton, Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::ReturnStructParams);
		}
		return Z_Registration_Info_UScriptStruct_WwiseExternalSourceCookedData.InnerSingleton;
	}
	struct Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_WwiseFileHandler_Public_Wwise_CookedData_WwiseExternalSourceCookedData_h_Statics
	{
		static const FStructRegisterCompiledInInfo ScriptStructInfo[];
	};
	const FStructRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_WwiseFileHandler_Public_Wwise_CookedData_WwiseExternalSourceCookedData_h_Statics::ScriptStructInfo[] = {
		{ FWwiseExternalSourceCookedData::StaticStruct, Z_Construct_UScriptStruct_FWwiseExternalSourceCookedData_Statics::NewStructOps, TEXT("WwiseExternalSourceCookedData"), &Z_Registration_Info_UScriptStruct_WwiseExternalSourceCookedData, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FWwiseExternalSourceCookedData), 1843187199U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_WwiseFileHandler_Public_Wwise_CookedData_WwiseExternalSourceCookedData_h_149382220(TEXT("/Script/WwiseFileHandler"),
		nullptr, 0,
		Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_WwiseFileHandler_Public_Wwise_CookedData_WwiseExternalSourceCookedData_h_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_RFS_Project_Plugins_Wwise_Source_WwiseFileHandler_Public_Wwise_CookedData_WwiseExternalSourceCookedData_h_Statics::ScriptStructInfo),
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
