// *****************************************************************************
// Source code for 'JHP Menu' Add-On
// API Development Kit 22
//
// Started on 07/18/2019 at 1:13pm by CFranklin
//
// *****************************************************************************

#include "JHP_Utilities.h"

// -----------------------------------------------------------------------------
// Audit walls and set properties of angles
// -----------------------------------------------------------------------------

bool JHP_WallChecker_PropertiesInitialized(void) //Returns true if all properties needed for wall checker to function exist and are correctly setup
{
	//Get or create the needed groups. We dont need to have reserved for this.
	API_Guid auditGroupGuid = JHP_GetorCreatePropertyGroup("API AUDITS"); 
	API_Guid wallGroupGuid = JHP_GetorCreatePropertyGroup("API WALLS");

	//Get all properties in these groups
	GS::Array<API_PropertyDefinition> wallDefinitions;
	GS::Array<API_PropertyDefinition> auditDefinitions;

	bool wallAngle = false;
	bool wallLength = false;
	bool wallBypass = false;
	bool wallBypassAngles = false;
	bool wallIsBypassAngle = false;
	bool wallIsOrthogonal = false;
	bool wallTolerance = false;

	//Iterate definitions and look for needed definitions
	if (ACAPI_Property_GetPropertyDefinitions(wallGroupGuid, wallDefinitions) == NoError)
	{
		for (UInt32 i = 0; i < wallDefinitions.GetSize(); ++i)
		{
			if (wallDefinitions[i].name == "API Wall Angle") { wallAngle = true; }
			if (wallDefinitions[i].name == "API Wall Length") { wallLength = true; }
		}
	}

	if (ACAPI_Property_GetPropertyDefinitions(auditGroupGuid, auditDefinitions) == NoError)
	{
		for (UInt32 i = 0; i < auditDefinitions.GetSize(); ++i)
		{
			if (auditDefinitions[i].name == "API Wall Bypass") { wallBypass = true; }
			if (auditDefinitions[i].name == "API Wall Bypass Angles") { wallBypassAngles = true; }
			if (auditDefinitions[i].name == "API Wall Is Bypass Angle") { wallIsBypassAngle = true; }
			if (auditDefinitions[i].name == "API Wall Is Orthogonal") { wallIsOrthogonal = true; }
			if (auditDefinitions[i].name == "API Wall Tolerance") { wallTolerance = true; }
		}
	}

	return wallAngle && wallLength && wallBypass && wallBypassAngles && wallIsBypassAngle && wallIsOrthogonal && wallTolerance;
}




//This will add a property for angle and length to all walls, and assign those properties
GSErrCode JHP_WallChecker_SetProperties(API_Elem_Head* elemHead)
{
	GSErrCode err = NoError;

	//Get element data
	API_Element elem;
	elem.header.guid = elemHead->guid;
	err = ACAPI_Element_Get(&elem);
	if (err != NoError) { return err; }

	//Get all our definitions of the current object, dont rely on storing our own guids
	GS::Array<API_PropertyDefinition> definitions;
	err = ACAPI_Element_GetPropertyDefinitions(elem.header.guid, API_PropertyDefinitionFilter_UserDefined, definitions);
	
	//Loop through all the properties of the wall and assign values to the ones we just created
	//Doing it this way wont error/crash if we fail to add the properties
	if (err == NoError)
	{
		//Assign calculated values to respective properties (local, still needs to be pushed to elements)
		for (UInt32 i = 0; i < definitions.GetSize(); ++i)
		{
			GS::Array<API_Property> properties;

			if (definitions[i].name == "API Wall Angle")
			{
				API_Property prop = {};
				prop.definition = definitions[i];

				prop.isDefault = false;
				prop.value.singleVariant.variant.type = API_PropertyStringValueType;
				prop.value.singleVariant.variant.uniStringValue = JHP_AngleToString(JHP_GetAngle(elem.wall.begC, elem.wall.endC));

				properties.Push(prop);
			}

			if (definitions[i].name == "API Wall Length")
			{
				API_Property prop = {};
				prop.definition = definitions[i];

				prop.isDefault = false;
				prop.value.singleVariant.variant.type = API_PropertyStringValueType;
				prop.value.singleVariant.variant.uniStringValue = JHP_LengthToString(JHP_GetLength(elem.wall.begC, elem.wall.endC));

				properties.Push(prop);
			}

			//Finally, push our altered properties back to the elements
			err = ACAPI_Element_SetProperties(elem.header.guid, properties);
		}
	}

	return err;
}