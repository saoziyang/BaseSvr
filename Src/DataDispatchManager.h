/* 
 * File:   DataDispatchManager.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 14, 2012, 2:14 PM
 */

#ifndef DATADISPATCHMANAGER_H
#define	DATADISPATCHMANAGER_H

#include "ClassMacro.h"
#include "Common.h"
#include "DataDispatcher.h"

class CDataDispatchManager
{
public:
	CDataDispatchManager(){}
	~CDataDispatchManager(){}

	void OnDataRecv(int fd, const char *pData, int nLen);
	void Delete(int fd);

	int  Parse(int fd, dataBufferPtr_t &pkt);

private:
	CDataDispatcher m_dataDispatcherList[64];
};

extern CDataDispatchManager DataDispatchManager;
#endif	/* DATADISPATCHMANAGER_H */

