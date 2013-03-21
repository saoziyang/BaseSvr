/* 
 * File:   WriteDispatchManager.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 16, 2012, 3:50 PM
 */

#include "WriteDispatchManager.h"

CWriteDispatchManager WriteDispatchManager;

void CWriteDispatchManager::Init(int nThread)
{
    m_nThread = nThread;
    m_evDispatchers = new CWriteDispatcher[nThread];
    for (int i = 0; i < m_nThread; ++i) {
        m_evDispatchers[i].Start();
    }
}

void CWriteDispatchManager::Put(int fd)
{
	int idx = fd % m_nThread;
	m_evDispatchers[idx].Put(fd);
}

void CWriteDispatchManager::Stop()
{
	for (int i = 0; i< m_nThread; ++i) 
		m_evDispatchers[i].Stop();
	__Free();
}

void CWriteDispatchManager::__Free()
{
	if(m_evDispatchers) {
		delete[] m_evDispatchers;
		m_evDispatchers = NULL;
	}
}