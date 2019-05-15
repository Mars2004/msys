/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech SYS DLL Interface
* @details		Contains definition of MarsTech SYS DLL interface (constants for DLL ids, typedefs of
*					object interfaces, etc.).
* @author		Martin Svoboda
* @date			05.05.2019
* @copyright	GNU General Public License (GPLv3).
* @note			Include this file when you need to load MarsTech C++ SYS DLL library.
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


#ifndef MARSTECH_SYSDLL_INTERFACE_H
#define MARSTECH_SYSDLL_INTERFACE_H


#include "msys/msys_lib/IMsvSys.h"


/**************************************************************************************************//**
* @brief		ID of MarsTech SYS Interface.
* @details	ID to acquire @ref IMsvSys interface from SYS dll.
* @note		Use @ref MSV_SYS_OBJECT_ID_LAST to get the latest version of SYS interface/implementation.
* @see		IMsvSys
* @see		MSV_SYS_OBJECT_ID_LAST
******************************************************************************************************/
const char* const MSV_SYS_OBJECT_ID = "{06CF2063-E5EC-40E2-AA35-D116F7C0F0E5}";

/**************************************************************************************************//**
* @brief		Last ID of MarsTech SYS Interface.
* @details	ID to acquire latest version of SYS interface/implementation from SYS dll.
* @see		IMsvSys
******************************************************************************************************/
const char* const MSV_SYS_OBJECT_ID_LAST = MSV_SYS_OBJECT_ID;

/**************************************************************************************************//**
* @brief		Last MarsTech SYS Interface.
* @details	Latest version of SYS interface/implementation from SYS dll.
* @see		IMsvSys
******************************************************************************************************/
typedef IMsvSys IMsvSys_Last;


#endif // MARSTECH_SYSDLL_INTERFACE_H

/** @} */	//End of group MSYS.
