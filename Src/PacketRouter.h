/* 
 * File:   PacketRouter.h
 * Author: Ke Liang <ke.liang.215@gmail.com> 
 * Date:   November 14, 2012, 10:54 PM
 */

#ifndef PACKETROUTER_H
#define	PACKETROUTER_H

#include "IPacketRouter.h"
#include "Common.h"

class CPacketRouter  
{
public:
	CPacketRouter():m_pRouter(NULL){}
	~CPacketRouter(){}

public:
	void Set(IPacketRouter * pRouter);

public:
	void OnReceivePacket(int fd, const dataBufferPtr_t & packet);
	void OnClientConnected(int fd, uint32_t ip, uint16_t port);
	void OnClientDisconnected(int fd);
private:
	IPacketRouter * m_pRouter;
};

extern CPacketRouter PacketRouter;

#endif	/* PACKETROUTER_H */

