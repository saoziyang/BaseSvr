/* 
 * File:   ParserManager.h
 * Author: Ke Liang <ke.liang.215@gmail.com>
 * Date:   November 14, 2012, 3:37 PM
 */

#ifndef PARSERMANAGER_H
#define	PARSERMANAGER_H

#include "DataParser.h"

class CDataParserManager
{
	typedef boost::shared_ptr<CDataParser>  dpThreadPtr_t;
	typedef std::vector<dpThreadPtr_t>      dpThreadPtrList_t;
public:
	CDataParserManager(): m_nThread(4){}
	~CDataParserManager(){}

	void Init(int nThread);
	void Stop();

private:
	int 			  m_nThread;
	dpThreadPtrList_t m_threadPtrList;
};

extern CDataParserManager DataParserManager;

#endif	/* PARSERMANAGER_H */

