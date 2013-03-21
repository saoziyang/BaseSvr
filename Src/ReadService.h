/* 
 * File:   ReadService.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 12, 2012, 4:39 PM
 */

#ifndef READSERVICE_H
#define	READSERVICE_H

#define RECV_BUFF_SIZE 1024

#include "EpollService.h"

class CReadService 
{
public:
	CReadService(){}
	~CReadService(){}

	void Init(int type=1, int id=0);
	void Run();

	bool AddClient(int fd);
	bool DelClient(int fd);

	void Process(epoll_event &ev);

private:
	CEpollService m_eps;
	int           m_id;
	char          m_recvBuf[RECV_BUFF_SIZE];
	DISALLOW_COPY_AND_ASSIGN(CReadService)	
};

#endif	/* READSERVICE_H */

