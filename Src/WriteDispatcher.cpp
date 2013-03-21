/* 
 * File:   WriteDispatcher.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 16, 2012, 2:50 PM
 */

#include "WriteDispatcher.h"
#include "SendDataStore.h"
#include "WriteServicePool.h"
#include "CleanService.h"

void CWriteDispatcher::Start()
{
	m_isClose = false;
	m_threadPtr = new thread_t(BIND(&CWriteDispatcher::__Run, this));
}
void CWriteDispatcher::Put(const int& fd)
{
	mutex_locker_t __locker(m_lock);
	m_evQueue.push(fd);
	m_wait.notify_one();	
}

void CWriteDispatcher::__Run()
{
    while (!m_isClose) {
        int fd;
		{
			mutex_locker_t __locker(m_lock);
			while (!m_isClose && m_evQueue.empty()) 
				m_wait.wait(__locker);
		}

        if (m_isClose)
            break;

        fd = m_evQueue.front();
        m_evQueue.pop();

        int ret = SendDataStore.Send(fd);
		if (ret == DATA_SEND_RESULT::SEND_ERROR) {
			CleanService.Clear(fd);
		}
		if (ret == DATA_SEND_RESULT::SEND_PARTIAL)
			WriteServicePool.AddClient(fd);	

    }	
}

void CWriteDispatcher::Stop()
{
    m_isClose = true;
    m_wait.notify_all();
    if (m_threadPtr) {
        m_threadPtr->join();
        delete m_threadPtr;
        m_threadPtr = NULL;
    }
}
