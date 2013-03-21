/* 
 * File:   PacketDispatcher.h
 * Author: Ke Liang <ke.liang.215@gmail.com> 
 * Date:   November 14, 2012, 10:25 PM
 */

#ifndef PACKETDISPATCHER_H
#define	PACKETDISPATCHER_H

#include "Common.h"

class CPacketDispatcher
{
	typedef std::pair<int, dataBufferPtr_t> packetItemData_t;
  	typedef std::deque<packetItemData_t>    packetQueue_t;
	typedef boost::thread *                 threadPtr_t;
public:
	CPacketDispatcher(): m_isClose(false), m_pThread(NULL){}
	~CPacketDispatcher(){}

	void Run(int idx);
	void Stop();
	void Put(int fd, const dataBufferPtr_t &pktPtr);
    void PutFront(int fd,const dataBufferPtr_t &pktPtr);
	void Delete(int fd);

private:
	void __Run(int idx);
	void __Dispatch(int fd, const dataBufferPtr_t &pktPtr);
	
private:
    int           m_id;
	bool 		  m_isClose;
	mutex_t       m_lock;
	wait_t   	  m_wait;
	packetQueue_t m_pktQueue;
	threadPtr_t   m_pThread;	
};

#endif	/* PACKETDISPATCHER_H */

