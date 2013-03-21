/* 
 * File:   EpollService.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 12, 2012, 4:45 PM
 */

#ifndef EPOLLSERVICE_H
#define	EPOLLSERVICE_H

#include "Epoll.h"

class CEpollService 
{
	typedef boost::function<void(epoll_event&)> callback_t;
public:
	CEpollService(){}
	~CEpollService(){}

	bool Init(int type = 0, int id = 0);
	int  AddEvent(int fd, epoll_event *pEv);
	int  DelEvent(int fd, epoll_event *pEv);
	void Run(const callback_t &cb);
	
	bool IsOpen() {return m_epoll.IsOpen();}
	void Close(){m_epoll.Close();}
	
private:
	CEpoll     m_epoll;
	DISALLOW_COPY_AND_ASSIGN(CEpollService)
};


#endif	/* EPOLLSERVICE_H */

