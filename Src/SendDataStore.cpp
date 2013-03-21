/* 
 * File:   SendDataStore.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 16, 2012, 1:51 PM
 */

#include "SendDataStore.h"

#define MAX_SEND_UNIT 10
#define MIN(X, Y) (X < Y) ? X : Y

CSendDataStore SendDataStore;

void CSendDataStore::Put(int fd, const char* pData, int nLen)
{
	uint8_t idx = fd % 256;
	write_locker_t __lk(m_lock[idx]);
	pktPtrMap_t &pktMap = m_pktMap[idx];
	pktPtrMap_t::const_iterator cIt = pktMap.find(fd);
	if (cIt == pktMap.end()) {
		dataBufferPtr_t pktPtr(new dataBuffer_t);
		pktPtr->insert(pktPtr->begin(), (uint8_t*)pData, (uint8_t*)pData + nLen);
		pktMap.insert(std::make_pair(fd, pktPtr));
    }else{
		cIt->second->insert(cIt->second->end(), (uint8_t*)pData, (uint8_t*)pData + nLen);
	}
}

void CSendDataStore::Delete(int fd)
{
	uint8_t idx = fd % 256;
	write_locker_t __lk(m_lock[idx]);
	pktPtrMap_t &pktMap = m_pktMap[idx];
	pktMap.erase(fd);
}

int CSendDataStore::Send(int fd)
{
	uint8_t idx = fd % 256;
	write_locker_t __lk(m_lock[idx]);
	pktPtrMap_t &pktMap = m_pktMap[idx];	
	pktPtrMap_t::iterator it = pktMap.find(fd);
	if (it == pktMap.end()) {
		return DATA_SEND_RESULT::NO_DATA;
	}else{
		dataBufferPtr_t pkt = it->second;
		int nLen; 

		if (!it->second || 0 >= (nLen = pkt->size()) ) {
			pktMap.erase(it);
			return DATA_SEND_RESULT::NO_DATA; // data queue is empty.
		}
	
		int nBytes = write(fd, &pkt->front(), nLen);

		if (nBytes > 0) {
			if (nBytes != nLen) {
				pkt->erase(pkt->begin(), pkt->begin() + nBytes);
				return DATA_SEND_RESULT::SEND_PARTIAL;
			}else{
				pkt->clear();
				return DATA_SEND_RESULT::SEND_COMPLETE;
			}
		}else{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				return 0;
			//printf("Send data error=%d, fd=%d.\n", errno, fd);
			pktMap.erase(it);
			return DATA_SEND_RESULT::SEND_ERROR;
		}	
	}
}