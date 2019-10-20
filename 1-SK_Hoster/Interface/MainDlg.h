//=====================================================================================

#pragma once

#include "../Resources/Resource.h"
#include "../Interface/WinAPI/Dialog.hpp"
#include "../Interface/WinAPI/Button.hpp"
#include "../Helpers/Message.hpp"
#include "../Helpers/Memory.hpp"

//=====================================================================================

#define PARTY_MINPLAYERS 0x141E165E0

//=====================================================================================

class cMainDlg : public cDialog
{
public:

	cMainDlg(HINSTANCE instance);
	~cMainDlg() {};

private:

	void RefreshGUI();

	DLG_HANDLER(OnInit);
	DLG_HANDLER(OnClose);
	DLG_HANDLER(OnTimer);
	DLG_HANDLER(OnForceHost);

	DWORD_PTR dwMinPlayers = NULL;
	bool bForceHost = false;

	ctrl::cButton _forceHost;

	HINSTANCE _instance;
};

//=====================================================================================