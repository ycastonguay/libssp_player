// Copyright © 2011-2015 Yanick Castonguay
//
// This file is part of Sessions, a music player for musicians.
//
// Sessions is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Sessions is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Sessions. If not, see <http://www.gnu.org/licenses/>.

#include "stdafx.h"
#include "player-sample-win32-mfc.h"
#include "sampleDlg.h"
#include "afxdialogex.h"
#include "../player/ssp_public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

sampleDlg::sampleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(sampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void sampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATICVERSION, m_lblVersion);
	DDX_Control(pDX, IDC_STATICTITLE, m_lblTitle);
	DDX_Control(pDX, IDC_STATICSTATE, m_lblState);
	DDX_Control(pDX, IDC_STATICPOSITION, m_lblPosition);
	DDX_Control(pDX, IDC_STATICPLAYLIST, m_lblPlaylist);
	DDX_Control(pDX, IDC_STATICFILEPATH, m_lblFilePath);
}

BEGIN_MESSAGE_MAP(sampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONPLAY, &sampleDlg::OnBnClickedButtonplay)
	ON_BN_CLICKED(IDC_BUTTONPAUSE, &sampleDlg::OnBnClickedButtonpause)
	ON_BN_CLICKED(IDC_BUTTONSTOP, &sampleDlg::OnBnClickedButtonstop)
	ON_BN_CLICKED(IDC_BUTTONPREVIOUS, &sampleDlg::OnBnClickedButtonprevious)
	ON_BN_CLICKED(IDC_BUTTONNEXT, &sampleDlg::OnBnClickedButtonnext)
	ON_BN_CLICKED(IDC_BUTTONOPEN, &sampleDlg::OnBnClickedButtonopen)
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL sampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	InitializePlayer();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void sampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void sampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR sampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void logCallback(void *user, const char* str) {
	TRACE("libssp_player :: %s\n", str);
}

void stateChangedCallback(void *user, ssp_player_state_t state) {	
	sampleDlg *dlg = (sampleDlg*)user;
	CString strState;
	strState.Format(_T("State: %d"), state);
	dlg->m_lblState.SetWindowTextW(strState);
}

void playlistIndexChangedCallback(void *user) {
	sampleDlg *dlg = (sampleDlg*)user;

	int currentIndex = SSP_Playlist_GetCurrentIndex();
	int count = SSP_Playlist_GetCount();

	SSP_PLAYLISTITEM item;
	SSP_Playlist_GetItemAt(currentIndex, &item);

	CString strPlaylist, strFilePath;
	strPlaylist.Format(_T("Playlist [%d/%d]"), currentIndex + 1, count);
	strFilePath.Format(_T("File path: %s"), CString(item.filePath));
	dlg->m_lblPlaylist.SetWindowTextW(strPlaylist);
	dlg->m_lblFilePath.SetWindowTextW(strFilePath);
}

void sampleDlg::OnTimer(UINT_PTR nIDEvent)
{
	SSP_POSITION pos;
	SSP_GetPosition(&pos);
	CString strPosition;
	strPosition.Format(_T("Position: %s"), CString(pos.str));
	m_lblPosition.SetWindowTextW(strPosition);

	CDialogEx::OnTimer(nIDEvent);
}

void sampleDlg::InitializePlayer()
{
	int version = SSP_GetVersion();
	TRACE("libssp_player version %d\n", version);

	CString strVersion;
	strVersion.Format(_T("Version %d"), version);
	m_lblVersion.SetWindowTextW(strVersion);

	// TODO: Setup plugin path correctly

	int error = CheckForError(SSP_Init(NULL));
	if (error != SSP_OK)
		return;

	SSP_SetLogCallback(logCallback, NULL);	
	SSP_SetStateChangedCallback(stateChangedCallback, this);
	SSP_SetPlaylistIndexChangedCallback(playlistIndexChangedCallback, this);

	error = CheckForError(SSP_InitDevice(-1, 44100, 1000, 100, true));
	if (error != SSP_OK)
		return;
}

int sampleDlg::CheckForError(int error)
{
	if (error != SSP_OK)
	{
		TRACE("libssp_player error %d", error);
	}

	return error;
}

void sampleDlg::OnBnClickedButtonplay()
{
	CheckForError(SSP_Play());
	SetTimer(0, 100, NULL);
}

void sampleDlg::OnBnClickedButtonpause()
{
	CheckForError(SSP_Pause());
}

void sampleDlg::OnBnClickedButtonstop()
{
	CheckForError(SSP_Stop());
	KillTimer(0);
}

void sampleDlg::OnBnClickedButtonprevious()
{
	CheckForError(SSP_Previous());
}

void sampleDlg::OnBnClickedButtonnext()
{
	CheckForError(SSP_Next());
}

void sampleDlg::OnBnClickedButtonopen()
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT,
		_T("Audio Files (*.mp3; *.flac)|*.mp3; *.flac||"), this);

	dlg.m_pOFN->lpstrTitle = _T("Choose audio files to play");
	dlg.m_pOFN->lpstrInitialDir = _T("c:");

	const DWORD numberOfFileNames = 100;
	const DWORD fileNameMaxLength = MAX_PATH + 1;
	const DWORD bufferSize = (numberOfFileNames * fileNameMaxLength) + 1;
	TCHAR* filenamesBuffer = new TCHAR[bufferSize];

	filenamesBuffer[0] = NULL;
	filenamesBuffer[bufferSize - 1] = NULL;

	dlg.m_ofn.lpstrFile = filenamesBuffer;
	dlg.m_ofn.nMaxFile = bufferSize;

	SSP_Playlist_Clear();

	if (dlg.DoModal() == IDOK)
	{
		POSITION fileNamesPosition = dlg.GetStartPosition();
		int iCtr = 0;
		while (fileNamesPosition != NULL)
		{
			CString filePath = dlg.GetNextPathName(fileNamesPosition);
			const size_t newsizew = (filePath.GetLength() + 1) * 2;
			char *nstringw = new char[newsizew];
			size_t convertedCharsw = 0;
			wcstombs_s(&convertedCharsw, nstringw, newsizew, filePath, _TRUNCATE);

			SSP_Playlist_AddItem(nstringw);
			iCtr++;
		}
	}

	delete[] filenamesBuffer;
}
