/* 
 * File:   Epoll.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 8, 2012, 11:16 AM
 */

#ifndef EPOLL_H
#define	EPOLL_H

#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "Common.h"
#include "ClassMacro.h"
#include "SocketInfo.h"

#define MAXEVENTS 256

class CEpoll {
	typedef boost::function<void(epoll_event&)> callback_t;
public:
    CEpoll(int n = MAXEVENTS) : m_efd(-1), m_evList(NULL), m_maxEvents(n) {}
    ~CEpoll() {Close();free(m_evList);}

public:
    int  Create(int type = 0, int id = 0);
    int  AddEvent(int fd, epoll_event *pEv);
	bool IsOpen();
    void Close();    
     
	void Run(const callback_t &cb);

private:
    int m_efd;
    int m_maxEvents;
	int m_id;
	int m_type;	
    struct epoll_event *m_evList;
    DISALLOW_COPY_AND_ASSIGN(CEpoll)
};

#endif	/* EPOLL_H */

