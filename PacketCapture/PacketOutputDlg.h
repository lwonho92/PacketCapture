#pragma once
#include "afxcmn.h"
#include <string>
#include <vector>
using namespace std;

#define MAX 100000

// CPacketOutputDlg 대화 상자입니다.
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
	CPacketOutputDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CPacketOutputDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OUTPUT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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