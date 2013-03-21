/* 
 * File:   ReadServicePool.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 19, 2012, 1:30 PM
 */

#ifndef READSERVICEPOOL_H
#define	READSERVICEPOOL_H

#include "ReadService.h"

class CReadServicePool
{
	typedef boost::thread   thread_t;
	typedef thread_t *      threadPtr_t;
public:
	CReadServicePool(): m_readNum(1){}
	~CReadServicePool(){}

	bool Init(int num=1);
	void Run();
	
	bool AddClient(int fd);

private:
	CReadService * m_readList;
	threadPtr_t    m_readThList;
	int            m_readNum;
};

extern CReadServicePool ReadServicePool;

#endif	/* READSERVICEPOOL_H */

