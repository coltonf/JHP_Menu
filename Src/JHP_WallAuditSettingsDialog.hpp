#ifndef JHPWALLCHECKERDIALOG_HPP
#define JHPWALLCHECKERDIALOG_HPP

#include	"DGModule.hpp"

class JHPWallAuditSettingsDialog : public DG::ModalDialog,
	public DG::ButtonItemObserver,
	public DG::CompoundItemObserver
{
protected:
	enum Controls {
		ButtonID = 1,
		LeftTextID = 2,
		IconItemID = 3
	};

	DG::Button	closeButton;
	DG::LeftText hellowWorldText;
	DG::IconItem JHPLogoIcon;

	virtual void ButtonClicked(const DG::ButtonClickEvent& ev) override;

public:
	JHPWallAuditSettingsDialog();
	~JHPWallAuditSettingsDialog();
};

#endif