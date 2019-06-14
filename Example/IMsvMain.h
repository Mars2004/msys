/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Main Interface
* @details		Contains definition of @ref IMsvMain interface.
* @author		Martin Svoboda
* @date			26.05.2019
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


#ifndef MARSTECH_IMAIN_H
#define MARSTECH_IMAIN_H


#include "mmodule/IMsvModule.h"


/**************************************************************************************************//**
* @brief		MarsTech Main Interface.
* @details	Main interface executed by program main function.
* @note		It is on its implementation to create and initialize all objects/classes/data
*				required by a program.
******************************************************************************************************/
class IMsvMain:
	public IMsvModule
{
public:
	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~IMsvMain() {}

	/**************************************************************************************************//**
	* @brief			Signal handler.
	* @details		Handles registered signals. Default implementation just sets stop event.
	* @param[in]	signal		Received signal to handle.
	******************************************************************************************************/
	virtual void OnSignal(int signal) = 0;

	/**************************************************************************************************//**
	* @brief			Wait for stop request.
	* @details		Waits for stop request - blocks current thread until stop event is not set.
	* @retval		other_error_code					When failed.
	* @retval		MSV_SUCCESS							On success.
	******************************************************************************************************/
	virtual MsvErrorCode WaitForStopRequest() = 0;
};


#endif // !MARSTECH_IMAIN_H

/** @} */	//End of group MSVEXAMPLE.
