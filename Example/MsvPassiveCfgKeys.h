/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Passive Config Keys
* @details		Contains enumeration @ref MsvPassiveCfgKey with passive config keys.
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


#ifndef MARSTECH_PASSIVECFGKEYS_H
#define MARSTECH_PASSIVECFGKEYS_H


#include "mheaders/MsvCompiler.h"
MSV_DISABLE_ALL_WARNINGS

#include <cstdint>

MSV_ENABLE_WARNINGS

/**************************************************************************************************//**
* @brief		MarsTech Passive Config Keys.
* @details	List of passive config keys used by application.
******************************************************************************************************/
enum class MsvPassiveCfgKey: int32_t
{
	//MsvMain: logging settings
	MAIN_LOG_FOLDER			= 0,
	MAIN_LOG_FILE,
	MAIN_LOG_FILEMAXSIZE,
	MAIN_LOG_MAXFILES,

	//MsvMain: active config settings
	MAIN_ACTIVECFG_PATH,
	MAIN_ACTIVECFG_GROUP	
};


#endif // !MARSTECH_PASSIVECFGKEYS_H

/** @} */	//End of group MSVEXAMPLE.
