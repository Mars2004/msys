/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Main Initiliazer Implementation
* @details		Contains implementation @ref MsvMainInitializer of @ref IMsvMainInitializer interface.
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


#ifndef MARSTECH_MAININITIALIZER_H
#define MARSTECH_MAININITIALIZER_H


#include "IMsvMainInitializer.h"


/**************************************************************************************************//**
* @brief		MarsTech Main Initializer Implementation.
* @details	Main initializer implementation which creates and initializes data required by @ref MsvMain.
******************************************************************************************************/
class MsvMainInitializer:
	public IMsvMainInitializer
{
public:
	MsvMainInitializer();

	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~MsvMainInitializer();

	/*-----------------------------------------------------------------------------------------------------
	**											IMsvMainInitializer public methods
	**---------------------------------------------------------------------------------------------------*/
public:
	/**************************************************************************************************//**
	* @copydoc IMsvMainInitializer::AddModulesToModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<IMsvModules> spModules, std::shared_ptr<IMsvDllFactory> spDllFactory, std::shared_ptr<IMsvActiveConfig> spActiveCfg) const
	******************************************************************************************************/
	virtual MsvErrorCode AddModulesToModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<IMsvModules> spModules, std::shared_ptr<IMsvDllFactory> spDllFactory, std::shared_ptr<IMsvActiveConfig> spActiveCfg) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvMainInitializer::GetActiveConfigData(const std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig, std::string& configPath, std::string& configGroup) const
	******************************************************************************************************/
	virtual MsvErrorCode GetActiveConfigData(const std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig, std::string& configPath, std::string& configGroup) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvMainInitializer::GetMsvLoggerProviderData(const std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig, std::string& logFolder, std::string& logFile, uint32_t& maxLogFileSize, uint32_t& maxLogFiles) const
	******************************************************************************************************/
	virtual MsvErrorCode GetMsvLoggerProviderData(const std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig, std::string& logFolder, std::string& logFile, uint32_t& maxLogFileSize, uint32_t& maxLogFiles) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvMainInitializer::InitializeAndGetActiveConfigKeyMap(std::shared_ptr<IMsvConfigKeyMap<IMsvDefaultValue>>& spActiveCfgKeyMap) const
	******************************************************************************************************/
	virtual MsvErrorCode InitializeAndGetActiveConfigKeyMap(std::shared_ptr<IMsvConfigKeyMap<IMsvDefaultValue>>& spActiveCfgKeyMap) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvMainInitializer::InitializeAndGetDllList(std::shared_ptr<IMsvDllList>& spDllList) const
	******************************************************************************************************/
	virtual MsvErrorCode InitializeAndGetDllList(std::shared_ptr<IMsvDllList>& spDllList) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvMainInitializer::InitializeAndGetPassiveConfigKeyMap(std::shared_ptr<IMsvConfigKeyMap<IMsvConfigKey>>& spPassiveCfgKeyMap) const
	******************************************************************************************************/
	virtual MsvErrorCode InitializeAndGetPassiveConfigKeyMap(std::shared_ptr<IMsvConfigKeyMap<IMsvConfigKey>>& spPassiveCfgKeyMap) const override;
};


#endif // !MARSTECH_MAININITIALIZER_H

/** @} */	//End of group MSVEXAMPLE.
