/* 
 * File:   WriteService.cpp
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 13, 2012, 1:46 PM
 */

#include "WriteService.h"
#include "WriteDispatchManager.h"
#include "ReadDispatchManager.h"
#include "DataDispatchManager.h"
#include "PacketDispatchManager.h"
#include "SendDataStore.h"
#include "PacketRouter.h"

bool CWriteService::Init(int type, int id)
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
		PacketRouter.OnClientDisconnected(fd);
		DataDispatchManager.Delete(fd);
		PacketDispatchManager.Delete(fd);
		SendDataStore.Delete(fd);
		close(fd);
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

bool CWriteService::Send(int fd, const char* pData, int nLen)
{
	int nBytes = write(fd, pData, nLen);
	printf("sent to socket=%d: %.*s.\n", fd, nLen, pData);
}
