/* 
 * File:   DataParser.cpp
 * Author: ke
 * 
 * Created on November 14, 2012, 5:45 PM
 */

#include "DataParser.h"
#include "WaitChannelManager.h"
#include "DataDispatchManager.h"
#include "PacketDispatchManager.h"

void CDataParser::Start()
{
	m_isClose = false;
	m_pThread = new thread_t(BIND(&CDataParser::__Run, this));
}

void CDataParser::Stop()
{
	m_isClose = true;
	if (m_pThread) {
		m_pThread->join();
		delete m_pThread;
		m_pThread = NULL;
	}	
}

void CDataParser::__Run()
{
	while (!m_isClose) {
		int fd = 0;
		bool ret = WaitChannelManager.GetSock(m_id, fd);
		if (!ret)
			continue;

		if (m_isClose)
			break;
		
		while (1) {
			dataBufferPtr_t pkt;
			int pktType = DataDispatchManager.Parse(fd, pkt);
			if (DPR_GOOD_PACKET == pktType && pkt) {
				PacketDispatchManager.Dispatch(fd, pkt);
			}else{
				break;
			}
		}
		
	}
}