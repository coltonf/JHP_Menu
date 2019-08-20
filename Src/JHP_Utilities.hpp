#pragma once
// *****************************************************************************
// JHP_Utilities.h
// JHP Utilities for JHP_Menu Addon
// API Development Kit 21; Mac/Win
//
// Namespaces:		Contact person:
//		-None-
//
// [SG compatible] - Yes
// *****************************************************************************


//General
#include	"APIEnvir.h"
#include	"ACAPinc.h"		// also includes APIdefs.h
#include	"APICommon.h"

//For Devtools
#include "windows.h"
#include "Lmcons.h"
#include "iostream"

//For Links
#include "shellapi.h"
#include "shlobj.h"
#include "shtypes.h"



#ifndef	_JHP_UTILITIES_H_
#define	_JHP_UTILITIES_H_
#define NOMINMAX

void JHP_MsgBox(const char* str, ...);
void JHP_Msg(std::string x);
void ShowMessage(char strMenuPick[]);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// JHP Menu Choices
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



// ~~~~~~~~~~~~~~~
// Text >
// ~~~~~~~~~~~~~~~

/* -- Constants ------------------------------- */

enum class JHP_Case
{
	Smart = 2,
	Upper = 1,
	Lower = 0
};

///<summary> Sets the selected text to the desired casing. 
///Asks user for new selection if invalid/missing. </summary>
GSErrCode JHP_TextToCase (JHP_Case textCase);

// ~~~~~~~~~~~~~~~
// Dimension >
// ~~~~~~~~~~~~~~~
GSErrCode DimsTo256(void);

// ~~~~~~~~~~~~~~~
// Links >
// ~~~~~~~~~~~~~~~

enum class JHP_Link
{
	//PDF Links
	PDF_DesignManual = 0,
	PDF_FairHousing = 1, 
	PDF_CityofDallas = 2, 
	PDF_OCEPlotwave = 3, 
	PDF_Dimensions101 = 4,

	//Web Links
	WEB_IBC = 5, 
	WEB_UL = 6,

	//File Locations (over 1000!)
	LOC_Logos = 1001,
	LOC_Standards = 1002,
};

///<summary> 
///Returns the correctly formatted path to the provided link enum. 
///</summary>
const char* JHP_Links(JHP_Link link);

///<summary> 
///Opens the provided link without safety. 
///exflag = "open" for files/links and "explore" for locations.
///</summary>
GSErrCode JHP_Open(const char* exflag, const char* link);

///<summary> 
///Opens the provided link. 
///</summary>
GSErrCode JHP_Open(JHP_Link link);

// ~~~~~~~~~~~~~~~
// Dev Tools >
// ~~~~~~~~~~~~~~~
char* JHP_UserName(void);
void JHP_Publish();
std::string ExtractFileName(const std::string& fullPath);
GSErrCode JHP_GetProp(const API_Guid& guid);
GSErrCode JHP_Entget(void);

///<summary> testing </summary>
///<param name = "i"> test </param>
int test(int i) { return i; }


/* -- Selection Utilities ------------------------------- */

///<summary> 
///Set pointer to all selected neigs;.
///If (newSelectionIfInvalid == true), ask for new selection. 
///</summary>
GSErrCode JHP_GetSelection(API_Neig*** selNeigs, bool newSelectionIfInvalid = false);

///<summary> 
///Set pointer to single selected neig. 
///If (newSelectionIfInvalid == true), ask for new selection. 
///</summary>
GSErrCode JHP_GetSelection(API_Neig* theNeig, bool newSelectionIfInvalid = false); 

///<summary> 
///Returns the type of the selected neig. 
///If (newSelectionIfInvalid == true), asks for new selection when invalid. 
///</summary>
API_ElemTypeID JHP_GetSelectionType(bool newSelectionIfInvalid = false); 

///<summary> 
///Selects all elements of type "id" on layer "layer" on the active floor. 
///</summary>
///<param name="id"> test </param>
GSErrCode JHP_SelectElements(API_ElemTypeID id, const char* layer); 

///<summary> 
///Selects all elements of type and layer matching the currently selected element. 
///</summary>
GSErrCode JHP_SelectSimilar(void);

GSErrCode SelectExteriorWalls();

/* -- Attribute Utilities ------------------------------- */

///<summary> Gets layer attributes by name, returns short for use in testing against element.header.layer </summary>
short JHP_GetLayerAttributeIndex(const char* layerName); 


#endif