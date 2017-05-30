// PacketOutputDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PacketCapture.h"
#include "PacketOutputDlg.h"
#include "afxdialogex.h"

// CPacketOutputDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPacketOutputDlg, CDialogEx)

CPacketOutputDlg::CPacketOutputDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OUTPUT_DIALOG, pParent)
{

}

CPacketOutputDlg::~CPacketOutputDlg()
{
}

void CPacketOutputDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Virtual, vListCtrl);
}


BEGIN_MESSAGE_MAP(CPacketOutputDlg, CDialogEx)
	//	�ݹ� �׸�� ���������� ����. ��� �׸� �����Ϳ� ���� �� �޽����� �߻��Ѵ�.
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_Virtual, &CPacketOutputDlg::OnLvnGetdispinfoList)

	//	���ʴ� ���� ����Ʈ �信 �����͸� ��Ȱ�ϰ� �����ϱ� ���� ĳ�ø� ������ �ʿ䰡 �ִ�.
	//	NMLVCACHEHINT ����ü�� �����Ͽ� ���� ���� �����͸� �̸� �� �� �ִ�. return 0�� �ؾ��Ѵ�.
	ON_NOTIFY(LVN_ODCACHEHINT, IDC_LIST_Virtual, &CPacketOutputDlg::OnLvnOdcachehintList)

	//	���ʰ� FindItem �Լ��� ȣ���߰ų� ����ڰ� Ű���� �˻�Ű�� ���� �׸� �˻��� ��û���� �� ��������.
	//	���� ����Ʈ ��� ������ �׸� �����͸� ������ ���� �ʱ� ������ ȥ�� �����δ� �˻��� �� �� ����
	//	���ʿ��� �� �޽����� ���� ���� ��û�� �Ѵ�. ���ʴ� �˻� ����� NMLVFINDITEM ����ü�� ä���� �ϸ�
	//	���� �˻� ����� ���ٸ� -1�� �����Ѵ�.
	//ON_NOTIFY(LVN_ODFINDITEM, IDC_LIST_Virtual, &CPacketOutputDlg::OnLvnFindItemList)

	//ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_Virtual, OnLvnClickColumn)
	ON_BN_CLICKED(IDOK, &CPacketOutputDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPacketOutputDlg �޽��� ó�����Դϴ�.


BOOL CPacketOutputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CString header;
	for (int i = 0; i < 7; i++)
	{
		header.LoadStringW(IDS_LISTCOL + i);
		vListCtrl.InsertColumn(i, header, LVCF_TEXT, 50);
	}

	//vListCtrl.SetExtendedStyle(vListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	vListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT
							| LVS_EX_GRIDLINES
							| LVS_EX_LABELTIP);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CPacketOutputDlg::OnLvnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;

	if (pItem == NULL) return;

	int nRow = pItem->iItem;
	int nCol = pItem->iSubItem;

	if (nRow<0 || nRow >= (vec.size())/*��ü ����Ʈ ����*/)
		return;


	//m_List.GetItemText(i, 1);   //<-�ڵ�� ������ ����Ŵ.

	if (pItem->pszText) //�̰��� �η� �� ���� �翬�� ����.
	{
		switch (nCol)
		{
		case 0:
			//lstrcpy(pItem->pszText, message[nRow].i/*nRow, 0�� ���� �� ���ڿ�*/);
			wsprintf(pItem->pszText, L"%d", vec[nRow].i);
			//lstrcpy(pItem->pszText, L"Hi1");
			
			break;
		case 1:
			wsprintf(pItem->pszText, L"%s", vec[nRow].name);
			//lstrcpy(pItem->pszText, vec[nRow].name/*nRow, 1�� ���� �� ���ڿ�*/);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		}
	}
	*pResult = 0;
}

void CPacketOutputDlg::OnLvnOdcachehintList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVCACHEHINT pCacheHint = reinterpret_cast<LPNMLVCACHEHINT>(pNMHDR);
		
	// Update the cache with the recommended range.
	for (int i = pCacheHint->iFrom; i <= pCacheHint->iTo; i++)
	{
		//vec[i].i = i % 2;
		//sprintf_s(vec[i].name, sizeof(vec[i].name), "Itme %d", i);
		/*
		m_Items[i].m_iImage = i % 2;
		m_Items[i].m_strItemText.Format(_T("Item %d"), i);
		m_Items[i].m_strSubItem1Text = _T("Sub 1");
		m_Items[i].m_strSubItem2Text = _T("Sub 2");
		*/
	}
	*pResult = 0;
}

/*
int CPacketOutputDlg::OnLvnFindItemList(NMHDR *pNMHDR, LRESULT *pResult)
{

return -1;
}
*/

void CPacketOutputDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	for (int i = 0; i < MAX; i++)
		vec.push_back(DATA(i, "HI"));
	
	vListCtrl.SetRedraw(FALSE);
	vListCtrl.SetItemCountEx(vec.size());
	vListCtrl.SetRedraw(TRUE);

	//CDialogEx::OnOK();
}
