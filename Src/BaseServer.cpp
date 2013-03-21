/* 
 * File:   BaseServer.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 19, 2012, 4:44 PM
 */

#include "BaseServer.h"
#include "PacketParserManager.h"
#include "PacketRouter.h"


void CBaseServer::Init(int readNum, int writeNum, int parseNum, int dispatchNum)
{
	ReadServicePool.Init(readNum);
	ReadDispatchManager.Init(readNum);
	WriteServicePool.Init(writeNum);
	WriteDispatchManager.Init(writeNum);

	DataParserManager.Init(parseNum);
	PacketDispatchManager.Init(dispatchNum);
}

void CBaseServer::SetListenSocket(const char* ipStr, int port)
{
	AcceptService.Init(0,0, ipStr, port);
}

void CBaseServer::SetPacketParseManager(IPacketParserManager* pPacketParserManager)
{
	PacketParserManager.Set(pPacketParserManager);
}

void CBaseServer::SetPacketRouter(IPacketRouter* pRouter)
{
	PacketRouter.Set(pRouter);
}

void CBaseServer::Start()
{
	AcceptService.Run();
	ReadServicePool.Run();
	WriteServicePool.Run();
}

void CBaseServer::Stop()
{
    DataParserManager.Stop();
	PacketDispatchManager.Stop();
	ReadDispatchManager.Stop();
	WriteDispatchManager.Stop();
	AcceptService.Stop();
}

void CBaseServer::Send(int fd, const char* pData, int nLen)
{
	WriteServicePool.Send(fd, pData, nLen);
}

IBaseServer * CreateBaseServer()
{
	return new CBaseServer();
}

void DestroyBaseServer(IBaseServer *p)
{
	delete p;
}
