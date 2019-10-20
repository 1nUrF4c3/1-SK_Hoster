//=====================================================================================

#include "MainDlg.h"

//=====================================================================================

cMainDlg::cMainDlg(HINSTANCE instance) : cDialog(IDD_MAIN), _instance(instance)
{
	_messages[WM_INITDIALOG] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnInit);
	_messages[WM_COMMAND] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnCommand);
	_messages[WM_CLOSE] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnClose);
	_messages[WM_TIMER] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnTimer);

	_events[IDC_FORCEHOST] = static_cast<cDialog::fnDlgProc>(&cMainDlg::OnForceHost);
}

//=====================================================================================

INT_PTR cMainDlg::OnInit(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	cDialog::OnInit(hDlg, message, wParam, lParam);

	HICON hIcon = LoadIcon(_instance, MAKEINTRESOURCE(IDI_ICON));

	SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
	SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);

	DeleteObject(hIcon);

	SetTimer(_hwnd, IDT_TIMER, 1000, NULL);

	_forceHost.Attach(_hwnd, IDC_FORCEHOST);

	RefreshGUI();

	return TRUE;
}

//=====================================================================================

INT_PTR cMainDlg::OnClose(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	return cDialog::OnClose(hDlg, message, wParam, lParam);
}

//=====================================================================================

INT_PTR cMainDlg::OnTimer(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (wParam == IDT_TIMER)
		if (bForceHost)
			cMemory::MemWrite("iw6mp64_ship.exe", dwMinPlayers + 0x10, 1);

	return TRUE;
}

//=====================================================================================

INT_PTR cMainDlg::OnForceHost(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (cMemory::MemRead("iw6mp64_ship.exe", PARTY_MINPLAYERS, &dwMinPlayers))
	{
		bForceHost = !bForceHost;
		RefreshGUI();
		cMessage::ShowInfo(_hwnd, bForceHost == true ?
			"Force Host enabled.\nEnter a lobby by yourself and people will join." :
			"Force Host disabled.\nExit the lobby and re-enter to apply changes.");
	}

	else
	{
		bForceHost = false;
		RefreshGUI();
		cMessage::ShowError(_hwnd, "BOOL cMemory::MemRead<TYPE>(const char* process, DWORD_PTR address, TYPE* buffer)\nFunction call returned FALSE (failure).");
	}

	return TRUE;
}

//=====================================================================================