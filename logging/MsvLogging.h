/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Logging Implementation
* @details		Contains implementation @ref MsvLogging of @ref IMsvLogging interface.
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


#ifndef MARSTECH_LOGGING_SYS_H
#define MARSTECH_LOGGING_SYS_H


#include "IMsvLogging.h"


/**************************************************************************************************//**
* @brief		MarsTech Logging Implementation.
* @details	Implementation of logging interface for easy access to logging interfaces and its implementations.
* @see		IMsvLogging
******************************************************************************************************/
class MsvLogging:
	public IMsvLogging
{
public:
	/**************************************************************************************************//**
	* @brief		Constructor.
	******************************************************************************************************/
	MsvLogging();

	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~MsvLogging();

	/**************************************************************************************************//**
	* @copydoc IMsvLogging::GetLogger(std::shared_ptr<MsvLogger>& spLogger, const char* loggerName) const
	******************************************************************************************************/
	virtual MsvErrorCode GetLogger(std::shared_ptr<MsvLogger>& spLogger, const char* loggerName = "MsvLogger") const override;

	/**************************************************************************************************//**
	* @copydoc IMsvLogging::GetLogger(std::shared_ptr<MsvLogger>& spLogger, const char* loggerName, const char* logFile, int maxLogFileSize, int maxLogFiles) const
	******************************************************************************************************/
	virtual MsvErrorCode GetLogger(std::shared_ptr<MsvLogger>& spLogger, const char* loggerName, const char* logFile, int maxLogFileSize, int maxLogFiles) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvLogging::GetLoggerProvider(std::shared_ptr<IMsvLoggerProvider>& spLoggerProvider, const char* logFolder = "", const char* logFile = "msvlog.txt", int maxLogFileSize = 10485760, int maxLogFiles = 3) const
	******************************************************************************************************/
	virtual MsvErrorCode GetLoggerProvider(std::shared_ptr<IMsvLoggerProvider>& spLoggerProvider, const char* logFolder = "", const char* logFile = "msvlog.txt", int maxLogFileSize = 10485760, int maxLogFiles = 3) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvLogging::SetLoggerProvider(std::shared_ptr<IMsvLoggerProvider> spLoggerProvider)
	******************************************************************************************************/
	virtual MsvErrorCode SetLoggerProvider(std::shared_ptr<IMsvLoggerProvider> spLoggerProvider) override;

	/**************************************************************************************************//**
	* @copydoc IMsvLogging::SetLogLevel(MsvLogLevel logLevel)
	******************************************************************************************************/
	virtual MsvErrorCode SetLogLevel(MsvLogLevel logLevel) override;

protected:
	/**************************************************************************************************//**
	* @brief		Thread mutex.
	* @details	Locks this object for thread safety access.
	******************************************************************************************************/
	mutable std::recursive_mutex m_lock;

	/**************************************************************************************************//**
	* @brief		Shared logger provider.
	* @details	It is returned by @ref GetLoggerProvider.
	******************************************************************************************************/
	mutable std::shared_ptr<IMsvLoggerProvider> m_spSharedLoggerProvider;
};


#endif // !MARSTECH_LOGGING_SYS_H

/** @} */	//End of group MSYS.
