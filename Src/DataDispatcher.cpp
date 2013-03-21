/* 
 * File:   DataDispatcher.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 14, 2012, 2:56 PM
 */

#include "DataDispatcher.h"
#include "PacketParserManager.h"

void CDataDispatcher::OnDataRecv(int fd, const char* pData, int nLen)
{
	LOCK_WRITE_SECTION()
	dataQueueMap_t & dataMap = m_dataMap;
	dataQueueMap_t::const_iterator cIt = dataMap.find(fd);
	if (cIt == dataMap.end()) {
		dataQueuePtr_t pDataQueue(new CDataQueue);
		pDataQueue->Append((void*)pData, nLen);
		dataMap.insert(std::make_pair(fd, pDataQueue));
	}else{
		cIt->second->Append((void*)pData, nLen);
	}
}

void CDataDispatcher::Delete(int fd)
{
	LOCK_WRITE_SECTION()
	dataQueueMap_t & dataMap = m_dataMap;
	dataMap.erase(fd);
}

int CDataDispatcher::Parse(int fd, dataBufferPtr_t &pkt)
{
	LOCK_WRITE_SECTION()
	dataQueueMap_t & dataMap = m_dataMap;
	if (dataMap.empty())
		return DPR_EMPTY;

	dataQueueMap_t::const_iterator cIt = dataMap.find(fd);
	if (cIt == dataMap.end())
		return DPR_UNKNOWN;

	int dataType = PacketParserManager.Parse(cIt->second, pkt);
	if (DPR_GOOD_PACKET == dataType) {
		cIt->second->PopFront(pkt->size());
	}else if (DPR_INVALID == dataType) {
		cIt->second->Clear();
		//todo: close the socket.
	}	
	return dataType;
}