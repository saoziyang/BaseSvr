/* 
 * File:   PaketParserManager.h
 * Author: ke
 *
 * Created on November 14, 2012, 3:59 PM
 */

#ifndef PAKETPARSERMANAGER_H
#define	PAKETPARSERMANAGER_H

#include "IPacketParserManager.h"
#include "DataQueue.h"

class CPacketParserManager {
public:
    CPacketParserManager(): m_pPktParserManager(NULL){}
    ~CPacketParserManager(){}

	void Set(IPacketParserManager *p);
	int  Parse(const dataQueuePtr_t &pDataQueue, dataBufferPtr_t &pkt);	
private:
	IPacketParserManager *m_pPktParserManager;
};

extern CPacketParserManager PacketParserManager;

#endif	/* PAKETPARSERMANAGER_H */

