
// 3dGraphDlg.h : ��� ����
//

#pragma once

#include "GraphImpl.h"

// CMy3dGraphDlg ��ȭ ����
class CMy3dGraphDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CMy3dGraphDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY3DGRAPH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private : 
	GraphImpl graph_;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton4();
};
