/* 
 * File:   WriteService.h
 * Author: Ke Liang <ke.liang.215@gmail.com> 
 * Date:   November 13, 2012, 11:31 AM
 */

#ifndef WRITESERVICE_H
#define	WRITESERVICE_H

#include "EpollService.h"

class CWriteService 
{
public:
	CWriteService(){}
	~CWriteService(){
		if (m_eps.IsOpen())	
			m_eps.Close();
	}

	bool Init(int type=2, int id=0);
	void Run();

	bool AddClient(int fd);
    bool Send(int fd, const char *pData, int nLen);

	void Process(epoll_event &ev);

private:
	CEpollService m_eps;
	int           m_id;
	DISALLOW_COPY_AND_ASSIGN(CWriteService)	
};

#endif	/* WRITESERVICE_H */

