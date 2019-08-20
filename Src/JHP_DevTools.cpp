#include "JHP_Utilities.h"

// ~~~~~~~~~~~~~~~
// Copy SOURCE .apx to USER .apx and create archive
// ~~~~~~~~~~~~~~~

// Usage:  printf("Filename = %s\n", ExtractFileName("c:\\some\\dir\\hello.exe").c_str());
void JHP_Publish()
{
	HWND hwnd=nullptr;
	char szFileName[MAX_PATH] = "";
	
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "ArchiCAD Add-On (*.apx)\0*.apx\0All Files (*.*)\0*.*\0";
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrInitialDir = "O:\\CAD\\ArchiCAD\\Tools\\CG source\\JHP_Menu\\Build\\x64\\Release";
	ofn.lpstrDefExt = "apx";

	if (GetOpenFileName(&ofn))
	// if (IFileDialog(&ofn))
	{
		std::string fname = (ExtractFileName(szFileName));

		char dpath[MAX_PATH] = "O:\\CAD\\ArchiCAD\\Tools\\API\\";
		strcat(dpath, fname.c_str());

		DWORD attr = GetFileAttributes(dpath);
		if (attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY))
		{
			//  Does not exist.  No archive and copy.
			CopyFile(szFileName, dpath, FALSE);
			return;
		}
		else
		{
			// Does exist.  Archive and copy if OK.
			const int result = MessageBox(NULL, "Destination file already exists.\n\nDo you want to opverwrite?", "Confirm Overwrite", MB_YESNO | MB_DEFBUTTON2 | MB_ICONWARNING);
			switch (result)
			{
//			case IDYES:
//				break;
			case IDNO:
				return;
			case IDCANCEL:
				return;
			}
		}
		char apath[MAX_PATH] = "O:\\CAD\\ArchiCAD\\Tools\\API\\Archive\\";
		strcat(apath, fname.c_str());

		int i = 0;
		char cpath[MAX_PATH] = "O:\\CAD\\ArchiCAD\\Tools\\API\\Archive\\";
		strcat(cpath, fname.c_str());
		char *str = new char[3];
		itoa(i, str, 10);
		strcat(cpath, "___0");
		strcat(cpath, str);

		bool ifexist = TRUE;
		attr = GetFileAttributes(cpath);
		while (ifexist == TRUE)
			if (attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY))
				ifexist=FALSE;   //  does not exist
			else
			{
//				ifexist = TRUE;  // does exist
				char cpath[MAX_PATH] = "O:\\CAD\\ArchiCAD\\Tools\\API\\Archive\\";
				strcat(cpath, fname.c_str());
				char *str = new char[3];
				itoa(i, str, 10);
				if (i < 10)
					strcat(cpath, "___0");
				else
					strcat(cpath, "___");

				strcat(cpath, str);
				attr = GetFileAttributes(cpath);
				i++;

			}

		if(i != 0)
			itoa(--i, str, 10);
			itoa(i, str, 10);
		if (i < 10)
			strcat(apath, "___0");
		else
			strcat(apath, "___");

		strcat(apath, str);

		CopyFile(dpath, apath, FALSE);

		ifexist = FALSE;
		attr = GetFileAttributes(apath);
		while (ifexist == FALSE)
			if (attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY))
			{
				ifexist = FALSE;   //  does not exist
				attr = GetFileAttributes(apath);
			}
			else
				ifexist = TRUE;  // does exist

		CopyFile(szFileName, dpath, FALSE);
	}
	return;
}


// (entget (car (entsel)))

GSErrCode JHP_Entget(void)
{
	GSErrCode				err = NoError;
	API_Neig				theNeig;

	BNClear(theNeig);

	err = JHP_GetSelection(&theNeig, true);

	if (err != NoError)
	{
		WriteReport_Alert("Error!");
		return err;
	}

//	API_Element element;
//	BNZeroMemory(&element, sizeof(API_Element));
//	element.header.guid = theNeig.guid;
//	if (ACAPI_Element_Get(&element) == NoError)
//	{
		//One Element Selected, do whatever
//		err = JHP_SelectElements(element.header.typeID, element.header.layer);
		err = JHP_GetProp(theNeig.guid);
//	}
	return err;
}


GSErrCode JHP_GetProp(const API_Guid& guid)
{
	API_Elem_Head						elemHead;
	API_PropertyObjectRefType		**propRefs;
	API_LibPart							libPart;
	Int32										nProp, i;
	char										s[256];
	GSErrCode								err;

	BNZeroMemory(&elemHead, sizeof(API_Elem_Head));
	elemHead.guid = guid;

	err = ACAPI_Element_GetPropertyObjects(&elemHead, &propRefs, &nProp);
	if (err == NoError) {
		for (i = 0; i < nProp; i++) {
			BNZeroMemory(&libPart, sizeof(API_LibPart));
			libPart.index = (*propRefs)[i].libIndex;
			err = ACAPI_LibPart_Get(&libPart);
			if (err == NoError) {
				if ((*propRefs)[i].assign)
					sprintf(s, "Associated property:");
				else
					sprintf(s, "Property by criteria:");
				sprintf(s, "%s %s", s, (const char *)GS::UniString(libPart.docu_UName).ToCStr());
				ACAPI_WriteReport(s, false);
			}
		}
		BMKillHandle((GSHandle *)&propRefs);
	}
	else
		JHP_Msg(ErrID_To_Name(err));
	return 0;
}