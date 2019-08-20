// *****************************************************************************
// Source code for 'JHP Menu' Add-On
// API Development Kit 22
//
// Started on 05/29/2019 at 12:47pm by CGilmer/CFranklin
//
// *****************************************************************************

//String-scan codes:
//ACAPI_WriteReport ("the answer is %d", false, i); //where i is an integer
//ACAPI_WriteReport ("the answer is %lf", false, d); //where d is a double

//%c	: single character
//%lf	: double
//%d	: decimal integer
//%f	: float

/* -- Includes  ------------------------------- */

#include	"JHP_Utilities.h"


// -----------------------------------------------------------------------------
// Change the content of text to desired case
// -----------------------------------------------------------------------------

void JHP_ChangeText(JHP_Case textCase, API_ElementMemo* memo)
{
	switch (textCase)
	{
	case JHP_Case::Upper:
	{
		CHtoUpper(*memo->textContent);
		break;
	}

	case JHP_Case::Lower:
	{
		CHtoLower(*memo->textContent);
		break;
	}

	case JHP_Case::Smart:
	{
		break;
	}
	}
}

// -----------------------------------------------------------------------------
// Get selected text or offer opportunity to select text to change case
// -----------------------------------------------------------------------------
GSErrCode JHP_TextToCase(JHP_Case textCase)
{
	GSErrCode				err;
	API_Neig**				selNeigs;
	API_ElementMemo			memo;
	API_Element				element, mask;
	UInt32					memoMask = 0;

	selNeigs = (API_Neig **)BMAllocateHandle(sizeof(API_Neig), ALLOCATE_CLEAR, 0);
	err = JHP_GetSelection(&selNeigs, true);

	UInt32 nSel = BMGetHandleSize((GSHandle)selNeigs) / sizeof(API_Neig);

	err = ACAPI_Element_Select(selNeigs, nSel, true);

	for (UInt32 i = 0; i < nSel; ++i) {

		BNZeroMemory(&element, sizeof(API_Element));
		BNZeroMemory(&memo, sizeof(API_ElementMemo));

		element.header.guid = (*selNeigs)[i].guid;

		element.header.typeID = Neig_To_ElemID((*selNeigs)[i].neigID);

		if (element.header.typeID != API_TextID) { continue; }

		if (!ACAPI_Element_Filter(element.header.guid, APIFilt_IsEditable))
		{
			WriteReport_Alert("Object not editable");
			break;
		}

		if (ACAPI_Element_Get(&element) != NoError) { continue; }

		memoMask |= APIMemoMask_TextContent;
		memoMask |= APIMemoMask_Paragraph;
		

		if (ACAPI_Element_GetMemo(element.header.guid, &memo, memoMask) != NoError) { continue; }

		JHP_ChangeText(textCase, &memo);

		err = ACAPI_Element_Change(&element, &mask, &memo, memoMask, true);

		ACAPI_DisposeElemMemoHdls(&memo);
	}

	BMKillHandle((GSHandle*)& selNeigs);

	return err;
}








