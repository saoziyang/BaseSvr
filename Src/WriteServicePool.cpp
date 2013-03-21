/* 
 * File:   WriteServicePool.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 19, 2012, 2:18 PM
 */

#include "WriteServicePool.h"

CWriteServicePool WriteServicePool;

void CWriteServicePool::Init(int num)
{
	m_writeNum = num;
	m_writeThList = new thread_t[num];
	m_writeList = new CWriteService[num];
	for (int i = 0; i < m_writeNum; ++i) {
        m_writeList[i].Init(2, i);
    }
}

void CWriteServicePool::Run()
{
	for (int i = 0; i < m_writeNum; ++i) {
		m_writeThList[i] = thread_t(BIND(&CWriteService::Run, &m_writeList[i]));
	}
}

bool CWriteServicePool::AddClient(int fd)
{
	uint8_t idx = fd % m_writeNum;
	return m_writeList[idx].AddClient(fd);
}

bool CWriteServicePool::DelClient(int fd)
{
	uint8_t idx = fd % m_writeNum;
	return m_writeList[idx].DelClient(fd);
}

void CWriteServicePool::Send(int fd, const char* pData, int nLen)
{
	if (!pData || nLen <= 0)
		return;

	SendDataStore.Put(fd, pData, nLen);

	if (!AddClient(fd))
		SendDataStore.Delete(fd);
}
