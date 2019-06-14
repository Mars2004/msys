/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Modules Interface
* @details		Contains definition of @ref IMsvModules interface.
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


#ifndef MARSTECH_IMODULES_H
#define MARSTECH_IMODULES_H


#include "mmodule/IMsvModuleManager.h"

#include "mlogging/mlogging.h"
#include "mconfig/mactivecfg/IMsvActiveConfig.h"
#include "mdllfactory/IMsvDllFactory.h"


/**************************************************************************************************//**
* @brief		MarsTech Modules Interface.
* @details	Modules interface for easy access to modules and module manager interfaces and its implementations.
******************************************************************************************************/
class IMsvModules
{
public:
	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~IMsvModules() {}

	/**************************************************************************************************//**
	* @brief			Get DLL module interface.
	* @details		Returns DLL module interface for module stored in DLL.
	* @param[out]	spModule							Shared pointer to module interface @ref IMsvModule.
	* @param[in]	moduleId							DLL module ID (ID to get module from DLL factory).
	* @param[in]	spDllFactory					Shared pointer to DLL factory @ref IMsvDllFactory interface.
	* @param[in]	spLogger							Shared pointer to logger for logging.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_INVALID_DATA_ERROR		When spDllFactory is empty.
	* @retval		MSV_SUCCESS						On success.
	* @see			IMsvModule
	******************************************************************************************************/
	virtual MsvErrorCode GetDllModule(std::shared_ptr<IMsvModule>& spModule, const char* moduleId, std::shared_ptr<IMsvDllFactory> spDllFactory, std::shared_ptr<MsvLogger> spLogger = nullptr) const = 0;

	/**************************************************************************************************//**
	* @brief			Get module configurator interface.
	* @details		Returns module configurator interface for module configuration.
	* @param[out]	spModuleConfigurator			Shared pointer to module configurator interface @ref IMsvModuleConfigurator.
	* @param[in]	spActiveCfg						Shared pointer to active config.
	* @param[in]	enabledCfgId					Config ID for enabled flag.
	* @param[in]	installedCfgId					Config ID for installed flag.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_INVALID_DATA_ERROR		When spActiveCfg is empty.
	* @retval		MSV_SUCCESS						On success.
	* @see			IMsvModuleConfigurator
	******************************************************************************************************/
	virtual MsvErrorCode GetModuleConfigurator(std::shared_ptr<IMsvModuleConfigurator>& spModuleConfigurator, std::shared_ptr<IMsvActiveConfig> spActiveCfg, int32_t enabledCfgId, int32_t installedCfgId) const = 0;

	/**************************************************************************************************//**
	* @brief			Get module manager interface.
	* @details		Returns module manager interface for module managing.
	* @param[out]	spModuleManager				Shared pointer to module manager interface @ref IMsvModuleManager.
	* @param[in]	spLogger							Shared pointer to logger for logging.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @see			IMsvModuleConfigurator
	******************************************************************************************************/
	virtual MsvErrorCode GetModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<MsvLogger> spLogger = nullptr) const = 0;

	/**************************************************************************************************//**
	* @brief			Get shared module manager interface.
	* @details		Returns shared module manager interface for module managing.
	* @param[out]	spModuleManager				Shared pointer to module manager interface @ref IMsvModuleManager.
	* @param[in]	spLogger							Shared pointer to logger for logging.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @see			IMsvModuleConfigurator
	******************************************************************************************************/
	virtual MsvErrorCode GetSharedModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<MsvLogger> spLogger = nullptr) const = 0;
};


#endif // !MARSTECH_IMODULES_H

/** @} */	//End of group MSYS.
