/* 
 * File:   WriteDispatchManager.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 16, 2012, 1:28 PM
 */

#ifndef WRITEDISPATCHMANAGER_H
#define	WRITEDISPATCHMANAGER_H

#include "WriteDispatcher.h"

class CWriteDispatchManager
{
public:
	CWriteDispatchManager(){}
	~CWriteDispatchManager(){}

    void Init(int nThread);
    void Stop();
    void Delete(int fd);

    void Put(int fd);

private:
    void __Free();

private:
    CWriteDispatcher * m_evDispatchers;
    int                m_nThread;
	
};

extern CWriteDispatchManager WriteDispatchManager;

#endif	/* WRITEDISPATCHMANAGER_H */

