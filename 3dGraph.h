
// 3dGraph.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CMy3dGraphApp:
// �� Ŭ������ ������ ���ؼ��� 3dGraph.cpp�� �����Ͻʽÿ�.
//

class CMy3dGraphApp : public CWinApp
{
public:
	CMy3dGraphApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CMy3dGraphApp theApp;