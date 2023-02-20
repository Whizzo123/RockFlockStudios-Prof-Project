/*******************************************************************************
The content of this file includes portions of the proprietary AUDIOKINETIC Wwise
Technology released in source code form as part of the game integration package.
The content of this file may not be used without valid licenses to the
AUDIOKINETIC Wwise Technology.
Note that the use of the game engine is subject to the Unreal(R) Engine End User
License Agreement at https://www.unrealengine.com/en-US/eula/unreal
 
License Usage
 
Licensees holding valid licenses to the AUDIOKINETIC Wwise Technology may use
this file in accordance with the end user license agreement provided with the
software or, alternatively, in accordance with the terms contained
in a written agreement between you and Audiokinetic Inc.
Copyright (c) 2022 Audiokinetic Inc.
*******************************************************************************/

#include "Wwise/Metadata/WwiseMetadataPluginInfo.h"
#include "Wwise/Metadata/WwiseMetadataLoader.h"

FWwiseMetadataPluginInfoAttributes::FWwiseMetadataPluginInfoAttributes(FWwiseMetadataLoader& Loader) :
	Platform(Loader.GetString(this, TEXT("Platform"))),
	BasePlatform(Loader.GetString(this, TEXT("BasePlatform")))
{
	Loader.LogParsed(TEXT("PluginInfoAttributes"));
}

FWwiseMetadataPluginInfo::FWwiseMetadataPluginInfo(FWwiseMetadataLoader& Loader) :
	FWwiseMetadataPluginInfoAttributes(Loader),
	PluginLibs(Loader.GetArray<FWwiseMetadataPluginLib>(this, TEXT("PluginLibs"))),
	FileHash(Loader.GetGuid(this, TEXT("FileHash")))
{
	Loader.LogParsed(TEXT("PluginInfo"));
}
