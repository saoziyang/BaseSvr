/*
 * BaseLogger.h
 *
 *  Created on: Mar 21, 2013
 *      Author: ke
 */

#ifndef BASELOGGER_H_
#define BASELOGGER_H_

#include "ILogger.h"

#define LOG(...) { { char lBuf[1024]; snprintf(lBuf, 1023, __VA_ARGS__); BaseLogger.Log(lBuf);} };

class CBaseLogger : public ILogger{
public:
	CBaseLogger(): m_logger(NULL){}
	virtual ~CBaseLogger(){}

	void Set(ILogger * pLogger);

	void Log(const std::string& str);
	void SetProperty(const std::string& name, const std::string& value);
private:
	ILogger * m_logger;
};

extern CBaseLogger BaseLogger;

#endif /* BASELOGGER_H_ */
