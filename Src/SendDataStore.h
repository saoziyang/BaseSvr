/* 
 * File:   SendDataStore.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 16, 2012, 1:37 PM
 */

#ifndef SENDDATASTORE_H
#define	SENDDATASTORE_H

#include "Common.h"
#include "DataQueue.h"

class CSendDataStore
{
	typedef std::map<int, dataBufferPtr_t> pktPtrMap_t; 
public:
	CSendDataStore(){}
	~CSendDataStore(){}

	void Put(int fd, const char *pData, int nLen);
	void Delete(int fd);

	int  Send(int fd);

private:
	pktPtrMap_t    m_pktMap[256];
	locker_t       m_lock[256];
};

extern CSendDataStore SendDataStore;

#endif	/* SENDDATASTORE_H */

