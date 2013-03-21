/* 
 * File:   DataDispatcher.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 14, 2012, 2:20 PM
 */

#ifndef DATADISPATCHER_H
#define	DATADISPATCHER_H

#include "ClassMacro.h"
#include "Common.h"
#include "DataQueue.h"

class CDataDispatcher
{
public:
	CDataDispatcher(){}
	~CDataDispatcher(){}

	void OnDataRecv(int fd, const char *pData, int nLen);
	void Delete(int fd);

	int  Parse(int fd, dataBufferPtr_t &pkt);
private:
	dataQueueMap_t  m_dataMap;
	locker_t  		m_lock;	
};



#endif	/* DATADISPATCHER_H */

