/* 
 * File:   PacketRouter.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com> 
 * Date:   November 14, 2012, 10:58 PM
 */

#include "PacketRouter.h"
#include <stdio.h>

CPacketRouter PacketRouter;

void CPacketRouter::Set(IPacketRouter* pRouter)
{
	m_pRouter=pRouter;
}

void CPacketRouter::OnReceivePacket(int fd, const dataBufferPtr_t& packet)
{
	if (m_pRouter)
		m_pRouter->OnReceivePacket(fd, (const char*)&packet->front(), packet->size());
}

void CPacketRouter::OnClientConnected(int fd, uint32_t ip, uint16_t port)
{
	if (m_pRouter)
		m_pRouter->OnClientConnected(fd, ip, port);
}

void CPacketRouter::OnClientDisconnected(int fd)
{
	if (m_pRouter)
		m_pRouter->OnClientDisconnected(fd);
}
