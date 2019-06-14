/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Modules Implementation
* @details		Contains implementation @ref MsvModules of @ref IMsvModules interface.
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


#ifndef MARSTECH_MODULES_H
#define MARSTECH_MODULES_H


#include "IMsvModules.h"


/**************************************************************************************************//**
* @brief		MarsTech Modules Implementation.
* @details	Implementation of modules interface for easy access to modules interfaces and its implementations.
* @see		IMsvModules
******************************************************************************************************/
class MsvModules:
	public IMsvModules
{
public:
	/**************************************************************************************************//**
	* @brief		Constructor.
	******************************************************************************************************/
	MsvModules();

	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~MsvModules();

	/**************************************************************************************************//**
	* @copydoc IMsvModules::GetDllModule(std::shared_ptr<IMsvModule>& spModule, const char* moduleId, std::shared_ptr<IMsvDllFactory> spDllFactory, std::shared_ptr<MsvLogger> spLogger = nullptr) const
	******************************************************************************************************/
	virtual MsvErrorCode GetDllModule(std::shared_ptr<IMsvModule>& spModule, const char* moduleId, std::shared_ptr<IMsvDllFactory> spDllFactory, std::shared_ptr<MsvLogger> spLogger = nullptr) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvModules::GetModuleConfigurator(std::shared_ptr<IMsvModuleConfigurator>& spModuleConfigurator, std::shared_ptr<IMsvActiveConfig> spActiveCfg, int32_t enabledCfgId, int32_t installedCfgId) const
	******************************************************************************************************/
	virtual MsvErrorCode GetModuleConfigurator(std::shared_ptr<IMsvModuleConfigurator>& spModuleConfigurator, std::shared_ptr<IMsvActiveConfig> spActiveCfg, int32_t enabledCfgId, int32_t installedCfgId) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvModules::GetModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<MsvLogger> spLogger = nullptr) const
	******************************************************************************************************/
	virtual MsvErrorCode GetModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<MsvLogger> spLogger = nullptr) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvModules::GetSharedModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<MsvLogger> spLogger = nullptr) const
	******************************************************************************************************/
	virtual MsvErrorCode GetSharedModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<MsvLogger> spLogger = nullptr) const override;

protected:
	/**************************************************************************************************//**
	* @brief		Thread mutex.
	* @details	Locks this object for thread safety access.
	******************************************************************************************************/
	mutable std::recursive_mutex m_lock;

	/**************************************************************************************************//**
	* @brief		Shared module manager.
	* @details	It is returned by @ref GetSharedModuleManager.
	******************************************************************************************************/
	mutable std::shared_ptr<IMsvModuleManager> m_spSharedModuleManager;
};


#endif // !MARSTECH_MODULES_H

/** @} */	//End of group MSYS.
