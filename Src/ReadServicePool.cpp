/* 
 * File:   ReadServicePool.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 19, 2012, 1:34 PM
 */

#include "ReadServicePool.h"

CReadServicePool ReadServicePool;

bool CReadServicePool::Init(int num)
{
	m_readNum = num;
	m_readList = new CReadService[num];
	m_readThList = new thread_t[num];
	for (int i = 0; i < m_readNum; ++i) {
        m_readList[i].Init(1, i);
    }
}

void CReadServicePool::Run()
{
	for (int i = 0; i < m_readNum; ++i) {
		m_readThList[i] = thread_t(BIND(&CReadService::Run, &m_readList[i]));
	}
}

bool CReadServicePool::AddClient(int fd)
{
	int idx = fd % m_readNum;
	return m_readList[idx].AddClient(fd);
}
