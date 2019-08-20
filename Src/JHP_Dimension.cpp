// *****************************************************************************
// JHP_Dimension.cpp
// Source code for 'Dimension' block of menu choices for 'JHP Menu' Add-On
// API Development Kit 22
//
// Started on 05/29/2019 at 12:47pm by CFranklin
//
// *****************************************************************************

/* -- Includes  ------------------------------- */

#include	"JHP_Utilities.h"

// -----------------------------------------------------------------------------
// Select all the exterior walls
// -----------------------------------------------------------------------------

GSErrCode SelectExteriorWalls()
{
	GSErrCode				err;
	err = JHP_SelectElements(API_WallID, "A-WALL-EXTR");
	return err;
	
}

GSErrCode DimsTo256(void)
{
	GSErrCode				err;
	err = JHP_SelectElements(API_DimensionID, "A-ANNO-PLAN.ENLARGED ROOM 1/4\" or 1/2\"");
	return err;
}
