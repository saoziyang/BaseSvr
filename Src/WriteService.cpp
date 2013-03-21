/* 
 * File:   WriteService.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 13, 2012, 1:46 PM
 */

#include "WriteService.h"
#include "CleanService.h"
#include "WriteDispatchManager.h"

void CWriteService::Init(int type, int id)
{
	m_eps.Init(type, id);
	m_id = id;
}

void CWriteService::Run()
{
	m_eps.Run(BIND(&CWriteService::Process, this, _1));
}

void CWriteService::Process(epoll_event& ev)
{
	int fd = ev.data.fd;
	if (ev.events & EPOLLOUT) {
		WriteDispatchManager.Put(fd);
	}else{
		CleanService.Clear(fd);
	}
}

bool CWriteService::AddClient(int fd)
{
	struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLOUT | EPOLLET;

    int ret = m_eps.AddEvent(fd, &ev);
	
	if (0 != ret) {
		printf("Error: cannot add event to write service, eCode=%d.\n", ret);
		return false;
	}
	return true;
}

bool CWriteService::DelClient(int fd)
{
	struct epoll_event ev;
    ev.data.fd = fd;
    ev.events = EPOLLOUT | EPOLLET;

    int ret = m_eps.DelEvent(fd, &ev);

	if (0 != ret) {
		printf("Error: cannot delete event to write service, eCode=%d.\n", ret);
		return false;
	}
	return true;
}

/*
bool CWriteService::Send(int fd, const char* pData, int nLen)
{
	int nBytes = write(fd, pData, nLen);
}
*/
