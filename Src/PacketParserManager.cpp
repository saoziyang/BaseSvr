/* 
 * File:   PaketParserManager.cpp
 * Author: ke
 * 
 * Created on November 14, 2012, 3:59 PM
 */

#include "PacketParserManager.h"
#include "IPacketParserManager.h"

#define MAX_PKT_LEN (10*1024)

CPacketParserManager PacketParserManager;

void CPacketParserManager::Set(IPacketParserManager* p)
{
	m_pPktParserManager = p;
}

int  CPacketParserManager::Parse(const dataQueuePtr_t& pDataQueue, dataBufferPtr_t& pkt)
{
	if (pDataQueue->IsEmpty())	
		return DPR_EMPTY;
	if (pDataQueue->GetSize() < 5)
		return DPR_NOT_COMPLETE;

	if (m_pPktParserManager)	
		return m_pPktParserManager->Parse(pDataQueue, pkt);

	int pktLen = 0;
	pDataQueue->CopyTo(&pktLen, 4);	
	if (pktLen > MAX_PKT_LEN || pktLen <= 0) {
		return DPR_INVALID;
	}else if (pktLen + 4 > pDataQueue->GetSize()) {
		return DPR_NOT_COMPLETE;
	}

	pkt.reset(new dataBuffer_t);
	pDataQueue->CopyTo(pkt, pktLen+4);
	return DPR_GOOD_PACKET;
}
