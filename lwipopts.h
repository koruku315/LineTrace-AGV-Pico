#ifndef _LWIPOPTS_H
#define _LWIPOPTS_H

// FreeRTOS と一緒に使う（NO_SYS=0 = OSあり）
#define NO_SYS                      0
#define LWIP_SOCKET                 0
#define LWIP_NETCONN                1

// メモリ設定
#define MEM_LIBC_MALLOC             0
#define MEM_ALIGNMENT               4
#define MEM_SIZE                    4000
#define MEMP_NUM_TCP_SEG            32
#define MEMP_NUM_ARP_QUEUE          10
#define PBUF_POOL_SIZE              24

// プロトコル有効化
#define LWIP_ARP                    1
#define LWIP_ETHERNET               1
#define LWIP_ICMP                   1
#define LWIP_RAW                    1
#define LWIP_DHCP                   1
#define LWIP_IPV4                   1
#define LWIP_TCP                    1
#define LWIP_UDP                    1
#define LWIP_DNS                    1

// TCP設定
#define TCP_WND                     (8 * TCP_MSS)
#define TCP_MSS                     1460
#define TCP_SND_BUF                 (8 * TCP_MSS)
#define TCP_SND_QUEUELEN            ((4 * (TCP_SND_BUF) + (TCP_MSS - 1)) / (TCP_MSS))

// ネットワークインターフェース
#define LWIP_NETIF_STATUS_CALLBACK  1
#define LWIP_NETIF_LINK_CALLBACK    1
#define LWIP_NETIF_HOSTNAME         1
#define LWIP_NETCONN_FULLDUPLEX     1
#define LWIP_NETCONN_SEM_PER_THREAD 1

// DHCPサーバー（APモードでスマホにIPを配るため）
#define LWIP_DHCP                   1

// HTTPサーバー（httpd）
#define LWIP_HTTPD                  1
#define LWIP_HTTPD_SSI              0
#define LWIP_HTTPD_CGI             1
#define HTTPD_USE_CUSTOM_FSDATA     0

// FreeRTOS統合用
#define TCPIP_THREAD_STACKSIZE      1024
#define DEFAULT_THREAD_STACKSIZE    1024
#define DEFAULT_RAW_RECVMBOX_SIZE   8
#define TCPIP_MBOX_SIZE             8
#define DEFAULT_TCP_RECVMBOX_SIZE   8
#define DEFAULT_UDP_RECVMBOX_SIZE   8
#define DEFAULT_ACCEPTMBOX_SIZE     8

// チェックサム
#define LWIP_CHKSUM_ALGORITHM       3

// 統計（デバッグ用、軽量化のためオフ）
#define MEM_STATS                   0
#define SYS_STATS                   0
#define MEMP_STATS                  0
#define LINK_STATS                  0

#endif /* _LWIPOPTS_H */