// *****************************************************************************
// JHP_Menu.c
// Source code for 'JHP Menu' Add-On
// API Development Kit 22
//
// *****************************************************************************

#include "JHP_Utilities.h"

//Dialog includes
#include "JHP_WallCheckerDialog.hpp"


// -----------------------------------------------------------------------------
// Element event handler function
// -----------------------------------------------------------------------------
GSErrCode __ACENV_CALL NewElementEventHandler(const API_NotifyElementType* notifyElemType) // new element
{
	GSErrCode       err = NoError;
	API_Elem_Head	elemHead = notifyElemType->elemHead;
	API_ElemTypeID	elemType = elemHead.typeID;

	switch (elemType)
	{
	case API_WallID:
		err = ACAPI_Element_AttachObserver(&elemHead, 0);
		err = JHP_WallChecker_SetProperties(&elemHead);

		//case API_DrawingID:
			//err = JHP_SetExternalDrawingScale(&elemHead);
	}

	return err;
}   // ElementEventHandler

//Callbacks for elements changed that we are observing
GSErrCode __ACENV_CALL ElementChangedEventHandler(const API_NotifyElementType* notifyElemType)
{
	GSErrCode		err = NoError;
	API_Elem_Head	elemHead = notifyElemType->elemHead;
	API_ElemTypeID	elemType = elemHead.typeID;

	switch (elemType)
	{
	case API_WallID: err = JHP_WallChecker_SetProperties(&elemHead);
	}

	return err;
}

//Split logic from call below for clarity
GSErrCode ElementReservationChanged(API_Elem_Head* elemHead)
{
	GSErrCode		err = NoError;
	API_ElemTypeID	elemType = elemHead->typeID;

	switch (elemType)
	{
	case API_WallID:
		err = ACAPI_Element_AttachObserver(elemHead, 0);
		err = JHP_WallChecker_SetProperties(elemHead);
	}

	return err;
}

//Callbacks for revervations of objects
GSErrCode __ACENV_CALL ElementReservationChangeHandler(const GS::HashTable<API_Guid, short>& reserved, const GS::HashSet<API_Guid>& /*released*/, const GS::HashSet<API_Guid>& /*deleted*/)
{
	GSErrCode err = NoError;
	//See APIReservationChangeHandlerProc in docs.
	for (GS::HashTable<API_Guid, short>::ConstPairIterator it = reserved.EnumeratePairs(); it != nullptr; ++it)
	{
		API_Elem_Head elemHead;
		BNZeroMemory(&elemHead, sizeof(API_Elem_Head));
		elemHead.guid = *(it->key);
		if (ACAPI_Element_GetHeader(&elemHead) == NoError)
		{
			err = ElementReservationChanged(&elemHead);
		}
	}
	return err;
}


//Callbacks for project events, some of these dont seem to work...
GSErrCode __ACENV_CALL ProjectEventHandler(API_NotifyEventID notifID, Int32/*param*/)
{
	//char    msgStr[256];
	GSErrCode err = NoError;

	switch (notifID) {
	case APINotify_New:																	break;
	case APINotify_NewAndReset:															break;
	case APINotify_Open:                												break;
	case APINotify_PreSave:            /*CHCopyC("APINotify_PreSave", msgStr);*/	     break;
	case APINotify_Save:               /*CHCopyC("APINotify_Save", msgStr);*/            break;
	case APINotify_Close:              /*CHCopyC("APINotify_Close", msgStr);*/           break;
	case APINotify_Quit:               /*CHCopyC("APINotify_Quit", msgStr);*/            break;

	case APINotify_SendChanges:        /*CHCopyC("APINotify_SendChanges", msgStr);*/     break;
	case APINotify_ReceiveChanges:     /*CHCopyC("APINotify_ReceiveChanges", msgStr);*/  break;

	case APINotify_ChangeProjectDB:    /*CHCopyC("APINotify_ChangeProjectDB", msgStr);*/ break;
	case APINotify_ChangeWindow:       /*CHCopyC("APINotify_ChangeWindow", msgStr);*/    break;
	case APINotify_ChangeFloor:        /*CHCopyC("APINotify_ChangeFloor", msgStr);*/     break;
	case APINotify_ChangeLibrary:      /*CHCopyC("APINotify_ChangeLibrary", msgStr);*/   break;
	}
	return err;
}






// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Handles Menu commands
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

GSErrCode __ACENV_CALL MenuCommandHandler(const API_MenuParams* menuParams)
{
	return ACAPI_CallUndoableCommand("JHP Menu Command", [&]() -> GSErrCode {
		switch (menuParams->menuItemRef.menuResID) {
		case 32500: { /* TEXT */
			switch (menuParams->menuItemRef.itemIndex) {
			case 1:	JHP_TextToCase(JHP_Case::Upper);					break;
			case 2:	JHP_TextToCase(JHP_Case::Lower);					break;
			}
			break;
		}
		case 32501: { /* WALL CHECKER DIALOG */

			if (JHP_VersionUpToDate())
			{
				DGModalDialog(ACAPI_GetOwnResModule(), 32600, ACAPI_GetOwnResModule(), WallCheckerDialogCallback, 0);
			}
			else
			{
				DGModalDialog(ACAPI_GetOwnResModule(), 32650, ACAPI_GetOwnResModule(), WallCheckerSetupDialogCallback, 0);
			}
			

			break;
		}
		case 32502: { /* LINKS */
			switch (menuParams->menuItemRef.itemIndex) {
			case 1:			JHP_Open(JHP_Link::WEB_IBC);				break;
			case 2:			JHP_Open(JHP_Link::WEB_UL);					break;
			case 3:			JHP_Open(JHP_Link::PDF_FairHousing);		break;
			case 4:			JHP_Open(JHP_Link::PDF_CityofDallas);		break;
			default:													break;
			}
			break;
		}

		case 32503: { /* STANDARDS */
			switch (menuParams->menuItemRef.itemIndex) {
			case 1:			JHP_Open(JHP_Link::PDF_DesignManual);		break;
			case 2:			JHP_Open(JHP_Link::LOC_Standards);			break;
			case 3:			JHP_Open(JHP_Link::PDF_Dimensions101);		break;
			case 4:			JHP_Open(JHP_Link::LOC_Logos);				break;
			default:													break;
			}
			break;
		}
		case 32504: { /* OFFICE */
			switch (menuParams->menuItemRef.itemIndex) {
			case 1:			JHP_Open(JHP_Link::PDF_OCEPlotwave);		break;
			default:													break;
			}
			break;
		}

		case 32505: { /* DEV */
			switch (menuParams->menuItemRef.itemIndex) {
			case 1: {
				char message[100] = "User ";
				char* uname = (JHP_UserName());
				std::strcat(message, uname);
				if (CHCompareCStrings(uname, "CGilmer") == 0)
				{
					// std::strcat(message, " is a verified user.");
					JHP_Publish();
					break;
				}
				else
				{
					std::strcat(message, " is NOT a user.");
				}
				ShowMessage(message);
				break;
			}
			case 2: {
				char message[100] = "User ";
				char* uname = (JHP_UserName());
				std::strcat(message, uname);
				if (CHCompareCStrings(uname, "CGilmer") == 0)
				{
					// std::strcat(message, " is a verified user.");
					JHP_Entget();
					break;
				}
				else
				{
					std::strcat(message, " is NOT a verified user.");
				}
				ShowMessage(message);
				break;
			}
			}
			break;
		}

		case 32506: /* HELP */
		{
			GS::UniString aboutMsg = "JHP Menu plugin\n\nVersion: %d\n\nQuarter: %s";
			//GS::UniString chrisMsg = "Call Chris Gilmer at:\n\ncell:  214.789.1097\nextension:  605";
			switch (menuParams->menuItemRef.itemIndex) {
			case 1:		JHP_Open(JHP_Link::SLACK_Archicad);											break;
			case 2:		ACAPI_WriteReport(aboutMsg, true, _JHPMENU_ARCHVERSION, _JHPMENU_VERSION);	break;
			default:																				break;
			}
			break;
		}
		}
		return NoError;
	});
}
// MenuCommandHandler

// *****************************************************************************
//
// Required functions to register and initialize "JHP" menu
//
// *****************************************************************************

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// CheckEnvironment
//		Dependency definitions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

API_AddonType	__ACENV_CALL	CheckEnvironment(API_EnvirParams* envir)
{
	RSGetIndString(&envir->addOnInfo.name, 32000, 1, ACAPI_GetOwnResModule());
	RSGetIndString(&envir->addOnInfo.description, 32000, 2, ACAPI_GetOwnResModule());

	return APIAddon_Preload;
}
// CheckEnvironment




// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// RegisterInterface
//		Interface definitions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

GSErrCode __ACENV_CALL	RegisterInterface(void)
{
	GSErrCode err = NoError;
	err = ACAPI_Register_Menu(32500, 0, MenuCode_UserDef, MenuFlag_Default); /*Text*/
	err = ACAPI_Register_Menu(32501, 32600, MenuCode_UserDef, MenuFlag_SeparatorAfter); /*Selection*/
	err = ACAPI_Register_Menu(32502, 0, MenuCode_UserDef, MenuFlag_Default); /*Links*/
	err = ACAPI_Register_Menu(32503, 0, MenuCode_UserDef, MenuFlag_Default); /*Standards*/
	err = ACAPI_Register_Menu(32504, 0, MenuCode_UserDef, MenuFlag_SeparatorAfter); /*Office*/
	err = ACAPI_Register_Menu(32505, 0, MenuCode_UserDef, MenuFlag_Default); /*About*/
	err = ACAPI_Register_Menu(32506, 0, MenuCode_UserDef, MenuFlag_Default); /*DevTools*/

	return err;
}
// RegisterInterface


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Initialize
//		Called when the Add-On has been loaded into memory
//		to perform an operation
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//I dont think this gets called until a menu option is picked...
GSErrCode __ACENV_CALL	Initialize(void)
{
	GSErrCode err = NoError;

	err = ACAPI_Install_MenuHandler(32500, MenuCommandHandler); /*Text*/
	err = ACAPI_Install_MenuHandler(32501, MenuCommandHandler); /*Settings*/
	err = ACAPI_Install_MenuHandler(32502, MenuCommandHandler); /*Links*/
	err = ACAPI_Install_MenuHandler(32503, MenuCommandHandler); /*Standards*/
	err = ACAPI_Install_MenuHandler(32504, MenuCommandHandler); /*Office*/
	err = ACAPI_Install_MenuHandler(32505, MenuCommandHandler); /*DevTools*/
	err = ACAPI_Install_MenuHandler(32506, MenuCommandHandler); /*About*/


	err = ACAPI_Notify_CatchProjectEvent(API_AllProjectNotificationMask, ProjectEventHandler); //catch all project events
	//ADDED THIS TO CATCH ALL EVENTS OF NEW WALL
	API_ToolBoxItem  elemType_All = { API_ZombieElemID, (API_ElemVariationID)0, 0, 0 };
	err = ACAPI_Notify_CatchNewElement(&elemType_All, NewElementEventHandler); //new element, observe
	err = ACAPI_Notify_InstallElementObserver(ElementChangedEventHandler); //call function when observed element gets modified

	err = ACAPI_Notify_CatchElementReservationChange(ElementReservationChangeHandler);

	return err;
}
// Initialize


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FreeData
//		Called when the Add-On is going to be unloaded
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

GSErrCode __ACENV_CALL	FreeData(void)
{
	//return ReleaseAllObservedElements();
	return NoError;
}
// FreeData