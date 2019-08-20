// *****************************************************************************
// Source code for 'JHP Menu' Add-On
// API Development Kit 22
//
// Started on 07/18/2019 at 1:13pm by CFranklin
//
// *****************************************************************************

#include "JHP_Utilities.h"

// -----------------------------------------------------------------------------
// Utility functions for dealing with properties, groups, and definitions
// -----------------------------------------------------------------------------

GSErrCode JHP_ImportProperties(XMLPropertySet properties)
{
	return ACAPI_Property_Import(JHP_GetXMLProperties(properties), API_ReplaceConflictingProperties);
}

//Creates or returns existing group guid of given name, returns APINULLGuid if fails.
API_Guid JHP_GetorCreatePropertyGroup(const char* name)
{
	API_PropertyGroup group;
	group.guid = APINULLGuid;
	group.name = name;

	if (ACAPI_Property_CreatePropertyGroup(group) == APIERR_NAMEALREADYUSED)
	{
		GS::Array<API_PropertyGroup> groups;
		if (ACAPI_Property_GetPropertyGroups(groups) == NoError)
		{
			for (UInt32 i = 0; i < groups.GetSize(); ++i)
			{
				if (groups[i].name == name)
				{
					return groups[i].guid;
				}
			}
		}
	}
	return group.guid;
}

GS::Array<API_Guid> JHP_GetClassificationDefaults(API_ElemTypeID id, API_ElemVariationID varid)

{
	GS::Array<API_Guid> classificationItems;
	GS::Array<GS::Pair<API_Guid, API_Guid>> classSystemItemPairs;
	if (ACAPI_Element_GetClassificationItemsDefault(id, varid, classSystemItemPairs) == NoError)
	{
		for (UIndex i = 0; i < classSystemItemPairs.GetSize(); ++i)
		{
			classificationItems.Push(classSystemItemPairs[i].second);
		}
	}
	return classificationItems;
}

//Create a empty generic property definition
API_PropertyDefinition JHP_EmptyPropertyDefinition(API_Guid groupGuid, const char* name)
{
	API_PropertyDefinition definition;
	definition.guid = APINULLGuid;
	definition.groupGuid = groupGuid;
	definition.name = name;
	definition.description = "Internally created property definition by the JHP plugin.";
	return definition;
}

//This will create a property definition at a default value for the different types
//Currently, list or enum/multienums not supported
GSErrCode JHP_CreatePropertyDefinition(API_Guid groupGuid, const char* name, API_VariantType type)
{
	GSErrCode err = NoError;
	GS::Array<API_PropertyDefinition> definitions;
	ACAPI_Property_GetPropertyDefinitions(groupGuid, definitions);

	for (UInt32 i = 0; i < definitions.GetSize(); ++i)
	{
		//Early out if the property already exists...
		if (definitions[i].name == name) { return err = APIERR_NAMEALREADYUSED; }
	}

	API_PropertyDefinition definition = JHP_EmptyPropertyDefinition(groupGuid, name);

	switch (type)
	{
	case API_PropertyIntegerValueType:
		definition.collectionType = API_PropertySingleCollectionType;
		definition.valueType = API_PropertyIntegerValueType;
		definition.measureType = API_PropertyDefaultMeasureType;
		definition.defaultValue.basicValue.singleVariant.variant.type = definition.valueType;
		definition.defaultValue.basicValue.singleVariant.variant.intValue = 0;
		//definition.availability = classifications;
		break;

	case API_PropertyRealValueType:
		definition.collectionType = API_PropertySingleCollectionType;
		definition.valueType = API_PropertyRealValueType;
		definition.measureType = API_PropertyDefaultMeasureType;
		definition.defaultValue.basicValue.singleVariant.variant.type = definition.valueType;
		definition.defaultValue.basicValue.singleVariant.variant.doubleValue = 0;
		//definition.availability = classifications;
		break;

	case API_PropertyBooleanValueType:
		definition.collectionType = API_PropertySingleCollectionType;
		definition.valueType = API_PropertyBooleanValueType;
		definition.measureType = API_PropertyDefaultMeasureType;
		definition.defaultValue.basicValue.singleVariant.variant.type = definition.valueType;
		definition.defaultValue.basicValue.singleVariant.variant.boolValue = false;
		//definition.availability = classifications;
		break;

	case API_PropertyStringValueType:
		definition.collectionType = API_PropertySingleCollectionType;
		definition.valueType = API_PropertyStringValueType;
		definition.measureType = API_PropertyDefaultMeasureType;
		definition.defaultValue.basicValue.singleVariant.variant.type = definition.valueType;
		definition.defaultValue.basicValue.singleVariant.variant.uniStringValue = "";
		//definition.availability = classifications;
		break;

	case API_PropertyUndefinedValueType:
	case API_PropertyGuidValueType:
	default: break;
	}

	err = ACAPI_Property_CreatePropertyDefinition(definition);
	return err;
}

