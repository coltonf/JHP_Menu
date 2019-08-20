// *****************************************************************************
// Source code for 'JHP Menu' Add-On
// API Development Kit 22
//
// Started on 07/18/2019 at 1:13pm by CFranklin
//
// *****************************************************************************

#include "JHP_Utilities.h"


bool JHP_VersionUpToDate(void)
{
	GS::Array<API_PropertyDefinition> versionDefinitions;
	API_PropertyDefinition versionDefinition;
	versionDefinition.guid = APINULLGuid;
	if (ACAPI_Property_GetPropertyDefinitions(JHP_GetorCreatePropertyGroup("API"), versionDefinitions) == NoError)
	{
		for (UInt32 i = 0; i < versionDefinitions.GetSize(); ++i)
		{
			if (versionDefinitions[i].name == "API Plugin Version")
			{
				versionDefinition = versionDefinitions[i];
			}
		}
	}
	if (versionDefinition.guid == APINULLGuid || versionDefinition.defaultValue.basicValue.singleVariant.variant.uniStringValue != _JHPMENU_VERSION)
	{
		//Version mismatch... do updates!
		return false;
	}
	return true;
}

GSErrCode JHP_SyncProjectPluginVersion (void)
{
	GSErrCode err = NoError;

	err = JHP_CreatePropertyDefinition(JHP_GetorCreatePropertyGroup("API"), "API Plugin Version", API_PropertyStringValueType);
	if (err == APIERR_NAMEALREADYUSED) { err = NoError; }

	GS::Array<API_PropertyDefinition> versionDefinitions;
	API_PropertyDefinition versionDefinition;
	versionDefinition.guid = APINULLGuid;
	if (ACAPI_Property_GetPropertyDefinitions(JHP_GetorCreatePropertyGroup("API"), versionDefinitions) == NoError)
	{
		for (UInt32 i = 0; i < versionDefinitions.GetSize(); ++i)
		{
			if (versionDefinitions[i].name == "API Plugin Version")
			{
				versionDefinition = versionDefinitions[i];
			}
		}
	}

	versionDefinition.defaultValue.basicValue.singleVariant.variant.uniStringValue = _JHPMENU_VERSION;
	err = ACAPI_Property_ChangePropertyDefinition(versionDefinition);
	
	return err;
}