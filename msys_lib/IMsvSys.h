/**************************************************************************************************//**
* @defgroup		MSYS MarsTech C++ SYS library
* @brief			MarsTech C++ SYS library
* @details		Contains implementation and all definitions of MarsTech C++ SYS library. Implements easy
*					access to most of MarsTech projects and creates static and dynamic library of C++ SYS
*					library.
* @copyright	GNU General Public License (GPLv3).
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech SYS Interface
* @details		Contains definition of @ref IMsvSys interface.
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


#ifndef MARSTECH_ISYS_H
#define MARSTECH_ISYS_H


#include "mdllfactory/IMsvDllObject.h"
#include "merror/MsvError.h"

#include "msys/configuration/IMsvConfiguration.h"
#include "msys/logging/IMsvLogging.h"
#include "msys/threading/IMsvThreading.h"

MSV_DISABLE_ALL_WARNINGS

#include <memory>

MSV_ENABLE_WARNINGS


/**************************************************************************************************//**
* @brief		MarsTech SYS Interface.
* @details	SYS interface for easy access to SYS interfaces and its implementations.
* @see		IMsvDllObject
* @note		There are two ways how to get this interface to work properly.
*				It might be got from DLL or it might be created in program main function or main class
*				and should be forwarded to all other classes/objects/functions as shared pointer.
* @warning	Some shared interfaces might not work properly when this interface is not singleton
*				for whole process (including all loaded DLLs).
******************************************************************************************************/
class IMsvSys:
	public IMsvDllObject
{
public:
	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~IMsvSys() {}

	/**************************************************************************************************//**
	* @brief			Get configuration interface.
	* @details		Returns configuration interface with get methods for active and passive configurations.
	*					Each call of this method returns same interface (same shared pointer).
	* @param[out]	spConfiguration		Shared pointer to configuration interface @ref IMsvConfiguration.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @note			When @ref IMsvSys is singleton, configuration interface is singleton too.
	* @see			IMsvConfiguration
	******************************************************************************************************/
	virtual MsvErrorCode GetMsvConfiguration(std::shared_ptr<IMsvConfiguration>& spConfiguration) const = 0;

	/**************************************************************************************************//**
	* @brief			Get logging interface.
	* @details		Returns logging interface with get methods for logger and logger provider.
	*					Each call of this method returns same interface (same shared pointer).
	* @param[out]	spLogging			Shared pointer to logging interface @ref IMsvLogging.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @note			When @ref IMsvSys is singleton, logging interface is singleton too.
	* @see			IMsvLogging
	******************************************************************************************************/
	virtual MsvErrorCode GetMsvLogging(std::shared_ptr<IMsvLogging>& spLogging) const = 0;

	/**************************************************************************************************//**
	* @brief			Get threading interface.
	* @details		Returns threading interface with get methods for event, threadpool, unique worker and
	*					worker.
	*					Each call of this method returns same interface (same shared pointer).
	* @param[out]	spThreading			Shared pointer to threading interface @ref IMsvThreading.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @note			When @ref IMsvSys is singleton, threading interface is singleton too.
	* @see			IMsvThreading
	******************************************************************************************************/
	virtual MsvErrorCode GetMsvThreading(std::shared_ptr<IMsvThreading>& spThreading) const = 0;
};


#endif // MARSTECH_ISYS_H

/** @} */	//End of group MSYS.
