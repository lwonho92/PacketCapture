// PacketOutputDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PacketCapture.h"
#include "PacketOutputDlg.h"
#include "afxdialogex.h"

// CPacketOutputDlg 대화 상자입니다.

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
	//	콜백 항목과 마찬가지의 목적. 모든 항목 데이터에 대해 이 메시지가 발생한다.
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST_Virtual, &CPacketOutputDlg::OnLvnGetdispinfoList)

	//	오너는 가상 리스트 뷰에 데이터를 원활하게 공급하기 위해 캐시를 유지할 필요가 있다.
	//	NMLVCACHEHINT 구조체를 참조하여 다음 읽을 데이터를 미리 알 수 있다. return 0을 해야한다.
	ON_NOTIFY(LVN_ODCACHEHINT, IDC_LIST_Virtual, &CPacketOutputDlg::OnLvnOdcachehintList)

	//	오너가 FindItem 함수를 호출했거나 사용자가 키보드 검색키를 눌러 항목 검색을 요청했을 때 보내진다.
	//	가상 리스트 뷰는 스스로 항목 데이터를 가지고 있지 않기 때문에 혼자 힘으로는 검색을 할 수 없어
	//	오너에게 이 메시지를 보내 협조 요청을 한다. 오너는 검색 결과를 NMLVFINDITEM 구조체에 채워야 하며
	//	만약 검색 결과가 없다면 -1을 리턴한다.
	//ON_NOTIFY(LVN_ODFINDITEM, IDC_LIST_Virtual, &CPacketOutputDlg::OnLvnFindItemList)

	//ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_Virtual, OnLvnClickColumn)
	ON_BN_CLICKED(IDOK, &CPacketOutputDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPacketOutputDlg 메시지 처리기입니다.


BOOL CPacketOutputDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
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
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CPacketOutputDlg::OnLvnGetdispinfoList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	LV_ITEM* pItem = &(pDispInfo)->item;

	if (pItem == NULL) return;

	int nRow = pItem->iItem;
	int nCol = pItem->iSubItem;

	if (nRow<0 || nRow >= (vec.size())/*전체 리스트 갯수*/)
		return;


	//m_List.GetItemText(i, 1);   //<-코드는 문제를 일으킴.

	if (pItem->pszText) //이값이 널로 올 때도 당연히 있음.
	{
		switch (nCol)
		{
		case 0:
			//lstrcpy(pItem->pszText, message[nRow].i/*nRow, 0번 열에 들어갈 문자열*/);
			wsprintf(pItem->pszText, L"%d", vec[nRow].i);
			//lstrcpy(pItem->pszText, L"Hi1");
			
			break;
		case 1:
			wsprintf(pItem->pszText, L"%s", vec[nRow].name);
			//lstrcpy(pItem->pszText, vec[nRow].name/*nRow, 1번 열에 들어갈 문자열*/);
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for (int i = 0; i < MAX; i++)
		vec.push_back(DATA(i, "HI"));
	
	vListCtrl.SetRedraw(FALSE);
	vListCtrl.SetItemCountEx(vec.size());
	vListCtrl.SetRedraw(TRUE);

	//CDialogEx::OnOK();
}
