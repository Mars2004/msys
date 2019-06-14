/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Logging Interface
* @details		Contains definition of @ref IMsvLogging interface.
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


#ifndef MARSTECH_ILOGGING_SYS_H
#define MARSTECH_ILOGGING_SYS_H


#include "mlogging/mlogging.h"

#include "merror/MsvError.h"
MSV_DISABLE_ALL_WARNINGS

#include <mutex>

MSV_ENABLE_WARNINGS


/**************************************************************************************************//**
* @brief		MarsTech Logging Interface.
* @details	Logging interface for easy access to logging interfaces and its implementations.
******************************************************************************************************/
class IMsvLogging
{
public:
	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~IMsvLogging() {}

	/**************************************************************************************************//**
	* @brief			Get logger.
	* @details		Returns logger for logging. Creates new logger if new loggerName was received.
	*					Returns already created logger and in parameters are ignored other way.
	* @param[out]	spLogger					Shared pointer to logger implementation @ref MsvLogger.
	* @param[in]	loggerName				Logger name which will be printed to log file.
	* @retval		MSV_DOES_NOT_EXIST_ERROR	When @ref GetLoggerProvider and @ref SetLoggerProvider method was not called before.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @warning		At least one of method @ref GetLoggerProvider and @ref SetLoggerProvider must be called
	*					before calling this method. Other way returns @ref MSV_DOES_NOT_EXIST_ERROR.
	*					@ref IMsvLoggerProvider must be intialized/set before.
	* @note			In parameters are used only when new loggerName was received. They are ignored
	*					when loggerName was used before.
	* @see			MsvLogger
	******************************************************************************************************/
	virtual MsvErrorCode GetLogger(std::shared_ptr<MsvLogger>& spLogger, const char* loggerName = "MsvLogger") const = 0;

	/**************************************************************************************************//**
	* @brief			Get logger.
	* @details		Returns logger for logging. Creates new logger if new loggerName was received.
	*					Returns already created logger and in parameters are ignored other way.
	* @param[out]	spLogger					Shared pointer to logger implementation @ref MsvLogger.
	* @param[in]	loggerName				Logger name which will be printed to log file.
	* @param[in]	logFile					Log file name.
	* @param[in]	maxLogFileSize			Maximum size of one log file (in bytes).
	* @param[in]	maxLogFiles				Maximum number of log files (rotating logger, the oldest file will be deleted).
	* @retval		MSV_DOES_NOT_EXIST_ERROR	When @ref GetLoggerProvider and @ref SetLoggerProvider method was not called before.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @warning		At least one of method @ref GetLoggerProvider and @ref SetLoggerProvider must be called
	*					before calling this method. Other way returns @ref MSV_DOES_NOT_EXIST_ERROR.
	*					@ref IMsvLoggerProvider must be intialized/set before.
	* @note			In parameters are used only when new loggerName was received. They are ignored
	*					when loggerName was used before.
	* @see			MsvLogger
	******************************************************************************************************/
	virtual MsvErrorCode GetLogger(std::shared_ptr<MsvLogger>& spLogger, const char* loggerName, const char* logFile, int maxLogFileSize, int maxLogFiles) const = 0;

	/**************************************************************************************************//**
	* @brief			Get logger provider interface.
	* @details		Returns logger provider interface with get methods for logger.
	*					Each call of this method returns same interface (same shared pointer).
	* @param[out]	spLoggerProvider		Shared pointer to logger interface @ref IMsvLoggerProvider.
	* @param[in]	logFolder				Path to log folder where log files will be stored.
	* @param[in]	logFile					Log file name.
	* @param[in]	maxLogFileSize			Maximum size of one log file (in bytes).
	* @param[in]	maxLogFiles				Maximum number of log files (rotating logger, the oldest file will be deleted).
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @note			When @ref IMsvLogging is singleton, logger provider interface is singleton too.
	* @note			In parameters are used only when the method is called first. They are ignored
	*					next time.
	* @warning		Log folder should be folder to which proccess has write access.
	* @warning		This method must be called before any call of GetLogger methods. Other way they failed
	*					@ref MSV_NOT_INITIALIZED_ERROR error.
	* @warning		It might be good practice to get and initialize this interface in main function or class
	*					and just use in all other classes/objects/functions.
	* @see			IMsvLoggerProvider
	******************************************************************************************************/
	virtual MsvErrorCode GetLoggerProvider(std::shared_ptr<IMsvLoggerProvider>& spLoggerProvider, const char* logFolder = "", const char* logFile = "msvlog.txt", int maxLogFileSize = 10485760, int maxLogFiles = 3) const = 0;
	
	/**************************************************************************************************//**
	* @brief			Set logger provider.
	* @details		Sets logger provider to logging. It should be called only once at the application start.
	*					This method is usefull when using @ref IMsvSys loaded from dynamic/shared library.
	* @param[in]	spLoggerProvider		Shared pointer to logger interface @ref IMsvLoggerProvider.
	* @retval		MSV_ALREADY_EXISTS_ERROR	When logger provider has been already set.
	* @retval		MSV_INVALID_DATA_ERROR		When input shared pointer to logger provider is empty.
	* @warning		This method should be called only once at the application start (in main function/class).
	* @warning		This method is usefull when using @ref IMsvSys loaded from dynamic/shared library. There
	*					is no reason to use it when using statically linked @ref IMsvSys.
	* @see			IMsvLoggerProvider
	******************************************************************************************************/
	virtual MsvErrorCode SetLoggerProvider(std::shared_ptr<IMsvLoggerProvider> spLoggerProvider) = 0;

	/**************************************************************************************************//**
	* @brief			Set log level.
	* @details		Sets log level for logging to all loggers. Default level is INFO.
	* @param[in]	logLevel			Log level to set.
	* @note			Default log level is set to info. It is not necessary to call this method when INFO log level
	*					is required.
	* @warning		At least one of method @ref GetLoggerProvider and @ref SetLoggerProvider must be called
	*					before calling this method. Other way returns @ref MSV_DOES_NOT_EXIST_ERROR.
	*					@ref IMsvLoggerProvider must be intialized/set before.
	* @see			IMsvLoggerProvider
	******************************************************************************************************/
	virtual MsvErrorCode SetLogLevel(MsvLogLevel logLevel) = 0;
};


#endif // !MARSTECH_ILOGGING_SYS_H

/** @} */	//End of group MSYS.
