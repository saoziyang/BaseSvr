/*
 * ILogger.h
 *
 *  Created on: Mar 21, 2013
 *      Author: ke
 */

#ifndef ILOGGER_H_
#define ILOGGER_H_

#include <string>

class ILogger
{
public:
	ILogger(){}
	virtual ~ILogger(){}
public:
	virtual void Log(const std::string& str)=0;
	virtual void SetProperty(const std::string& name, const std::string& value)=0;
};

#endif /* ILOGGER_H_ */
