/* 
 * File:   EpollService.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 12, 2012, 4:50 PM
 */

#include "EpollService.h"

bool CEpollService::Init(int type, int id)
{
	int ret = m_epoll.Create(type, id);
	if (0 != ret) {
		printf("Error: cannot create epoll: %d.\n", ret);
		return false;
    }
}

int CEpollService::AddEvent(int fd, epoll_event* pEv)
{
	return m_epoll.AddEvent(fd, pEv);
}

void CEpollService::Run(const callback_t& cb)
{
	m_epoll.Run(cb);
}
