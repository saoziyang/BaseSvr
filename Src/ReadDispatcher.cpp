/* 
 * File:   EventDispatcher.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 15, 2012, 4:44 PM
 */

#include "ReadDispatcher.h"
#include "DataDispatchManager.h"
#include "PacketDispatchManager.h"
#include "SendDataStore.h"
#include "PacketRouter.h"

void CReadDispatcher::Start()
{
	m_isClose = false;
	m_threadPtr = new thread_t(BIND(&CReadDispatcher::__Run, this));
}
void CReadDispatcher::Put(const int &fd)
{
	mutex_locker_t __locker(m_lock);
	m_evQueue.push(fd);
	m_wait.notify_one();
}

void CReadDispatcher::__Run()
{
	while (!m_isClose) {
		int fd;
		mutex_locker_t __locker(m_lock);
		while (!m_isClose && m_evQueue.empty()) {
			m_wait.wait(__locker);	
		}	

		if (m_isClose)
			break;
		
		fd = m_evQueue.front();
		m_evQueue.pop();
		bool isOK = false;
		std::vector<char> dataBuf;
		while (1) {
            int nLen = read(fd, m_recvBuf, READ_BUF_SIZE);
            if (0 == nLen) {

				PacketRouter.OnClientDisconnected(fd);
				DataDispatchManager.Delete(fd);
				PacketDispatchManager.Delete(fd);
				SendDataStore.Delete(fd);
				close(fd);
				
				isOK = false;
                break;
            } else if (-1 == nLen) {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    isOK = true;
                break;
            } else {
				dataBuf.insert(dataBuf.end(), m_recvBuf, m_recvBuf + nLen);
            }
        }

		if (isOK)
			DataDispatchManager.OnDataRecv(fd, &dataBuf[0], (int)dataBuf.size());

	}
}

void CReadDispatcher::Stop()
{
    m_isClose = true;
    m_wait.notify_all();
    if (m_threadPtr) {
        m_threadPtr->join();
        delete m_threadPtr;
        m_threadPtr = NULL;
    }
}
