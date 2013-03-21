/* 
 * File:   DataParser.h
 * Author: ke
 *
 * Created on November 14, 2012, 5:45 PM
 */

#ifndef DATAPARSER_H
#define	DATAPARSER_H

#include "Common.h"

class CDataParser {
	typedef boost::thread   thread_t;
	typedef thread_t *      threadPtr_t;
public:
    CDataParser(int i): m_pThread(NULL), m_id(i), m_isClose(true){}
    ~CDataParser(){}

	void Start();
	void Stop();

private:
	void __Run();

private:
	threadPtr_t m_pThread;
	int         m_id;
	bool        m_isClose;
};

#endif	/* DATAPARSER_H */

