/* 
 * File:   EventDispatchManager.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 15, 2012, 6:05 PM
 */

#include "ReadDispatchManager.h"

CReadDispatchManager ReadDispatchManager;

void CReadDispatchManager::Init(int nThread)
{
    m_nThread = nThread;
    m_evDispatchers = new CReadDispatcher[nThread];
    for (int i = 0; i < m_nThread; ++i) {
        m_evDispatchers[i].Start();
    }
}

void CReadDispatchManager::Put(int fd)
{
	int idx = fd % m_nThread;
	m_evDispatchers[idx].Put(fd);
}

void CReadDispatchManager::Stop()
{
	for (int i = 0; i< m_nThread; ++i) 
		m_evDispatchers[i].Stop();
	__Free();
}

void CReadDispatchManager::__Free()
{
	if(m_evDispatchers) {
		delete[] m_evDispatchers;
		m_evDispatchers = NULL;
	}
}