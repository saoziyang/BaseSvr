/* 
 * File:   IPacketRouter.h
 * Author: Ke Liang <ke.liang.215@gmail.com> 
 * Date:   November 14, 2012, 10:53 PM
 */

#ifndef IPACKETROUTER_H
#define	IPACKETROUTER_H

#include "Common.h"

class IPacketRouter
{
public:
	virtual ~IPacketRouter(){}
public:
	virtual void OnReceivePacket(int fd, const char *pData, int nLen)=0;
	virtual void OnClientConnected(int fd, uint32_t ip, uint16_t port)=0;
	virtual void OnClientDisconnected(int fd)=0;
};

#endif	/* IPACKETROUTER_H */

