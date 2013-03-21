/* 
 * File:   ReadService.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 12, 2012, 5:09 PM
 */

#include "ReadService.h"
#include "CleanService.h"
#include "ReadDispatchManager.h"

void CReadService::Init(int type, int id)
{
	m_eps.Init(type, id);
	m_id = id;
}

void CReadService::Run()
{
	m_eps.Run(BIND(&CReadService::Process, this, _1));
}

void CReadService::Process(epoll_event& ev)
{
	int fd = ev.data.fd;
	if (ev.events & EPOLLIN) {
		ReadDispatchManager.Put(fd);
	}else {
		CleanService.Clear(fd);
	}
}

bool CReadService::AddClient(int fd)
{
	struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET;

    int ret = m_eps.AddEvent(fd, &ev);
	
	if (0 != ret) {
		printf("Error: cannot add event to epoll service.\n");
		return false;
	}
	return true;
}

bool CReadService::DelClient(int fd)
{
	struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLIN | EPOLLET;

    int ret = m_eps.DelEvent(fd, &ev);

	if (0 != ret) {
		printf("Error: cannot delete event to epoll service.\n");
		return false;
	}
	return true;
}

