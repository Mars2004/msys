/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Main Initializer Interface
* @details		Contains definition of @ref IMsvMainInitializer interface.
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


#ifndef MARSTECH_IMAININITIALIZER_H
#define MARSTECH_IMAININITIALIZER_H


#include "mconfig/common/IMsvConfigKeyMap.h"
#include "mconfig/common/IMsvDefaultValue.h"
#include "mconfig/common/IMsvConfigKey.h"
#include "mconfig/mactivecfg/IMsvActiveConfig.h"
#include "mconfig/mpassivecfg/IMsvPassiveConfig.h"
#include "mdllfactory/IMsvDllList.h"
#include "mdllfactory/IMsvDllFactory.h"
#include "mmodule/IMsvModuleManager.h"
#include "msys/modules/IMsvModules.h"


/**************************************************************************************************//**
* @brief		MarsTech Main Initializer Interface.
* @details	Main initializer interface which creates and initializes data required by @ref IMsvMain.
******************************************************************************************************/
class IMsvMainInitializer
{
public:
	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~IMsvMainInitializer() {}

	/**************************************************************************************************//**
	* @brief			Add application modules to module manager.
	* @details		Creates static modules, loads dynamic modules and adds them to module manager.
	* @param[out]	spModuleManager		Module manager.
	* @param[in]	spModules				Modules object to create DLL modules.
	* @param[in]	spDllFactory			DLL factory for DLL modules (it might be used by statically linked modules too).
	* @param[in]	spActiveCfg				Active config for module configurators.
	* @retval		other_error_code		When failed.
	* @retval		MSV_SUCCESS				On success.
	******************************************************************************************************/
	virtual MsvErrorCode AddModulesToModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<IMsvModules> spModules, std::shared_ptr<IMsvDllFactory> spDllFactory, std::shared_ptr<IMsvActiveConfig> spActiveCfg) const = 0;

	/**************************************************************************************************//**
	* @brief			Get active config data.
	* @details		Returns active config data - path to stored active config and active config group.
	* @param[in]	spPassiveConfig		Passive config (active config data are stored in passive config).
	* @param[out]	configPath				Path to active config.
	* @param[out]	configGroup				Active config group.
	* @retval		other_error_code		When failed.
	* @retval		MSV_SUCCESS				On success.
	******************************************************************************************************/
	virtual MsvErrorCode GetActiveConfigData(const std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig, std::string& configPath, std::string& configGroup) const = 0;

	/**************************************************************************************************//**
	* @brief			Get logger provider data.
	* @details		Returns logger provider data - path to log folder, default log file name, max log files and theirs max size.
	* @param[in]	spPassiveConfig		Passive config (logger provider data are stored in passive config).
	* @param[out]	logFolder				Log folder (all log files will be stored there).
	* @param[out]	logFile					Default log file name.
	* @param[out]	maxLogFileSize			Max size of log files.
	* @param[out]	maxLogFiles				Max count of log files.
	* @retval		other_error_code		When failed.
	* @retval		MSV_SUCCESS				On success.
	******************************************************************************************************/
	virtual MsvErrorCode GetMsvLoggerProviderData(const std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig, std::string& logFolder, std::string& logFile, uint32_t& maxLogFileSize, uint32_t& maxLogFiles) const = 0;

	/**************************************************************************************************//**
	* @brief			Initialize and get active config key map.
	* @details		Returns created and initialized active config key map.
	* @param[out]	spActiveCfgKeyMap		Created and initialized active config key map.
	* @retval		other_error_code		When failed.
	* @retval		MSV_SUCCESS				On success.
	******************************************************************************************************/
	virtual MsvErrorCode InitializeAndGetActiveConfigKeyMap(std::shared_ptr<IMsvConfigKeyMap<IMsvDefaultValue>>& spActiveCfgKeyMap) const = 0;

	/**************************************************************************************************//**
	* @brief			Initialize and get DLL list.
	* @details		Returns created and initialized list of dynamic/shared libraries.
	* @param[out]	spDllList				Created and initialized list of dynamic/shared libraries.
	* @retval		other_error_code		When failed.
	* @retval		MSV_SUCCESS				On success.
	******************************************************************************************************/
	virtual MsvErrorCode InitializeAndGetDllList(std::shared_ptr<IMsvDllList>& spDllList) const = 0;

	/**************************************************************************************************//**
	* @brief			Initialize and get passive config key map.
	* @details		Returns created and initialized passive config key map.
	* @param[out]	spPassiveCfgKeyMap	Created and initialized passive config key map.
	* @retval		other_error_code		When failed.
	* @retval		MSV_SUCCESS				On success.
	******************************************************************************************************/
	virtual MsvErrorCode InitializeAndGetPassiveConfigKeyMap(std::shared_ptr<IMsvConfigKeyMap<IMsvConfigKey>>& spPassiveCfgKeyMap) const = 0;
};


#endif // !MARSTECH_IMAININITIALIZER_H

/** @} */	//End of group MSVEXAMPLE.
