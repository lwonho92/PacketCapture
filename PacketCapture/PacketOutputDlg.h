#pragma once
#include "afxcmn.h"
#include <string>
#include <vector>
using namespace std;

#define MAX 100000

// CPacketOutputDlg ��ȭ �����Դϴ�.
typedef class Data {
public:
	int i;
	char *name;

	Data(int i, char *name)
	{
		this->i = i;
		this->name = name;
	}
}DATA;

class CPacketOutputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPacketOutputDlg)

public:
	CPacketOutputDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPacketOutputDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OUTPUT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl vListCtrl;
	virtual BOOL OnInitDialog();
	virtual void OnLvnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnLvnOdcachehintList(NMHDR *pNMHDR, LRESULT *pResult);
	//virtual int CPacketOutputDlg::OnLvnFindItemList(NMHDR *pNMHDR, LRESULT *pResult);

	vector<DATA> vec;
	afx_msg void OnBnClickedOk();
};