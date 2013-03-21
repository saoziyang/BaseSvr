/*
 * CleanService.cpp
 *
 *  Created on: Mar 21, 2013
 *      Author: ke
 */

#include "CleanService.h"
#include "BaseLogger.h"

CCleanService CleanService;

CCleanService::CCleanService() {
	// TODO Auto-generated constructor stub

}

CCleanService::~CCleanService() {
	// TODO Auto-generated destructor stub
}

void CCleanService::Clear(int fd)
{
	PacketRouter.OnClientDisconnected(fd);
	ReadServicePool.DelClient(fd);
	WriteServicePool.DelClient(fd);
	DataDispatchManager.Delete(fd);
	PacketDispatchManager.Delete(fd);
	SendDataStore.Delete(fd);
	close(fd);
}


