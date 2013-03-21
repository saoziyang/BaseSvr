/* 
 * File:   IPacketParseManager.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 14, 2012, 4:02 PM
 */

#ifndef IPACKETPARSEMANAGER_H
#define	IPACKETPARSEMANAGER_H

#include "Common.h"
#include "DataQueue.h"

class IPacketParserManager
{
	typedef boost::shared_ptr<CDataQueue> dataQueuePtr_t;
public:
	virtual ~IPacketParserManager(){}
	
	virtual int Parse(const dataQueuePtr_t &pDataQueue, dataBufferPtr_t &pkt);	
};

#endif	/* IPACKETPARSEMANAGER_H */

