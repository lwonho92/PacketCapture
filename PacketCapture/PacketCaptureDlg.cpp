
// PacketCaptureDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "PacketCapture.h"
#include "PacketCaptureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPacketCaptureDlg 대화 상자



CPacketCaptureDlg::CPacketCaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PACKETCAPTURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPacketCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPacketCaptureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPacketCaptureDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CPacketCaptureDlg::OnBnClickedMfcbutton2)
END_MESSAGE_MAP()


// CPacketCaptureDlg 메시지 처리기

BOOL CPacketCaptureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CPacketCaptureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CPacketCaptureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CPacketCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPacketCaptureDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*
	sqlite3* pDB;
	char* strSQL;
	CString str, strNum, strTrno, strHotime;
	char* pErr, *pDBFile = "Data.db";
	int nResult = sqlite3_open(pDBFile, &pDB);
	if (nResult)
	{
		AfxMessageBox(L"DB 파일을 열지 못했습니다.");
		return;
	}

	str = "DB 생성.\r\n";

	strSQL = "DROP TABLE [PacketTable]"; // 테이블이 있으면 지운다.
	nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);

	strSQL = "CREATE TABLE [PacketTable] ( \
		[Num] int(11) NOT NULL, \
		[trno] varchar(8) DEFAULT NULL, \
		[hotime] varchar(6) DEFAULT NULL \
		)"; // MySQL 자료형으로 지정함, SQLite 자료형 확인하기.
	nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);
	if (nResult)
	{
		AfxMessageBox(L"테이블을 만들기 실패!");
		sqlite3_free(&pErr);
		return;
	}

	str += "테이블 생성.\r\n";

	strSQL = "INSERT INTO PacketTable (Num, trno, hotime) VALUES ( 100, 'PHONE', '10:10:10' );";
	nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);
	if (nResult)
	{
		AfxMessageBox(L"데이터 저장 실패!");
		sqlite3_free(pErr);
		return;
	}

	str += "데이터 삽입.\r\n";

	strSQL = "SELECT * FROM PacketTable;";
	char **results = NULL;
	int rows, columns;

	// 조회된 데이터의 행과 열의 수를 각각 rows, columns 에 저장한다.
	nResult = sqlite3_get_table(pDB, strSQL, &results, &rows, &columns, &pErr);	
	if (nResult)
	{
		AfxMessageBox(CString(sqlite3_errmsg(pDB)));
		return;
	}
	else
	{
		// Display Table
		for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
		{
			// 첫번째 행은 테이블의 컬럼 정보를 가져오고 두번째 행부터 데이터가 된다.
			// 데이터만 가져오려면 rowCtr을 1부터 시작한다.
			strNum = (CA2W)results[rowCtr * columns];
			strTrno = (CA2W)results[rowCtr * columns + 1];
			strHotime = (CA2W)results[rowCtr * columns + 2];

			str += (strNum + L"\t" + strTrno + L"\t" + strHotime + L"\r\n");
		}
	}
	AfxMessageBox(str);
	sqlite3_free_table(results);

	// Close Database
	sqlite3_close(pDB);
	*/

	CDialogEx::OnOK();
}


void CPacketCaptureDlg::OnBnClickedMfcbutton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
