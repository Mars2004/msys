/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Logging Implementation
* @details		Contains implementation of @ref MsvLogging.
* @author		Martin Svoboda
* @date			05.05.2019
* @copyright	GNU General Public License (GPLv3).
******************************************************************************************************/


/*
This file is part of MarsTech C++ SYS Library.

MarsTech Dependency Injection is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MarsTech Promise Like Syntax is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/


#include "MsvLogging.h"

#include "mlogging/MsvSpdLogLoggerProvider.h"

#include "merror/MsvErrorCodes.h"


/********************************************************************************************************************************
*															Constructors and destructors
********************************************************************************************************************************/


MsvLogging::MsvLogging()
{

}


MsvLogging::~MsvLogging()
{
	
}


/********************************************************************************************************************************
*															IMsvLogging public methods
********************************************************************************************************************************/


MsvErrorCode MsvLogging::GetLogger(std::shared_ptr<MsvLogger>& spLogger, const char* loggerName) const
{
	if (!m_spSharedLoggerProvider)
	{
		return MSV_DOES_NOT_EXIST_ERROR;
	}

	spLogger = m_spSharedLoggerProvider->GetLogger(loggerName);
	if (!spLogger)
	{
		return MSV_ALLOCATION_ERROR;
	}

	return MSV_SUCCESS;
}

MsvErrorCode MsvLogging::GetLogger(std::shared_ptr<MsvLogger>& spLogger, const char* loggerName, const char* logFile, int maxLogFileSize, int maxLogFiles) const
{
	if (!m_spSharedLoggerProvider)
	{
		return MSV_DOES_NOT_EXIST_ERROR;
	}

	spLogger = m_spSharedLoggerProvider->GetLogger(loggerName, logFile, maxLogFileSize, maxLogFiles);
	if (!spLogger)
	{
		return MSV_ALLOCATION_ERROR;
	}

	return MSV_SUCCESS;
}

MsvErrorCode MsvLogging::GetLoggerProvider(std::shared_ptr<IMsvLoggerProvider>& spLoggerProvider, const char* logFolder, const char* logFile, int maxLogFileSize, int maxLogFiles) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (!m_spSharedLoggerProvider)
	{
		m_spSharedLoggerProvider.reset(new (std::nothrow) MsvLoggerProvider(logFolder, logFile, maxLogFileSize, maxLogFiles));
		if (!m_spSharedLoggerProvider)
		{
			return MSV_ALLOCATION_ERROR;
		}
	}

	spLoggerProvider = m_spSharedLoggerProvider;

	return MSV_SUCCESS;
}

MsvErrorCode MsvLogging::SetLoggerProvider(std::shared_ptr<IMsvLoggerProvider> spLoggerProvider)
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (m_spSharedLoggerProvider)
	{
		return MSV_ALREADY_EXISTS_ERROR;
	}

	if (!spLoggerProvider)
	{
		return MSV_INVALID_DATA_ERROR;
	}

	m_spSharedLoggerProvider = spLoggerProvider;

	return MSV_SUCCESS;
}

MsvErrorCode MsvLogging::SetLogLevel(MsvLogLevel logLevel)
{
	if (!m_spSharedLoggerProvider)
	{
		return MSV_DOES_NOT_EXIST_ERROR;
	}

	m_spSharedLoggerProvider->SetLogLevel(logLevel);

	return MSV_SUCCESS;
}


/** @} */	//End of group MSYS.
