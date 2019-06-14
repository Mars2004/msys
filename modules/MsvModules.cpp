/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Modules Implementation
* @details		Contains implementation of @ref MsvModules.
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


#include "MsvModules.h"

#include "mmodule/MsvModuleManager.h"
#include "mmodule/MsvDllModuleAdapter.h"
#include "mmodule/MsvModuleConfigurator.h"

#include "merror/MsvErrorCodes.h"


/********************************************************************************************************************************
*															Constructors and destructors
********************************************************************************************************************************/


MsvModules::MsvModules()
{

}


MsvModules::~MsvModules()
{
	
}


/********************************************************************************************************************************
*															IMsvModules public methods
********************************************************************************************************************************/


MsvErrorCode MsvModules::GetDllModule(std::shared_ptr<IMsvModule>& spModule, const char* moduleId, std::shared_ptr<IMsvDllFactory> spDllFactory, std::shared_ptr<MsvLogger> spLogger) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (!spDllFactory)
	{
		return MSV_INVALID_DATA_ERROR;
	}

	std::shared_ptr<IMsvModule> spTempModule(new (std::nothrow) MsvDllModuleAdapter(moduleId, spDllFactory, spLogger));

	if (!spTempModule)
	{
		return MSV_ALLOCATION_ERROR;
	}

	spModule = spTempModule;

	return MSV_SUCCESS;
}

MsvErrorCode MsvModules::GetModuleConfigurator(std::shared_ptr<IMsvModuleConfigurator>& spModuleConfigurator, std::shared_ptr<IMsvActiveConfig> spActiveCfg, int32_t enabledCfgId, int32_t installedCfgId) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (!spActiveCfg)
	{
		return MSV_INVALID_DATA_ERROR;
	}

	std::shared_ptr<IMsvModuleConfigurator> spTempModuleConfigurator(new (std::nothrow) MsvModuleConfigurator(spActiveCfg, enabledCfgId, installedCfgId));

	if (!spTempModuleConfigurator)
	{
		return MSV_ALLOCATION_ERROR;
	}

	spModuleConfigurator = spTempModuleConfigurator;

	return MSV_SUCCESS;
}

MsvErrorCode MsvModules::GetModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<MsvLogger> spLogger) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	std::shared_ptr<IMsvModuleManager> spTempModuleManager(new (std::nothrow) MsvModuleManager(spLogger));

	if (!spTempModuleManager)
	{
		return MSV_ALLOCATION_ERROR;
	}

	spModuleManager = spTempModuleManager;

	return MSV_SUCCESS;
}

MsvErrorCode MsvModules::GetSharedModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<MsvLogger> spLogger) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (!m_spSharedModuleManager)
	{
		//if GetModuleManager fails it does not set out shared pointer -> m_spSharedModuleManager is unset when failed
		MSV_RETURN_FAILED(GetModuleManager(m_spSharedModuleManager, spLogger));
	}

	spModuleManager = m_spSharedModuleManager;

	return MSV_SUCCESS;
}


/** @} */	//End of group MSYS.
