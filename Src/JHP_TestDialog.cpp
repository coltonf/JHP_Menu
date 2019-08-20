#include	"JHP_Utilities.h"
#include	"JHP_WallAuditSettingsDialog.hpp"


JHPWallAuditSettingsDialog::JHPWallAuditSettingsDialog () :
	DG::ModalDialog(ACAPI_GetOwnResModule(), 32600, ACAPI_GetOwnResModule()),
	closeButton(GetReference(), ButtonID),
	hellowWorldText(GetReference(), LeftTextID),
	JHPLogoIcon(GetReference(), IconItemID)
{
	AttachToAllItems(*this);
}

JHPWallAuditSettingsDialog::~JHPWallAuditSettingsDialog()
{
}

void JHPWallAuditSettingsDialog::ButtonClicked(const DG::ButtonClickEvent& ev)
{
	if (ev.GetSource() == &closeButton)
	{
		PostCloseRequest(Accept);
	}
}
	