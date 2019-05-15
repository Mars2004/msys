/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech DLL main
* @details		DLL main of MarsTech C++ SYS library. Contains implementation of exported @ref GetDllObject function.
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


#include "MsvSysDll_Interface.h"
#include "msys/msys_lib/MsvSys.h"
#include "mdllfactory/MsvDllMainHelper.h"

#include "merror/MsvErrorCodes.h"


/**************************************************************************************************//**
* @brief		DLL global mutex.
* @details	Locks this DLL (its @ref GetDllObject function) for thread safety access.
******************************************************************************************************/
std::recursive_mutex g_lock;

/**************************************************************************************************//**
* @brief		Shared @ref IMsvSys.
* @details	Shared interface @ref IMsvSys. It is std::weak_ptr, so returns shared object until someone
*				holds in a std::shared_ptr.
******************************************************************************************************/
std::weak_ptr<IMsvDllObject> g_spSys;


/**************************************************************************************************//**
* @brief			Get DLL object.
* @details		Checks if known object id is requested and returns it when it is known. It failes
*					when unknow object id is requested.
* @param[in]	id						Requested object ID.
* @param[out]	spDllObject			Returned object (when object ID is known).
* @returns		MsvErrorCode
* @retval		MSV_ALLOCATION_ERROR		When create requested object failed.
* @retval		MSV_NOT_FOUND_ERROR		When was requested object with unknown ID.
* @retval		MSV_SUCCESS					On success.
* @note			Caller should known real object type (at least real object interface type).
* @note			Some objects might be returned as shared objects (DLL can holds std::weak_ptr to created
*					objects).
* @see			IMsvDllObject
******************************************************************************************************/
#ifdef _WIN32
MsvErrorCode GetDllObject(const char* id, std::shared_ptr<IMsvDllObject>& spDllObject)
#else
extern "C" MsvErrorCode GetDllObject(const char* id, std::shared_ptr<IMsvDllObject>& spDllObject)
#endif // _WIN32
{
	std::lock_guard<std::recursive_mutex> lock(g_lock);

	//convert to string for comparison
	std::string idString(id);

	//create and return DLL object when known id was used
	MSV_GETWEAKSHARED_DLLOBJECT_WITH_ID(idString, MSV_SYS_OBJECT_ID, MsvSys, g_spSys, spDllObject);

	//uknown id (not found) -> error
	return MSV_NOT_FOUND_ERROR;
}


/** @} */	//End of group MSYS.
