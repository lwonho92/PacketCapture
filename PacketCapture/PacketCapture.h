
// PacketCapture.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPacketCaptureApp:
// �� Ŭ������ ������ ���ؼ��� PacketCapture.cpp�� �����Ͻʽÿ�.
//

class CPacketCaptureApp : public CWinApp
{
public:
	CPacketCaptureApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPacketCaptureApp theApp;