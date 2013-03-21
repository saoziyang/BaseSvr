/* 
 * File:   WriteServicePool.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 19, 2012, 2:13 PM
 */

#ifndef WRITESERVICEPOOL_H
#define	WRITESERVICEPOOL_H

#include "WriteService.h"
#include "SendDataStore.h"

class CWriteServicePool
{
	typedef boost::thread   thread_t;
	typedef thread_t *      threadPtr_t;
public:
	CWriteServicePool(): m_writeNum(1){}
	~CWriteServicePool(){}

	bool Init(int num=1);
	void Run();
	
	bool AddClient(int fd);
	void Send(int fd, const char *pData, int nLen);

private:
	CWriteService * m_writeList;
	threadPtr_t     m_writeThList;
	int             m_writeNum;
};

extern CWriteServicePool WriteServicePool;


#endif	/* WRITESERVICEPOOL_H */

