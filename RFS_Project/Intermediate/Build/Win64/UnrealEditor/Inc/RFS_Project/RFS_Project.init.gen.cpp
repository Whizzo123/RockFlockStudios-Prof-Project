// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeRFS_Project_init() {}
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_RFS_Project;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_RFS_Project()
	{
		if (!Z_Registration_Info_UPackage__Script_RFS_Project.OuterSingleton)
		{
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/RFS_Project",
				nullptr,
				0,
				PKG_CompiledIn | 0x00000000,
				0x8602EDCE,
				0x1F4841E3,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_RFS_Project.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_RFS_Project.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_RFS_Project(Z_Construct_UPackage__Script_RFS_Project, TEXT("/Script/RFS_Project"), Z_Registration_Info_UPackage__Script_RFS_Project, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0x8602EDCE, 0x1F4841E3));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
