/* 
 * File:   WaitChannel.h
 * Author: ke
 *
 * Created on November 14, 2012, 6:19 PM
 */

#ifndef WAITCHANNEL_H
#define	WAITCHANNEL_H

#include "Common.h"

class CWaitChannel {
	typedef std::queue<int> fdQueue_t;
public:
    CWaitChannel(): m_isClose(false){}
    ~CWaitChannel(){}

	void Push(const int &fd);
	bool GetSock(int &fd);
	void Stop();

private:
	bool       m_isClose;
	fdQueue_t  m_fdQueue;
	locker_t   m_lock;
	wait_t     m_wait;	
};

#endif	/* WAITCHANNEL_H */

