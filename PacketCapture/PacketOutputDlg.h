#pragma once
#include "afxcmn.h"
#include <string>
#include <vector>
#include "headers.h"
using namespace std;

#define MAX 1000000
int packetCount = 0;

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
	//virtual int OnLvnFindItemList(NMHDR *pNMHDR, LRESULT *pResult);

	vector<DATA> vec;
	afx_msg void OnBnClickedOk();
};

//	패킷이 도착할 때 libcap에서 실행되는 콜백 함수.
void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *packet_data)
{
	struct tm ltime;
	char timestr[16];
	time_t local_tv_sec;

	/*
	* 사용하지 않는 변수.
	*/
	(VOID)(param);

	//	타임 스탬프를 읽을 수 있게 변환.
	local_tv_sec = header->ts.tv_sec;
	localtime_s(&ltime, &local_tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", &ltime);

	//	타임 스탬프와 패킷 길이 출력.
	printf("%d-th\t%s.%.6d\tlen:%-5d\t", ++packetCount, timestr, header->ts.tv_usec, header->len);

	ethernet_proc(packet_data);
	printf("\n");
}

void ethernet_proc(const u_char *ethernet_data)
{
	ethernet_header *eh;

	eh = (ethernet_header *)(ethernet_data);
	eh->dType = ntohs(eh->dType);

	// Print Mac address.
	print_mac(eh->saddr, eh->daddr);

	printf("Ethernet Type: ");
	if (eh->dType <= 0x05dc)
		printf("IEEE 802.3 CSMA/CD, %016x ", eh->dType);
	else if (eh->dType == 0x0600)
		printf("XNS IDP ");
	else if (eh->dType == 0x0800)
	{
		printf("IP");
		ip_proc(ethernet_data + ETHER_HEADER_LEN);
	}
	else if (eh->dType == 0x0805)
		printf("X.25 PLP ");
	else if (eh->dType == 0x0806)
	{
		printf("ARP ");
		arp_proc(ethernet_data + ETHER_HEADER_LEN);
	}
	else if (eh->dType == 0x8035)
		printf("RARP ");
	else if (eh->dType == 0x8137)
		printf("NetwareIPX ");
	else if (eh->dType == 0x8191)
		printf("NetBIOS ");
	else
		printf("Unknown. ");
}

void arp_proc(const u_char *arp_data)
{
	arp_header *ah;

	ah = (arp_header *)(arp_data);
	ah->hType = ntohs(ah->hType);
	ah->pType = ntohs(ah->pType);
	ah->op = ntohs(ah->op);

	switch (ah->op)
	{
	case 1:
		printf("Request ");
		break;
	case 2:
		printf("Reply ");
		break;
	}
}
void ip_proc(const u_char *ip_data)
{
	ip_header *ih;
	u_int ip_version, ip_header_len;

	//	Ethernet 헤더만큼 이동하여 IP패킷을 구조체에 넣음.
	ih = (ip_header *)(ip_data);

	//	네트워크 바이트 순서에서 호스트 바이트 순서로 변환.
	ih->tlen = ntohs(ih->tlen);
	ih->identification = ntohs(ih->identification);
	ih->flags_fo = ntohs(ih->flags_fo);
	ih->crc = ntohs(ih->crc);
	// ntohs(op_pad) 주의.
	//ih->op_pad = ntohs(ih->op_pad);

	print_ip(ih->saddr, ih->daddr);

	ip_version = (ih->ver_ihl & 0xf0);
	ip_version >>= 4;
	printf("Version %u", ip_version);
	//	IP 패킷의 길이만큼 이동.
	ip_header_len = (ih->ver_ihl & 0xf) * 4;

	switch (ih->proto)
	{
	case 1:		
		printf("[ ICMP ]");
		icmp_proc(ip_data + ip_header_len);
		break;
	case 2:
		printf("[ IGMP ]");
		break;
	case 6:
		printf("[ TCP ]");
		tcp_proc(ip_data + ip_header_len);

		break;
	case 8:
		printf("[ EGP ]");
		break;
	case 17:
		printf("[ UDP ]");
		tcp_proc(ip_data + ip_header_len);

		break;
	case 41:
		printf("[ IPv6 ]");
		break;
	case 89:
		printf("[ OSPF ]");
		break;
	default:
		printf("[ Unknown ]");
		break;
	}
}

void icmp_proc(const u_char *icmp_data)
{
	icmp_header *ih;
	ih = (icmp_header *)(icmp_data);
	ih->checksum = ntohs(ih->checksum);

	switch (ih->type)
	{
	case 3:
		printf("Destination unreadchable ");
		break;
	case 4:
		printf("Source quench ");
		break;
	case 11:
		printf("Time exceeded ");
		break;
	case 12:
		printf("Parameter problem ");
		break;
	case 5:
		printf("Redirection ");
		break;
	case 8:
	case 0:
		printf("Echo request or reply ");
		break;
	case 13:
	case 14:
		printf("Timestame request and reply ");
		break;
	case 17:
	case 18:
		printf("Address mask request and reply ");
		break;
	case 10:
	case 9:
		printf("Router solicitation and advertisement ");
		break;
	}
}

void tcp_proc(const u_char *tcp_data)
{
	tcp_header *th;
	th = (tcp_header *)(tcp_data);
	th->sport = ntohs(th->sport);
	th->dport = ntohs(th->dport);

	//th->seq_number = ntohl(th->seq_number);
	//th->Ack_number = ntohl(th->Ack_number);
	//printf("seq: (%u), ack: (%u) ", th->seq_number, th->Ack_number);

	th->window_size = ntohs(th->window_size);
	th->checksum = ntohs(th->checksum);
	th->urgent = ntohs(th->urgent);

	print_port(th->sport, th->dport);
}
void udp_proc(const u_char *udp_data)
{
	udp_header *uh;
	uh = (udp_header *)(udp_data);
	uh->sport = ntohs(uh->sport);
	uh->dport = ntohs(uh->dport);
	uh->len = ntohs(uh->len);
	uh->crc = ntohs(uh->crc);

	print_port(uh->sport, uh->dport);
}

void print_mac(ethernet_address saddr, ethernet_address daddr)
{
	printf("\t%02x:%02x:%02x:%02x:%02x:%02x -> %02x:%02x:%02x:%02x:%02x:%02x",
		saddr.byte1,
		saddr.byte2,
		saddr.byte3,
		saddr.byte4,
		saddr.byte5,
		saddr.byte6,

		daddr.byte1,
		daddr.byte2,
		daddr.byte3,
		daddr.byte4,
		daddr.byte5,
		daddr.byte6
		);
}

void print_ip(ip_address saddr, ip_address daddr)
{
	printf("\t%3d.%3d.%3d.%3d -> %3d.%3d.%3d.%3d",
		saddr.byte1,
		saddr.byte2,
		saddr.byte3,
		saddr.byte4,

		daddr.byte1,
		daddr.byte2,
		daddr.byte3,
		daddr.byte4);
}

void print_port(u_short sport, u_short dport)
{
	printf("\t%5d -> %5d", sport, dport);
}