/* 
 * File:   DataDispatchManager.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 14, 2012, 3:22 PM
 */

#include "DataDispatchManager.h"
#include "WaitChannelManager.h"

CDataDispatchManager DataDispatchManager;


void CDataDispatchManager::OnDataRecv(int fd, const char* pData, int nLen)
{
	int idx = fd % 64;
	m_dataDispatcherList[idx].OnDataRecv(fd, pData, nLen);
	WaitChannelManager.Push(fd);
}

void CDataDispatchManager::Delete(int fd)
{
	int idx = fd % 64;
	m_dataDispatcherList[idx].Delete(fd);
}

int CDataDispatchManager::Parse(int fd, dataBufferPtr_t& pkt)
{
	int idx = fd % 64;
	return m_dataDispatcherList[idx].Parse(fd, pkt);
}