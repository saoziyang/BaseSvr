/* 
 * File:   BaseServer.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 19, 2012, 4:35 PM
 */

#ifndef BASESERVER_H
#define	BASESERVER_H

#include "Common.h"
#include "IBaseServer.h"
#include "ILogger.h"

#include "AcceptService.h"
#include "ReadServicePool.h"
#include "WriteServicePool.h"

#include "ReadDispatchManager.h"
#include "DataParserManager.h"
#include "PacketDispatchManager.h"
#include "SendDataStore.h"
#include "WriteDispatchManager.h"

#include "BaseLogger.h"

class CBaseServer: public IBaseServer
{
public:
	CBaseServer(){}
	~CBaseServer(){}

	void Init(int readNum=2, int writeNum=2, int parseNum=4, int dispatchNum=4);	
	void SetListenSocket(const char * ipStr, int port);
	void SetPacketRouter(IPacketRouter *pRouter);
	void SetPacketParseManager(IPacketParserManager * pPacketParserManager);
	void SetBaseLogger(ILogger *pLogger);
	void Start();
	void Stop();
	void Send(int fd, const char *pData, int nLen);

};


#endif	/* BASESERVER_H */

