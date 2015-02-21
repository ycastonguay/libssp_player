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

#pragma once
#include "afxwin.h"
#include "../player/ssp_public.h"

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
	afx_msg void StateChangedCallback(void *user, ssp_player_state_t state);
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
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
