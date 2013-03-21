/* 
 * File:   EventDispatchManager.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 15, 2012, 4:29 PM
 */

#ifndef EVENTDISPATCHMANAGER_H
#define	EVENTDISPATCHMANAGER_H

#include "ReadDispatcher.h"

class CReadDispatchManager
{
public:
	CReadDispatchManager(){}	
	~CReadDispatchManager(){}	

	void Init(int nThread);
    void Stop();
    void Delete(int fd);
	
	void Put(int fd);

private:
	void __Free();
	
private:
	CReadDispatcher * m_evDispatchers;
	int               m_nThread;
};

extern CReadDispatchManager ReadDispatchManager;

#endif	/* EVENTDISPATCHMANAGER_H */

