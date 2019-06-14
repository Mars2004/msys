/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Example Module DLL Interface
* @details		Contains definition of MarsTech Example Module DLL interface (constants for DLL ids, typedefs of
*					object interfaces, etc.).
* @author		Martin Svoboda
* @date			26.05.2019
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


#ifndef MARSTECH_EXAMPLEMODULEDLL_INTERFACE_H
#define MARSTECH_EXAMPLEMODULEDLL_INTERFACE_H


#include "msys/msys_lib/IMsvSys.h"


/**************************************************************************************************//**
* @brief		ID of Example Module 1.
******************************************************************************************************/
const char* const MSV_EXAMPLEMODULE1_OBJECT_ID = "{91D68031-1687-42A6-AE48-141096DB8CF7}";

/**************************************************************************************************//**
* @brief		ID of Example Module 2.
******************************************************************************************************/
const char* const MSV_EXAMPLEMODULE2_OBJECT_ID = "{BE3FBC0A-C5EC-405D-84B6-F8C48188109E}";


#endif // MARSTECH_EXAMPLEMODULEDLL_INTERFACE_H

/** @} */	//End of group MSVEXAMPLE.
