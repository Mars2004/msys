/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Main Factory
* @details		Contains implementation of dependency injection factory @ref MsvMain_Factory
*					for @ref MsvMain.
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


#ifndef MARSTECH_MAIN_FACTORY_H
#define MARSTECH_MAIN_FACTORY_H


#include "mdi/MdiFactory.h"

#include "mconfig/mpassivecfg/MsvPassiveConfig.h"
#include "mlogging/MsvSpdLogLoggerProvider.h"
#include "mdllfactory/MsvDllFactory.h"


/**************************************************************************************************//**
* @class		MsvMain_Factory
* @brief		MarsTech Main Dependency Injection Factory.
* @details	Implementation of dependency injection factory for @ref MsvMain.
******************************************************************************************************/
MSV_FACTORY_START(MsvMain_Factory)
MSV_FACTORY_GET_0(IMsvPassiveConfig, MsvPassiveConfig);
MSV_FACTORY_GET_4(IMsvLoggerProvider, MsvLoggerProvider, const char*, const char*, int, int);
MSV_FACTORY_GET_2(IMsvDllFactory, MsvDllFactory, const std::shared_ptr<IMsvDllList>&, std::shared_ptr<MsvLogger>);
MSV_FACTORY_END


#endif // MARSTECH_MAIN_FACTORY_H

/** @} */	//End of group MSVEXAMPLE.
