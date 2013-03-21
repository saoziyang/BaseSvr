/* 
 * File:   IBaseServer.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 19, 2012, 5:56 PM
 */

#ifndef IBASESERVER_H
#define	IBASESERVER_H

#include "IPacketRouter.h"
#include "IPacketParserManager.h"

class IBaseServer
{
public:
	IBaseServer(){}
	virtual ~IBaseServer(){}
public:
	virtual void Init(int readNum, int writeNum, int parseNum, int dispatchNum)=0;	
	virtual void SetListenSocket(const char * ipStr, int port)=0;
	virtual void SetPacketRouter(IPacketRouter *pRouter)=0;
	virtual void SetPacketParseManager(IPacketParserManager * pPacketParserManager)=0;
	virtual void Start()=0;
	virtual void Stop()=0;
	virtual void Send(int fd, const char *pData, int nLen)=0;

};

extern "C" {
	IBaseServer * CreateBaseServer();
	void DestroyBaseServer(IBaseServer * p);
}

#endif	/* IBASESERVER_H */

