/* 
 * File:   AcceptService.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 12, 2012, 6:48 PM
 */

#ifndef ACCEPTSERVICEEX_H
#define	ACCEPTSERVICEEX_H

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>

#include "EpollService.h"

class CAcceptService
{
	typedef boost::thread   thread_t;
	typedef thread_t *      threadPtr_t;
public:
	CAcceptService(): m_socket(-1){}
	~CAcceptService();
	
	bool Init(int type, int id, const char *ipStr, int port);
	void Run();

	void Process(epoll_event &ev);
	void Stop();

private:
	bool __SetNonBlocking(int &s);
	void __Run();

private:
	int           m_socket;
	CEpollService m_eps;
	threadPtr_t   m_thread;
	DISALLOW_COPY_AND_ASSIGN(CAcceptService)
		
};

extern CAcceptService AcceptService;

#endif	/* ACCEPTSERVICEEX_H */

