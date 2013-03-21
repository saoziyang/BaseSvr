/* 
 * File:   WriteDispatcher.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 16, 2012, 1:28 PM
 */

#ifndef WRITEDISPATCHER_H
#define	WRITEDISPATCHER_H

#include "Common.h"

class CWriteDispatcher
{
	typedef boost::thread   thread_t;
	typedef thread_t *      threadPtr_t;
    typedef std::queue<int> evQueue_t;
public:
	CWriteDispatcher(): m_isClose(true){}
	~CWriteDispatcher(){}

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
};

#endif	/* WRITEDISPATCHER_H */

