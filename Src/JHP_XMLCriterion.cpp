// *****************************************************************************
// Source code for 'JHP Menu' Add-On
// API Development Kit 22
//
// Started on 07/18/2019 at 1:13pm by CFranklin
//
// *****************************************************************************

#include "JHP_Utilities.h"

// *****************************************************************************
// Contains all the criterion we need to import in XML form.
// *****************************************************************************

//NOTE! WHEN EXPORTING THE XML FROM ARCHICAD, IT WONT BE FORMATTED CORRECTLY
//1. FIND AND REPLACE ALL QUOTES (") WITH ESCAPED QUOTES (\")
//2. SELECT ALL, THEN PLACE CURSOR (SHIFT+ALT+I IN VSCODE)
//3. PLACE QUOTES AT END OF EVERY LINE (")
//4. SELECT ALL AGAIN, PLACE CURSOR, PRESS HOME TWICE TO BE AT LINE BEGINNING
//5. PLACE QUOTES AGAIN, ALL LINES SHOULD START WITH (")
//6. COPY PASTE TO HERE.


const char* JHP_GetXMLCriterion(XMLCriterion /*crit*/)
{
	return "null";
	//placeholder... probably will need this one day
}