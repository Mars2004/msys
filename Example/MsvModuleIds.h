/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Module IDs
* @details		Contains enumeration @ref MsvModuleId with module IDs.
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


#ifndef MARSTECH_MODULEIDS_H
#define MARSTECH_MODULEIDS_H


#include "mheaders/MsvCompiler.h"
MSV_DISABLE_ALL_WARNINGS

#include <cstdint>

MSV_ENABLE_WARNINGS

/**************************************************************************************************//**
* @brief		MarsTech Module IDs.
* @details	List of application module IDs.
******************************************************************************************************/
enum class MsvModuleId: int32_t
{
	MSV_EXAMPLE_STATIC_MODULE_1				= 0,
	MSV_EXAMPLE_STATIC_MODULE_2,
	MSV_EXAMPLE_DYNAMIC_MODULE_1,
	MSV_EXAMPLE_DYNAMIC_MODULE_2
};


#endif // !MARSTECH_MODULEIDS_H

/** @} */	//End of group MSVEXAMPLE.
