/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Active Config Keys
* @details		Contains enumeration @ref MsvActiveCfgKey with active config keys.
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


#ifndef MARSTECH_ACTIVECFGKEYS_H
#define MARSTECH_ACTIVECFGKEYS_H


#include "mheaders/MsvCompiler.h"
MSV_DISABLE_ALL_WARNINGS

#include <cstdint>

MSV_ENABLE_WARNINGS

/**************************************************************************************************//**
* @brief		MarsTech Active Config Keys.
* @details	List of active config keys used by application.
******************************************************************************************************/
enum class MsvActiveCfgKey: int32_t
{
	//static module config IDs
	MSV_STATIC_MODULE1_INSTALLED = 0,
	MSV_STATIC_MODULE1_ENABLED,
	MSV_STATIC_MODULE2_INSTALLED,
	MSV_STATIC_MODULE2_ENABLED,

	//dynamic module config IDs
	MSV_DYNAMIC_MODULE1_INSTALLED,
	MSV_DYNAMIC_MODULE1_ENABLED,
	MSV_DYNAMIC_MODULE2_INSTALLED,
	MSV_DYNAMIC_MODULE2_ENABLED
};


#endif // !MARSTECH_ACTIVECFGKEYS_H

/** @} */	//End of group MSVEXAMPLE.
