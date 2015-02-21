
// sampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "player-sample-win32-mfc.h"
#include "sampleDlg.h"
#include "afxdialogex.h"

extern "C" {
#include "../player/ssp_public.h"
}

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

// sampleDlg dialog

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
END_MESSAGE_MAP()

// sampleDlg message handlers

BOOL sampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

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
}

void playlistIndexChangedCallback(void *user) {
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
	SSP_SetStateChangedCallback(stateChangedCallback, NULL);
	SSP_SetPlaylistIndexChangedCallback(playlistIndexChangedCallback, NULL);

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
	// TODO: Add your control notification handler code here
}

void sampleDlg::OnBnClickedButtonpause()
{
	// TODO: Add your control notification handler code here
}

void sampleDlg::OnBnClickedButtonstop()
{
	// TODO: Add your control notification handler code here
}

void sampleDlg::OnBnClickedButtonprevious()
{
	// TODO: Add your control notification handler code here
}

void sampleDlg::OnBnClickedButtonnext()
{
	// TODO: Add your control notification handler code here
}

void sampleDlg::OnBnClickedButtonopen()
{
	// TODO: Add your control notification handler code here
}
