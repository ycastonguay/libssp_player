
// sampleDlg.h : header file
//

#pragma once
#include "afxwin.h"


// sampleDlg dialog
class sampleDlg : public CDialogEx
{
// Construction
public:
	sampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PLAYERSAMPLEWIN32MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int CheckForError(int error);
	afx_msg void InitializePlayer();
	afx_msg void OnBnClickedButtonplay();
	afx_msg void OnBnClickedButtonpause();
	afx_msg void OnBnClickedButtonstop();
	afx_msg void OnBnClickedButtonprevious();
	afx_msg void OnBnClickedButtonnext();
	afx_msg void OnBnClickedButtonopen();
	CStatic m_lblVersion;
	CStatic m_lblTitle;
	CStatic m_lblState;
	CStatic m_lblPosition;
	CStatic m_lblPlaylist;
	CStatic m_lblFilePath;
};
