/* 
 * File:   PacketDispatchManager.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 15, 2012, 10:19 AM
 */

#include "PacketDispatchManager.h"

CPacketDispatchManager PacketDispatchManager;

void CPacketDispatchManager::Init( int nThread )
{
	m_nThread = nThread;
	m_pDispatchers = new CPacketDispatcher[nThread];
	for (int i = 0; i < m_nThread; ++i) {
		m_pDispatchers[i].Run(i);
	}
}

void CPacketDispatchManager::__Free()
{
	if(m_pDispatchers) {
		delete[] m_pDispatchers;
		m_pDispatchers = NULL;
	}
}

void CPacketDispatchManager::Stop()
{
	for (int i=0;i<m_nThread;++i) 
		m_pDispatchers[i].Stop();
	__Free();
}

void CPacketDispatchManager::Delete(int fd)
{
	int idx = fd % m_nThread;
	m_pDispatchers[idx].Delete(fd);
}

void CPacketDispatchManager::Dispatch(int fd, const dataBufferPtr_t &packet )
{
	int idx = fd % m_nThread;
	m_pDispatchers[idx].Put(fd, packet);
}

void CPacketDispatchManager::DispatchHigh(int fd, const dataBufferPtr_t &packet )
{
	Dispatch(fd, packet);
}