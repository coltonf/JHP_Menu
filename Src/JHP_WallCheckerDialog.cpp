#include	"JHP_Utilities.h"
#include	"JHP_WallChecker.hpp"

// -----------------------------------------------------------------------------
// MAIN WALL CHECKER DIALOG BOX
// -----------------------------------------------------------------------------
#define OKButtonId				1
#define CancelButtonId			2 
#define AngleListBoxId			4
#define PickButtonId			5
#define RemButtonId				6
#define PrecisionSlidId			8
#define ReserveTextId			14
#define ResFreeIconId			15
#define ResIconId				16
#define ResLockedIconId			17
#define ReserveButtonId			18
#define DescriptionId			19
#define MasterOnId				21
#define MasterOffId				22

#define ClassAndPropGuid	(ACAPI_TeamworkControl_FindLockableObjectSet ("ClassificationsAndProperties"))
#define GraphicOverrideGuid	(ACAPI_TeamworkControl_FindLockableObjectSet ("GraphicOverrides")) //CANT FIGURE OUT WHAT THE STRING IS TO RESERVE GRAPHIC OVERRIDE COMBOS

GS::UniString standardPrecision = "Precision is set to standard.\nThis is useful for general wood construction.\nWalls of 1/8\" dimensions will be highlighted.\nWalls less precise than 1/8\" inch are always highlighted.";
GS::UniString finePrecision = "Precision is set to fine.\nThis is useful for precise wood construction.\nWalls of 1/8\" and 1/4\" dimensions will be highlighted.\nWalls less precise than 1/8\" inch are always highlighted.";
GS::UniString decimalPrecision = "Precision is set to decimal.\nThis is useful for metal construction.\nOnly walls less precise than 1/8\" will be highlighted.";

void JHP_EnableWallCheckerControls(short dialID)
{
	DGEnableItem(dialID, AngleListBoxId);
	DGEnableItem(dialID, PrecisionSlidId);
	DGEnableItem(dialID, PickButtonId);
	DGEnableItem(dialID, RemButtonId);
	DGEnableItem(dialID, MasterOnId);
	DGEnableItem(dialID, MasterOffId);
}

void JHP_DisableWallCheckerControls(short dialID)
{
	DGDisableItem(dialID, AngleListBoxId);
	DGDisableItem(dialID, PrecisionSlidId);
	DGDisableItem(dialID, PickButtonId);
	DGDisableItem(dialID, RemButtonId);
	DGDisableItem(dialID, MasterOnId);
	DGDisableItem(dialID, MasterOffId);
}

void JHP_SetReservedIconText(short dialId, API_LockableStatus lock, GS::UniString lockedByMsg)
{
	switch (lock)
	{
	case APILockableStatus_Free:
		DGSetItemText(dialId, ReserveTextId, "Free to Reserve");
		DGSetItemText(dialId, ReserveButtonId, "Reserve");
		DGShowItem(dialId, ReserveButtonId);
		DGHideItem(dialId, ResLockedIconId);
		DGHideItem(dialId, ResIconId);
		DGShowItem(dialId, ResFreeIconId);
		break;
	case APILockableStatus_Editable:
		DGSetItemText(dialId, ReserveTextId, "Reserved");
		DGSetItemText(dialId, ReserveButtonId, "Release");
		DGShowItem(dialId, ReserveButtonId);
		DGHideItem(dialId, ResLockedIconId);
		DGShowItem(dialId, ResIconId);
		DGHideItem(dialId, ResFreeIconId);
		break;
	case APILockableStatus_Locked:
		DGSetItemText(dialId, ReserveTextId, "Locked By Other");
		if (lockedByMsg != "None")
		{
			DGSetItemText(dialId, ReserveTextId, lockedByMsg);
		}
		DGHideItem(dialId, ReserveButtonId);
		DGShowItem(dialId, ResLockedIconId);
		DGHideItem(dialId, ResIconId);
		DGHideItem(dialId, ResFreeIconId);
		break;
	case APILockableStatus_NotAvailable:
		DGSetItemText(dialId, ReserveTextId, "Unavailable");
		DGHideItem(dialId, ReserveButtonId);
		DGShowItem(dialId, ResLockedIconId);
		DGHideItem(dialId, ResIconId);
		DGHideItem(dialId, ResFreeIconId);
		break;
	case APILockableStatus_NotExist:
		DGSetItemText(dialId, ReserveTextId, "Local Project");
		DGHideItem(dialId, ReserveButtonId);
		DGHideItem(dialId, ResLockedIconId);
		DGShowItem(dialId, ResIconId);
		DGHideItem(dialId, ResFreeIconId);
		break;
	}

}

void JHP_ResolveControlVisibility(short dialId, bool master, API_LockableStatus lock)
{
	if (master == true) { DGHideItem(dialId, MasterOffId); }
	if (master == false) { DGHideItem(dialId, MasterOnId); }

	switch (lock)
	{
	case APILockableStatus_Editable: //Reserved
	{
		switch (master)
		{
		case true: //off
			JHP_DisableWallCheckerControls(dialId);
			DGEnableItem(dialId, MasterOnId);
			break;

		case false: //on
			JHP_EnableWallCheckerControls(dialId);
			break;
		}
		break;
	}
	case APILockableStatus_Free: //Able to be reserved.
	{
		JHP_DisableWallCheckerControls(dialId);
		break;
	}
	case APILockableStatus_Locked: //locked by other
	{
		JHP_DisableWallCheckerControls(dialId);
		break;
	}
	case APILockableStatus_NotAvailable: //server not available
	{
		JHP_DisableWallCheckerControls(dialId);
		break;
	}
	case APILockableStatus_NotExist: //not teamwork
	{
		switch (master)
		{
		case true: //off
			JHP_DisableWallCheckerControls(dialId);
			DGEnableItem(dialId, MasterOnId);
			break;

		case false: //on
			JHP_EnableWallCheckerControls(dialId);
			break;
		}
	}
	}
}


short DGCALLBACK WallCheckerDialogCallback(short message, short dialId, short item, DGUserData, DGMessageData)
{

	switch (message) {
	case DG_MSG_INIT:
	{
		//CHECK THE PROPERTIES AND CLASSIFICATIONS FOR LOCKS BEFORE EDITS
		GS::PagedArray<GS::UniString> conflicts;
		API_LockableStatus propLockStatus = ACAPI_TeamworkControl_GetLockableStatus(ClassAndPropGuid, &conflicts);
		GS::UniString lockedMsg = "None";
		if (propLockStatus == APILockableStatus_Locked && !conflicts.IsEmpty())
		{
			lockedMsg = "Locked by " + conflicts[0];
		}

		//CHECK THAT THE BYPASS ANGLES AND PRECISION DEFINITIONS EXIST AND STORE REFERENCE
		GS::Array<API_PropertyDefinition> definitions;
		API_PropertyDefinition bypassAngleDefinition;
		API_PropertyDefinition toleranceDefinition;
		API_PropertyDefinition bypassDefinition;

		if (ACAPI_Property_GetPropertyDefinitions(JHP_GetorCreatePropertyGroup("API AUDITS"), definitions) == NoError)
		{
			for (UInt32 i = 0; i < definitions.GetSize(); ++i)
			{
				if (definitions[i].name == "API Wall Bypass") { bypassDefinition = definitions[i]; }
				if (definitions[i].name == "API Wall Bypass Angles") { bypassAngleDefinition = definitions[i]; }
				if (definitions[i].name == "API Wall Tolerance") { toleranceDefinition = definitions[i]; }
			}
		}

		//SET RESERVED ICON STATUS
		JHP_SetReservedIconText(dialId, propLockStatus, lockedMsg);

		//DISABLE/ENABLE CONTROLS AS NEEDED
		JHP_ResolveControlVisibility(dialId, bypassDefinition.defaultValue.basicValue.singleVariant.variant.boolValue, propLockStatus);

		//CLEAR ALL ITEMS
		DGListDeleteItem(dialId, AngleListBoxId, DG_ALL_ITEMS);

		//GET DEFAULT VALUES OF THE PROPERTY DEFINITION
		GS::Array<GS::UniString> defaultValues = JHP_Split(bypassAngleDefinition.defaultValue.basicValue.singleVariant.variant.uniStringValue, ':');

		//BUILD THE LIST FROM THE DEFAULT VALUE OPTION SET ENTRIES
		for (UInt32 i = 0; i < defaultValues.GetSize(); ++i)
		{
			DGListInsertItem(dialId, AngleListBoxId, DG_LIST_BOTTOM);
			GS::UniString itemString = defaultValues[i];
			itemString.DeleteFirst();
			GS::UIndex decimalPosition = itemString.FindFirst('.');
			GS::UniString decimalSubstring = itemString.GetSubstring(decimalPosition, MaxUIndex);
			if (decimalSubstring == ".0000") { itemString = itemString.GetSubstring(0, decimalPosition); }
			DGListSetItemText(dialId, AngleListBoxId, DG_LIST_BOTTOM, itemString.ToCStr().Get());
		}

		//SET THE SLIDER TO THE CURRENTLY SELECTED PRECISION
		GS::Int32 sliderValue = 1;
		if (toleranceDefinition.defaultValue.basicValue.singleVariant.variant.uniStringValue == "Decimal")
		{
			sliderValue = 0;
			DGSetItemText(dialId, DescriptionId, decimalPrecision);
		}
		if (toleranceDefinition.defaultValue.basicValue.singleVariant.variant.uniStringValue == "Standard")
		{
			sliderValue = 1;
			DGSetItemText(dialId, DescriptionId, standardPrecision);
		}
		if (toleranceDefinition.defaultValue.basicValue.singleVariant.variant.uniStringValue == "Fine")
		{
			sliderValue = 2;
			DGSetItemText(dialId, DescriptionId, finePrecision);
		}
		DGSetItemValLong(dialId, PrecisionSlidId, sliderValue);
	}
	break;
	// /DG_MSG_INIT

	case DG_MSG_CLICK: //START CLICK EVENT
	{
		//CHECK THE PROPERTIES AND CLASSIFICATIONS FOR LOCKS BEFORE EDITS
		GS::PagedArray<GS::UniString> conflicts;
		API_LockableStatus propLockStatus = ACAPI_TeamworkControl_GetLockableStatus(ClassAndPropGuid, &conflicts);

		//CHECK THAT THE BYPASS ANGLES AND PRECISION DEFINITIONS EXIST AND STORE REFERENCE
		GS::Array<API_PropertyDefinition> definitions;
		API_PropertyDefinition bypassAngleDefinition;
		API_PropertyDefinition bypassDefinition;

		if (ACAPI_Property_GetPropertyDefinitions(JHP_GetorCreatePropertyGroup("API AUDITS"), definitions) == NoError)
		{
			for (UInt32 i = 0; i < definitions.GetSize(); ++i)
			{
				if (definitions[i].name == "API Wall Bypass") { bypassDefinition = definitions[i]; }
				if (definitions[i].name == "API Wall Bypass Angles") { bypassAngleDefinition = definitions[i]; }
			}
		}

		switch (item) {
		case CancelButtonId:
		case OKButtonId:
			return item;

			//Close dialog and handle in closing call
		case ReserveButtonId:
		case PickButtonId:
			switch (propLockStatus)
			{
			case APILockableStatus_Editable:
			case APILockableStatus_Free:
			case APILockableStatus_NotExist:
				return item; //close the dialog...
			}

			break;

		case RemButtonId:
		{
			short listItem = DGListGetSelected(dialId, AngleListBoxId, 0);
			if (listItem > 0)
			{
				//FORMAT ANGLE TO TEST AGAINST STORED STRING ANGLES
				GS::UniString angle = DGListGetItemText(dialId, AngleListBoxId, listItem);
				if (!angle.Contains('.')) { angle += ".0000"; }
				angle.Insert(0, ':');

				GS::Array<GS::UniString> bypassAngles = JHP_Split(bypassAngleDefinition.defaultValue.basicValue.singleVariant.variant.uniStringValue, ':');

				for (UInt32 i = 0; i < bypassAngles.GetSize(); ++i)
				{
					if (bypassAngles[i] == angle)
					{
						bypassAngles.Delete(i);
						bypassAngleDefinition.defaultValue.basicValue.singleVariant.variant.uniStringValue = JHP_Join(bypassAngles, ':');
						if (ACAPI_Property_ChangePropertyDefinition(bypassAngleDefinition) == NoError)
						{
							DGListDeleteItem(dialId, AngleListBoxId, listItem);
						}
					}
				}
			}
		}
		break;

		case MasterOnId:
		{
			bypassDefinition.defaultValue.basicValue.singleVariant.variant.boolValue = false;
			if (ACAPI_Property_ChangePropertyDefinition(bypassDefinition) == NoError)
			{
				DGHideItem(dialId, MasterOnId);
				DGShowItem(dialId, MasterOffId);
				JHP_EnableWallCheckerControls(dialId);
			}
		}
		break;

		case MasterOffId:
		{
			bypassDefinition.defaultValue.basicValue.singleVariant.variant.boolValue = true;
			if (ACAPI_Property_ChangePropertyDefinition(bypassDefinition) == NoError)
			{
				DGHideItem(dialId, MasterOffId);
				DGShowItem(dialId, MasterOnId);
				JHP_DisableWallCheckerControls(dialId);
				DGEnableItem(dialId, MasterOnId);
			}
		}
		break;

		}
		break;
		// /DG_MSG_CLICK;
	}

	case DG_MSG_CHANGE:
	{


		switch (item)
		{
		case PrecisionSlidId:

			//CHECK THAT THE BYPASS ANGLES AND PRECISION DEFINITIONS EXIST AND STORE REFERENCE
			GS::Array<API_PropertyDefinition> definitions;
			API_PropertyDefinition toleranceDefinition;

			if (ACAPI_Property_GetPropertyDefinitions(JHP_GetorCreatePropertyGroup("API AUDITS"), definitions) == NoError)
			{
				for (UInt32 i = 0; i < definitions.GetSize(); ++i)
				{
					if (definitions[i].name == "API Wall Tolerance") { toleranceDefinition = definitions[i]; }
				}
			}

			GS::UInt32 sliderValue = DGGetItemValLong(dialId, PrecisionSlidId);
			GS::UniString sliderString = "";
			switch (sliderValue)
			{
			case 0:
				sliderString = "Decimal";
				DGSetItemText(dialId, DescriptionId, decimalPrecision);
				break;
			case 1:
				sliderString = "Standard";
				DGSetItemText(dialId, DescriptionId, standardPrecision);
				break;
			case 2:
				sliderString = "Fine";
				DGSetItemText(dialId, DescriptionId, finePrecision);
				break;
			}
			toleranceDefinition.defaultValue.basicValue.singleVariant.variant.uniStringValue = sliderString;
			ACAPI_Property_ChangePropertyDefinition(toleranceDefinition);

			break;
		}

		// /DG_MSG_CHANGE;
	}

	//CALLED WHEN THE DIALOG IS CLOSING
	case DG_MSG_CLOSE:
	{

		//CHECK THE PROPERTIES AND CLASSIFICATIONS FOR LOCKS BEFORE EDITS
		GS::PagedArray<GS::UniString> conflicts;
		API_LockableStatus propLockStatus = ACAPI_TeamworkControl_GetLockableStatus(ClassAndPropGuid, &conflicts);

		//CHECK THAT THE BYPASS ANGLES AND PRECISION DEFINITIONS EXIST AND STORE REFERENCE
		GS::Array<API_PropertyDefinition> definitions;
		API_PropertyDefinition bypassAngleDefinition;

		if (ACAPI_Property_GetPropertyDefinitions(JHP_GetorCreatePropertyGroup("API AUDITS"), definitions) == NoError)
		{
			for (UInt32 i = 0; i < definitions.GetSize(); ++i)
			{
				if (definitions[i].name == "API Wall Bypass Angles") { bypassAngleDefinition = definitions[i]; }
			}
		}

		switch (item)
		{

		case ReserveButtonId:

			switch (propLockStatus)
			{
			case APILockableStatus_Editable:
				//release the properties
				ACAPI_TeamworkControl_ReleaseLockable(ClassAndPropGuid);
				break;
			case APILockableStatus_Free:
				//reserve the properties.
				ACAPI_TeamworkControl_ReserveLockable(ClassAndPropGuid);
				break;
			}

			//reopen the dialog...
			DGModalDialog(ACAPI_GetOwnResModule(), 32600, ACAPI_GetOwnResModule(), WallCheckerDialogCallback, 0);

			break;

		case PickButtonId:

			GS::UniString angle = "Err";

			API_Neig theNeig;
			BNClear(theNeig);

			//DIALOG IS CLOSED, MAKE USER PICK A WALL FOR ANGLE ADDITION

			if (ClickAnElem("Click an element:", API_WallID, &theNeig))
			{
				GS::Array<API_PropertyDefinition> defs;

				if (ACAPI_Element_GetPropertyDefinitions(theNeig.guid, API_PropertyDefinitionFilter_UserDefined, defs) == NoError)
				{
					for (UInt32 i = 0; i < defs.GetSize(); ++i)
					{
						if (defs[i].name == "API Wall Angle")
						{
							API_Property prop;
							if (ACAPI_Element_GetPropertyValue(theNeig.guid, defs[i].guid, prop) == NoError)
							{

								angle = prop.value.singleVariant.variant.uniStringValue;
								if (angle == "0.0000" || angle == "90.0000" || angle == "180.0000") { break; } //dont add ortho angles, we are checking those elsewhere

								//GET SUPPLEMENTARY ANGLE BEFORE APPENDING DELIMETER ON ANGLE
								double supplementaryAngleVal;
								if (GS::UniStringToValue(angle, supplementaryAngleVal))
								{
									supplementaryAngleVal = JHP_GetSupplementaryAngle(supplementaryAngleVal);
								}

								//FORMAT THE TWO ANGLES FOR ADDING TO STRING
								angle.Insert(0, ':');
								GS::UniString supplementaryAngle = ':' + JHP_AngleToString(supplementaryAngleVal);

								GS::Array<GS::UniString> bypassAngles = JHP_Split(bypassAngleDefinition.defaultValue.basicValue.singleVariant.variant.uniStringValue, ':');

								//ONLY ADD THESE IF THEY DONT EXIST ALREADY
								if (!bypassAngles.Contains(angle)) { bypassAngles.Push(angle); }
								if (!bypassAngles.Contains(supplementaryAngle)) { bypassAngles.Push(supplementaryAngle); }

								//FINALLY, SET THE DEFINITION TO BE CHANGED
								bypassAngleDefinition.defaultValue.basicValue.singleVariant.variant.uniStringValue = JHP_Join(bypassAngles, ':');
								ACAPI_Property_ChangePropertyDefinition(bypassAngleDefinition);
							}
						}
					}
				}
			}

			//Reopen dialog...
			DGModalDialog(ACAPI_GetOwnResModule(), 32600, ACAPI_GetOwnResModule(), WallCheckerDialogCallback, 0);

			break;
			// /DG_MSG_CLOSE;
		}
	}

	break;
	}
	return 0;
}		// ManagerDialogCallback

#undef OKButtonId				
#undef CancelButtonId			 
#undef AngleListBoxId			
#undef PickButtonId			
#undef RemButtonId				
#undef PrecisionSlidId			
#undef ReserveTextId			
#undef ResFreeIconId			
#undef ResIconId				
#undef ResLockedIconId			
#undef ReserveButtonId			
#undef DescriptionId			
#undef MasterOnId				
#undef MasterOffId		

// -----------------------------------------------------------------------------
// WALL CHECKER SETUP DIALOG BOX
// -----------------------------------------------------------------------------

#define ImportButtonId			1
#define CancelButtonId			2
#define DescriptionId			3

short DGCALLBACK WallCheckerSetupDialogCallback(short message, short dialId, short item, DGUserData, DGMessageData)
{
	switch (message) {

	case DG_MSG_INIT:
	{
		GS::UniString setupMessage = "The plugin version is newer than the project plugin version, or this is the first time setup."
			"\n\n The plugin needs to import necessary properties and override rules to function correctly."
			"\n\n Please reserve both Properties and Graphic Overrides to continue."
			"\n\n Press Import to attempt to import necessary updates.";
		DGSetItemText(dialId, DescriptionId, setupMessage);
	}
	break;
	case DG_MSG_CLICK:
	{
		switch (item)
		{
		case CancelButtonId:
		case ImportButtonId:
			return item;

		}

	}
	break;
	case DG_MSG_CLOSE:
	{
		switch (item)
		{
		case ImportButtonId:

			if (JHP_ImportProperties(XMLPropertySet::WallCheckerProperties) == NoError)
			{
				if (JHP_WallChecker_ImportRules() == NoError)
				{

					if (JHP_SyncProjectPluginVersion() == NoError)
					{
						ACAPI_WriteReport("Import successful.\n\nAll walls will be highlighted until they are initially reserved and checked. Please Release all walls, and reserve all walls again.", true);
					}
					else
					{
						ACAPI_WriteReport("Please reserve Properties and Graphic Overrides and reopen the Wall Checker.", true);
					}

				}
				else
				{
					ACAPI_WriteReport("Graphic Override import failed.\n\nEnsure that the Properties and Graphic Overrides are reserved and retry.", true);
				}
			}
			else
			{
				ACAPI_WriteReport("Properties import failed.\n\nEnsure that the Properties and Graphic Overrides are reserved and retry.", true);
			}

			break;
		case CancelButtonId:

			break;
		}
	}
	break;
	}
	return 0;
}

#undef ImportButtonId			
#undef CancelButtonId						
#undef DescriptionId				