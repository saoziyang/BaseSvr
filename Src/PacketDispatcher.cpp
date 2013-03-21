/* 
 * File:   PacketDispatcher.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com> 
 * Date:   November 14, 2012, 10:32 PM
 */

#include "PacketDispatcher.h"
#include "PacketRouter.h"

void CPacketDispatcher::Run(int idx)
{
	m_id = idx;
	m_pThread=new boost::thread(boost::bind(& CPacketDispatcher::__Run, this, idx));
}

void CPacketDispatcher::__Run(int idx) {
    while (!m_isClose) {
        dataBufferPtr_t pkt;
        int fd;
        {
			mutex_locker_t __locker(m_lock);
            while (!m_isClose && m_pktQueue.empty()) {
				m_wait.wait(__locker);
            }

            if (!m_pktQueue.empty()) {
                const packetItemData_t & item = m_pktQueue.front();
                fd  = item.first;
                pkt = item.second;
                m_pktQueue.erase(m_pktQueue.begin());
            }
        }
        if (pkt)
            __Dispatch(fd, pkt);
    }
}

void CPacketDispatcher::Stop()
{
	m_isClose = true;
	m_wait.notify_all();
	if (m_pThread) {
		m_pThread->join();
		delete m_pThread;
		m_pThread = NULL;
	}
}

void CPacketDispatcher::__Dispatch(int fd, const dataBufferPtr_t& pktPtr)
{
	PacketRouter.OnReceivePacket(fd, pktPtr);	
}

void CPacketDispatcher::Put(int fd, const dataBufferPtr_t& pktPtr)
{
	mutex_locker_t __locker(m_lock);
	m_pktQueue.push_back(std::make_pair(fd, pktPtr));
	m_wait.notify_one();
}

void CPacketDispatcher::PutFront(int fd, const dataBufferPtr_t& pktPtr)
{
	mutex_locker_t __locker(m_lock);
	m_pktQueue.push_front(std::make_pair(fd, pktPtr));
	m_wait.notify_one();
}

void CPacketDispatcher::Delete(int fd)
{
	mutex_locker_t __locker(m_lock);
	if (m_pktQueue.empty())
		return;
	for (int i = (int)m_pktQueue.size()-1; i >= 0; --i) {
		if (m_pktQueue[i].first == fd)
			m_pktQueue.erase(m_pktQueue.begin()+i);
	}
}

