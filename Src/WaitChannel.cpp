/* 
 * File:   WaitChannel.cpp
 * Author: ke
 * 
 * Created on November 14, 2012, 6:19 PM
 */

#include "WaitChannel.h"

void CWaitChannel::Push(const int& fd)
{
	LOCK_WRITE_SECTION();
	m_fdQueue.push(fd);
	NOTIFY_SECTION();		
}

bool CWaitChannel::GetSock(int& fd)
{
	LOCK_WRITE_SECTION();
	while (!m_isClose && m_fdQueue.empty()) {
		WAIT_SECTION();
	}
	if (m_isClose)
		return false;
	fd = m_fdQueue.front();
	m_fdQueue.pop();
	return true;
}

void CWaitChannel::Stop()
{
	m_isClose = true;
	NOTIFY_SECTION();
}