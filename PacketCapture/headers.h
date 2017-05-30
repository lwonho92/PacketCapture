#include "pcap.h"
#include <winsock2.h>

#pragma comment (lib, "wpcap.lib")
#pragma comment (lib, "ws2_32.lib" )

#define ETHER_HEADER_LEN 14

typedef struct ethernet_address {
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
	u_char byte5;
	u_char byte6;
}ethernet_address;

typedef struct ethernet_header {
	//u_long pre_start;		// Preamble (7 bytes) + Start Delimiter (1 byte)
	ethernet_address daddr;	// Destination Address
	ethernet_address saddr;	// Source Address
	u_short dType;			// dType >= 0x05dc : Data Type, dLength < 0x0600 : Data Length.
}ethernet_header;

/* ARP header */
typedef struct arp_header {
	u_short hType;			// Hardware Type.
	u_short pType;			// Protocol Type.
	u_char hlen;			// Hardware address length.
	u_char plen;			// Protocol address length.
	u_short op;				// Operation.
}arp_header;

/* 4 bytes IP address */
typedef struct ip_address {
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

/* IPv4 header */
typedef struct ip_header {
	u_char  ver_ihl;        // Version (4 bits) + Internet header length (4 bits)
	u_char  tos;            // Type of service 
	u_short tlen;           // Total length 
	u_short identification; // Identification
	u_short flags_fo;       // Flags (3 bits) + Fragment offset (13 bits)
	u_char  ttl;            // Time to live
	u_char  proto;          // Protocol
	u_short crc;            // Header checksum
	ip_address  saddr;      // Source address
	ip_address  daddr;      // Destination address
							//u_int   op_pad;         // Option + Padding
}ip_header;

/* ICMP header */
typedef struct icmp_header {
	u_char type;			// Type
	u_char code;			// Code
	u_short checksum;		// CheckSum
	u_int message1;			// Message1
}icmp_header;

/* UDP header*/
typedef struct udp_header {
	u_short sport;          // Source port
	u_short dport;          // Destination port
	u_short len;            // Datagram length
	u_short crc;            // Checksum
}udp_header;

/* TCP header*/
typedef struct tcp_header {
	u_short sport;			// Source port
	u_short dport;			// Destination port
	u_int seq_number;		// Sequence number
	u_int Ack_number;		// Acknowledgment number
	u_char len : 4;			// Header length
	u_char reserverd : 6;	// Reserved
	u_char urg : 1;			// Control (Urgent pointer in valid)
	u_char ack : 1;			// Control (Acknowledgment is valid)
	u_char psh : 1;			// Control (Request for push)
	u_char rst : 1;			// Control (Reset the connection)
	u_char syn : 1;			// Control (Synchronize sequence numbers)
	u_char fin : 1;			// Control (Terminate the connection)
	u_short window_size;	// Windows size
	u_short checksum;		// Checksum
	u_short urgent;			// Urgent pointer
}tcp_header;

void packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *packet_data);

void ethernet_proc(const u_char *ethernet_data);

void arp_proc(const u_char *arp_data);
void ip_proc(const u_char *ip_data);
void icmp_proc(const u_char *icmp_data);

void tcp_proc(const u_char *ethernet_data);
void udp_proc(const u_char *ethernet_data);

void print_mac(ethernet_address saddr, ethernet_address daddr);
void print_ip(ip_address saddr, ip_address daddr);
void print_port(u_short sport, u_short dport);