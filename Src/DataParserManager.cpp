/* 
 * File:   DataParserManager.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 14, 2012, 6:15 PM
 */

#include "DataParserManager.h"
#include "WaitChannelManager.h"

CDataParserManager DataParserManager;

void CDataParserManager::Init(int nThread)
{
	WaitChannelManager.Init(nThread);
	m_nThread = nThread;
	m_threadPtrList.clear();
	for (int i = 0; i < m_nThread; ++i) {
		dpThreadPtr_t pThread(new CDataParser(i));
		m_threadPtrList.push_back(pThread);
	}
	for (int i = 0; i < m_nThread; ++i) {
		m_threadPtrList[i]->Start();
	}
}

void CDataParserManager::Stop()
{
	WaitChannelManager.Stop();
	for (int i=0;i<m_nThread;++i) {
		m_threadPtrList[i]->Stop();
	}
	m_threadPtrList.clear();
}
