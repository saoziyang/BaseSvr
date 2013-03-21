/*
 * BaseLogger.cpp
 *
 *  Created on: Mar 21, 2013
 *      Author: ke
 */

#include "BaseLogger.h"

CBaseLogger BaseLogger;

void CBaseLogger::Set(ILogger * pLogger)
{
	m_logger = pLogger;
}

void CBaseLogger::Log(const std::string& str)
{
	if (m_logger)
		m_logger->Log(str);
}

void CBaseLogger::SetProperty(const std::string& name, const std::string& value)
{
	if (m_logger)
		m_logger->SetProperty(name, value);
}

