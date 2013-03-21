/* 
 * File:   EventDispatcher.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 15, 2012, 4:31 PM
 */

#ifndef EVENTDISPATCHER_H
#define	EVENTDISPATCHER_H

#include "Common.h"
#define READ_BUF_SIZE (10*1024)

class CReadDispatcher
{
	typedef boost::thread   thread_t;
	typedef thread_t *      threadPtr_t;
    typedef std::queue<int> evQueue_t;
public:
	CReadDispatcher(): m_isClose(true){}
	~CReadDispatcher(){}

	void Start();
	void Stop();
	void Put(const int &fd);

private:
	void __Run();

private:
	evQueue_t    m_evQueue;
	bool         m_isClose;
	wait_t       m_wait;
	mutex_t      m_lock;
	threadPtr_t  m_threadPtr;
	char         m_recvBuf[READ_BUF_SIZE];
};

#endif	/* EVENTDISPATCHER_H */

