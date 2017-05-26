
// PacketCaptureDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "PacketCapture.h"
#include "PacketCaptureDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CPacketCaptureDlg ��ȭ ����



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


// CPacketCaptureDlg �޽��� ó����

BOOL CPacketCaptureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CPacketCaptureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CPacketCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPacketCaptureDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	/*
	sqlite3* pDB;
	char* strSQL;
	CString str, strNum, strTrno, strHotime;
	char* pErr, *pDBFile = "Data.db";
	int nResult = sqlite3_open(pDBFile, &pDB);
	if (nResult)
	{
		AfxMessageBox(L"DB ������ ���� ���߽��ϴ�.");
		return;
	}

	str = "DB ����.\r\n";

	strSQL = "DROP TABLE [PacketTable]"; // ���̺��� ������ �����.
	nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);

	strSQL = "CREATE TABLE [PacketTable] ( \
		[Num] int(11) NOT NULL, \
		[trno] varchar(8) DEFAULT NULL, \
		[hotime] varchar(6) DEFAULT NULL \
		)"; // MySQL �ڷ������� ������, SQLite �ڷ��� Ȯ���ϱ�.
	nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);
	if (nResult)
	{
		AfxMessageBox(L"���̺��� ����� ����!");
		sqlite3_free(&pErr);
		return;
	}

	str += "���̺� ����.\r\n";

	strSQL = "INSERT INTO PacketTable (Num, trno, hotime) VALUES ( 100, 'PHONE', '10:10:10' );";
	nResult = sqlite3_exec(pDB, strSQL, NULL, NULL, &pErr);
	if (nResult)
	{
		AfxMessageBox(L"������ ���� ����!");
		sqlite3_free(pErr);
		return;
	}

	str += "������ ����.\r\n";

	strSQL = "SELECT * FROM PacketTable;";
	char **results = NULL;
	int rows, columns;

	// ��ȸ�� �������� ��� ���� ���� ���� rows, columns �� �����Ѵ�.
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
			// ù��° ���� ���̺��� �÷� ������ �������� �ι�° ����� �����Ͱ� �ȴ�.
			// �����͸� ���������� rowCtr�� 1���� �����Ѵ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
