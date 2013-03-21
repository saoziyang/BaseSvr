/* 
 * File:   AcceptService.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 12, 2012, 6:53 PM
 */

#include "AcceptService.h"
#include "WriteService.h"
#include "ReadServicePool.h"
#include "PacketRouter.h"

CAcceptService AcceptService;

CAcceptService::~CAcceptService()
{
	if (m_socket != -1)
		close(m_socket);
	m_eps.Close();
}

bool CAcceptService::Init(int type, int id, const char *ipStr, int port)
{
	m_eps.Init(type, id);
	
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == m_socket) {
		printf("Error: cannot create socket for listen: %d.\n", errno);
		return false;
	}
	int toSet = 1;
	setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &toSet, sizeof(toSet));

	struct sockaddr_in svrAddr = {0};
    svrAddr.sin_family = AF_INET;
    svrAddr.sin_port   = htons(port);
    inet_aton(ipStr, &(svrAddr.sin_addr) );
	
    if (0 != bind(m_socket, (struct sockaddr *) &svrAddr, sizeof (svrAddr)) ) {
		printf("Error: cannot bind socket: .\n", errno);
		return false;
	}

	if (!__SetNonBlocking(m_socket)) {
		printf("Error: cannot set nonblocking: .\n", errno);
		return false;
    }

	if (-1 == listen(m_socket, SOMAXCONN) ) {
		printf("Error: cannot listen: . \n", errno);
		return false;
    }

    struct epoll_event ev;
    ev.data.fd = m_socket;
    ev.events = EPOLLIN | EPOLLET;

    int ret = m_eps.AddEvent(m_socket, &ev);
	if (0 != ret) {
		printf("Error: cannot add event to epoll service (type=%d, id=%d).\n", type, id);
		return false;
	}
	return true;
}

void CAcceptService::Run()
{
	m_thread = new thread_t(BIND(&CAcceptService::__Run, this));
}

void CAcceptService::__Run()
{
	m_eps.Run(BIND(&CAcceptService::Process, this, _1));
}

void CAcceptService::Process(epoll_event& ev)
{
	struct sockaddr addr = {0};
	socklen_t       addrLen = sizeof(addr);
	
 	while (1) {
       	int inFd = accept4(m_socket, &addr, &addrLen, SOCK_NONBLOCK);
	   	if (-1 == inFd) {
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				break;
		   	printf("Error: accept error: %d.\n", errno);
		   	break;
	   	}
		
		uint32_t ip   = ntohl(*(uint32_t*)&addr.sa_data[2]);
		uint16_t port = ntohs(*(uint16_t*)&addr.sa_data[0]);
		
		PacketRouter.OnClientConnected(inFd, ip, port);
		ReadServicePool.AddClient(inFd);
	}	
}

bool CAcceptService::__SetNonBlocking(int &s)
{
	return ( fcntl(s, F_SETFL, O_NONBLOCK) < 0 ) ? false : true;
}

void CAcceptService::Stop()
{
	close(m_socket);
	m_eps.Close();
}