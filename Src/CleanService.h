/*
 * CleanService.h
 *
 *  Created on: Mar 21, 2013
 *      Author: ke
 */

#ifndef CLEANSERVICE_H_
#define CLEANSERVICE_H_

#include "ReadServicePool.h"
#include "ReadDispatchManager.h"
#include "WriteServicePool.h"
#include "WriteDispatchManager.h"
#include "DataDispatchManager.h"
#include "PacketDispatchManager.h"
#include "SendDataStore.h"
#include "PacketRouter.h"


class CCleanService {
public:
	CCleanService();
	virtual ~CCleanService();

	void Clear(int fd);
};

extern CCleanService CleanService;
#endif /* CLEANSERVICE_H_ */
