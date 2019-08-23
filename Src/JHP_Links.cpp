#include "JHP_Utilities.h"

// -----------------------------------------------------------------------------
// Links to external documentation - online, .pdf file, etc.
// -----------------------------------------------------------------------------

///TO ADD A NEW LINK, OPEN THE JHP_UTILITIES.H FILE AND ADD A NAME FOR THE LINK INTO
///THE ENUM JHP_LINK. FOR CONVENIENCE, THE ENUM VALUES FOR LOCATIONS IS 1000 HIGHER THAN
///WEB OR PDF/FILE LINKS, SUCH THAT JHP_OPENLINK CAN DECIDE WHETHER TO PASS "EXPLORE" OR "OPEN
///TO THE SHELLEXECUTE COMMAND. 

///SO THE LINK YOU ADD NEEDS TO BE APPROPRIATELY ASSIGNED A VALUE OF LESS THAN 1000 FOR FILES (PDF ETC)
///OR WEB LINKS AND GREATER THAN 1000 FOR FILE LOCATIONS YOU WANT TO EXPLORE

///NEXT, ADD A CASE BELOW FOR THE NEWLY CREATED LINK NAME AND RETURN THE LINK ITSELF.

const char* JHP_Links(JHP_Link link)
{
	switch (link)
	{
	//PDF LINKS*****
	case JHP_Link::PDF_DesignManual:
		return "\"\\\\earth\\STANDARDS\\01 PLANNING AND DESIGN\\03 TRAINING\\Design Manual\\150722_JHP Design Manual.pdf\"";
	case JHP_Link::PDF_FairHousing:
		return "\"\\\\earth\\STANDARDS\\04 ARCHITECTURAL REFERENCE\\Fair Housing\\Fair Housing Act Design Manual.pdf\"";
	case JHP_Link::PDF_CityofDallas:
		return "\"\\\\earth\\STANDARDS\\CAD\\Autodesk\\Tools\\source\\CoD Parking_Driveways_Handbook.pdf\"";
	case JHP_Link::PDF_OCEPlotwave:
		return "\"\\\\earth\\STANDARDS\\CAD\\Autodesk\\Tools\\source\\Oce Plotwave 500.pdf\"";
	case JHP_Link::PDF_Dimensions101:
		return "\"\\\\earth\\STANDARDS\\05 GENERAL OFFICE\\JHP University\\Lectures\\Dimensioning A101\\Dimension 101.PDF\"";

	//WEB LINKS*****
	case JHP_Link::WEB_IBC:
		return "https://codes.iccsafe.org/content/IBC2018P2";
	case JHP_Link::WEB_UL:
		return "https://iq2.ulprospector.com/session/new?redirect=http%3a%2f%2fiq.ulprospector.com%2fen%2f";
	case JHP_Link::WEB_GITHELP:
		return "https://github.com/coltonf/JHP_Menu_Docs";

	//OTHER OPEN LINKS*****
	case JHP_Link::SLACK_Archicad:
		return "https://jhp-architecture.slack.com/app_redirect?channel=CFC6P6355";
	case JHP_Link::MSDN_APIDocs:
		return ""; //need to fix this...

	//EXPLORER LOCATIONS*****
	case JHP_Link::LOC_Logos:
		return "\"\\\\earth\\MARKETING\\4 - Brand_Website\\Logos\"";
	case JHP_Link::LOC_Standards:
		return "\"\\\\earth\\STANDARDS\\05 GENERAL OFFICE\\Office Standards and Best Practices\"";
	default:
		return nullptr;
	}
}

GSErrCode JHP_Open(const char* exflag, const char* link) // raw function 
{
	if (exflag == nullptr || link == nullptr)
		return ErrNilPtr;
	ShellExecute(NULL, exflag, link, NULL, NULL, SW_SHOWNORMAL);
	return NoError;
}

GSErrCode JHP_Open(JHP_Link link) //this uses links weve already established
{
	GSErrCode err = NoError;
	const char* linkText = JHP_Links(link); //gets actual link using enum
	if (linkText == nullptr) { return err = ErrNilPtr; } //returns proper error if the link isnt here

	if ((int)link <= 1000) //pdf or weblink, use "open"
	{
		err = JHP_Open("open", linkText);
	}
	if ((int)link > 1000) //file location,us "explore"
	{
		err = JHP_Open("explore", linkText);
	}
	return err; 
}



