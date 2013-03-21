/* 
 * File:   WaitChannelManager.cpp
 * Author: ke
 * 
 * Created on November 14, 2012, 6:33 PM
 */

#include "WaitChannelManager.h"


CWaitChannelManager WaitChannelManager;

void CWaitChannelManager::Init(int n)
{
	m_nWaitChannel = n;
	m_channelVec.resize(n);
	for (int i = 0; i < n; ++i) {
		m_channelVec[i] = new CWaitChannel;
	}
}

void CWaitChannelManager::Push(const int &fd)
{
	int idx = fd % m_nWaitChannel;
	m_channelVec[idx]->Push(fd);
}

bool CWaitChannelManager::GetSock(int idx, int &fd)
{
	if(m_nWaitChannel <= idx)
		return false;

	return m_channelVec[idx]->GetSock(fd);
}

void CWaitChannelManager::Stop()
{
	for (int i = 0; i < m_nWaitChannel; ++i)
		m_channelVec[i]->Stop();
}
