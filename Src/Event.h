/* 
 * File:   Event.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 13, 2012, 4:02 PM
 */

#ifndef EVENT_H
#define	EVENT_H

#include "Epoll.h"
#include "ClassMacro.h"
#include "Common.h"

class CEvent : public epoll_event {
public:
	CEvent(){
		memset((epoll_event *)this, 0, sizeof(epoll_event));	
	}
	~CEvent(){}
	inline epoll_event * Get() {return this;}
};

class CReadEvent : public CEvent
{
public:
	CReadEvent(){}
	CReadEvent(int fd){
		data.fd = fd;	
		events  = EPOLLIN | EPOLLET;
	}
	~CReadEvent(){ 
		printf("read event destroyed.\n");
	}

private:
	char recvBuf[1024];
};

class CWriteEvent : public CEvent
{
	typedef boost::function<void()> callback_t;
public:
	CWriteEvent(){}
	~CWriteEvent(){}
private:
	callback_t m_cb;
	DISALLOW_COPY_AND_ASSIGN(CWriteEvent)	
};


#endif	/* EVENT_H */

