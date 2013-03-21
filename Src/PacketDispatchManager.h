/* 
 * File:   PacketDispatchManager.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 15, 2012, 10:16 AM
 */

#ifndef PACKETDISPATCHMANAGER_H
#define	PACKETDISPATCHMANAGER_H

#include "Common.h"
#include "PacketDispatcher.h"

class CPacketDispatchManager {
    typedef CPacketDispatcher * packetDispatcherPtr_t;
    typedef std::vector<int> 	packetQueueInfo_t;
public:
    CPacketDispatchManager() {} 
    ~CPacketDispatchManager() {}

    void Init(int nThread);
    void Stop();
    void Delete(int fd);

    void Dispatch(int fd, const dataBufferPtr_t & pPacket);
    void DispatchHigh(int fd, const dataBufferPtr_t & packet);

private:
    void __Free();

private:
    packetDispatcherPtr_t m_pDispatchers;
    int                   m_nThread;
};

extern CPacketDispatchManager PacketDispatchManager;


#endif	/* PACKETDISPATCHMANAGER_H */

