/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Main Initializer Implementation
* @details		Contains implementation of @ref MsvMainInitializer.
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


#include "MsvMainInitializer.h"

#include "MsvActiveCfgKeys.h"
#include "MsvPassiveCfgKeys.h"
#include "MsvModuleIds.h"
#include "msvexamplemodule_lib/MsvExampleModule.h"
#include "msvexamplemodule/MsvExampleModuleDll_Interface.h"

#include "mconfig/common/MsvConfigKeyMapBase.h"
#include "mconfig/common/MsvConfigKey.h"
#include "mconfig/common/MsvDefaultValue.h"
#include "mdllfactory/MsvDllList.h"
#include "msys/msys/MsvSysDll_Interface.h"
#include "mmodule/MsvModuleConfigurator.h"
#include "merror/MsvErrorCodes.h"


/********************************************************************************************************************************
*															Passive Config Constants
********************************************************************************************************************************/


const char* const PCFG_LOGGING_GROUP = "Logging";
const char* const PCFG_ACTIVECFG_GROUP = "Active Config";


/********************************************************************************************************************************
*															Helper functions
********************************************************************************************************************************/


MsvErrorCode InsertConfigKey(std::shared_ptr<MsvConfigKeyMapBase<IMsvConfigKey>> spPassiveCfgKeyMap, MsvPassiveCfgKey cfgId, const char* group, const char* key, IMsvDefaultValue* pDefaultValue)
{
	if (!pDefaultValue)
	{
		return MSV_ALLOCATION_ERROR;
	}

	std::shared_ptr<IMsvConfigKey> spConfigKey(new (std::nothrow) MsvConfigKey(group, key, std::shared_ptr<IMsvDefaultValue>(pDefaultValue)));
	if (!spConfigKey)
	{
		return MSV_ALLOCATION_ERROR;
	}

	return spPassiveCfgKeyMap->InsertKeyData(static_cast<int32_t>(cfgId), spConfigKey);
}

MsvErrorCode InsertConfigKey(std::shared_ptr<MsvConfigKeyMapBase<IMsvDefaultValue>> spActiveCfgKeyMap, MsvActiveCfgKey cfgId, IMsvDefaultValue* pDefaultValue)
{
	if (!pDefaultValue)
	{
		return MSV_ALLOCATION_ERROR;
	}

	return spActiveCfgKeyMap->InsertKeyData(static_cast<int32_t>(cfgId), std::shared_ptr<IMsvDefaultValue>(pDefaultValue));
}

MsvErrorCode AddModule(std::shared_ptr<IMsvModuleManager>& spModuleManager, MsvModuleId moduleId, std::shared_ptr<IMsvModule> spModule, std::shared_ptr<IMsvActiveConfig> spActiveCfg, MsvActiveCfgKey enabledCfgId, MsvActiveCfgKey installedCfgId)
{
	if (!spModule)
	{
		return MSV_ALLOCATION_ERROR;
	}

	std::shared_ptr<IMsvModuleConfigurator> spModuleConfigurator(new (std::nothrow) MsvModuleConfigurator(spActiveCfg, static_cast<int32_t>(enabledCfgId), static_cast<int32_t>(installedCfgId)));
	if (!spModuleConfigurator)
	{
		return MSV_ALLOCATION_ERROR;
	}

	return spModuleManager->AddModule(static_cast<int32_t>(moduleId), spModule, spModuleConfigurator);
}

MsvErrorCode AddModule(std::shared_ptr<IMsvModuleManager>& spModuleManager, MsvModuleId moduleId, IMsvModule* pModule, std::shared_ptr<IMsvActiveConfig> spActiveCfg, MsvActiveCfgKey enabledCfgId, MsvActiveCfgKey installedCfgId)
{
	if (!pModule)
	{
		return MSV_ALLOCATION_ERROR;
	}

	return AddModule(spModuleManager, moduleId, std::shared_ptr<IMsvModule>(pModule), spActiveCfg, enabledCfgId, installedCfgId);
}

MsvErrorCode AddModule(std::shared_ptr<IMsvModuleManager>& spModuleManager, MsvModuleId moduleId, std::shared_ptr<IMsvModules> spModules, const char* dllModuleId, std::shared_ptr<IMsvDllFactory> spDllFactory, std::shared_ptr<IMsvActiveConfig> spActiveCfg, MsvActiveCfgKey enabledCfgId, MsvActiveCfgKey installedCfgId)
{
	std::shared_ptr<IMsvModule> spDllModule;
	MSV_RETURN_FAILED(spModules->GetDllModule(spDllModule, dllModuleId, spDllFactory));
	MSV_RETURN_FAILED(AddModule(spModuleManager, moduleId, spDllModule, spActiveCfg, enabledCfgId, installedCfgId));

	return MSV_SUCCESS;
}


/********************************************************************************************************************************
*															Constructors and destructors
********************************************************************************************************************************/


MsvMainInitializer::MsvMainInitializer()
{

}


MsvMainInitializer::~MsvMainInitializer()
{
	
}


/********************************************************************************************************************************
*															IMsvMainInitializer public methods
********************************************************************************************************************************/


MsvErrorCode MsvMainInitializer::AddModulesToModuleManager(std::shared_ptr<IMsvModuleManager>& spModuleManager, std::shared_ptr<IMsvModules> spModules, std::shared_ptr<IMsvDllFactory> spDllFactory, std::shared_ptr<IMsvActiveConfig> spActiveCfg) const
{
	//static modules
	MSV_RETURN_FAILED(AddModule(spModuleManager, MsvModuleId::MSV_EXAMPLE_STATIC_MODULE_1, new (std::nothrow) MsvExampleModule("MsvStaticModule_1", "MsvStatic_1", spDllFactory), spActiveCfg, MsvActiveCfgKey::MSV_STATIC_MODULE1_ENABLED, MsvActiveCfgKey::MSV_STATIC_MODULE1_INSTALLED));
	MSV_RETURN_FAILED(AddModule(spModuleManager, MsvModuleId::MSV_EXAMPLE_STATIC_MODULE_2, new (std::nothrow) MsvExampleModule("MsvStaticModule_2", "MsvStatic_2", spDllFactory), spActiveCfg, MsvActiveCfgKey::MSV_STATIC_MODULE2_ENABLED, MsvActiveCfgKey::MSV_STATIC_MODULE2_INSTALLED));
	
	//dynamic modules
	MSV_RETURN_FAILED(AddModule(spModuleManager, MsvModuleId::MSV_EXAMPLE_DYNAMIC_MODULE_1, spModules, MSV_EXAMPLEMODULE1_OBJECT_ID, spDllFactory, spActiveCfg, MsvActiveCfgKey::MSV_DYNAMIC_MODULE1_ENABLED, MsvActiveCfgKey::MSV_DYNAMIC_MODULE1_INSTALLED));
	MSV_RETURN_FAILED(AddModule(spModuleManager, MsvModuleId::MSV_EXAMPLE_DYNAMIC_MODULE_2, spModules, MSV_EXAMPLEMODULE2_OBJECT_ID, spDllFactory, spActiveCfg, MsvActiveCfgKey::MSV_DYNAMIC_MODULE2_ENABLED, MsvActiveCfgKey::MSV_DYNAMIC_MODULE2_INSTALLED));

	return MSV_SUCCESS;
}

MsvErrorCode MsvMainInitializer::GetActiveConfigData(const std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig, std::string& configPath, std::string& configGroup) const
{
	MSV_RETURN_FAILED(spPassiveConfig->GetValue(static_cast<int32_t>(MsvPassiveCfgKey::MAIN_ACTIVECFG_PATH), configPath));
	MSV_RETURN_FAILED(spPassiveConfig->GetValue(static_cast<int32_t>(MsvPassiveCfgKey::MAIN_ACTIVECFG_GROUP), configGroup));

	return MSV_SUCCESS;
}

MsvErrorCode MsvMainInitializer::GetMsvLoggerProviderData(const std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig, std::string& logFolder, std::string& logFile, uint32_t& maxLogFileSize, uint32_t& maxLogFiles) const
{
	MSV_RETURN_FAILED(spPassiveConfig->GetValue(static_cast<int32_t>(MsvPassiveCfgKey::MAIN_LOG_FOLDER), logFolder));
	MSV_RETURN_FAILED(spPassiveConfig->GetValue(static_cast<int32_t>(MsvPassiveCfgKey::MAIN_LOG_FILE), logFile));
	MSV_RETURN_FAILED((spPassiveConfig->GetValue<uint32_t, uint64_t>(static_cast<int32_t>(MsvPassiveCfgKey::MAIN_LOG_FILEMAXSIZE), maxLogFileSize)));
	MSV_RETURN_FAILED((spPassiveConfig->GetValue<uint32_t, uint64_t>(static_cast<int32_t>(MsvPassiveCfgKey::MAIN_LOG_MAXFILES), maxLogFiles)));

	return MSV_SUCCESS;
}

MsvErrorCode MsvMainInitializer::InitializeAndGetActiveConfigKeyMap(std::shared_ptr<IMsvConfigKeyMap<IMsvDefaultValue>>& spActiveCfgKeyMap) const
{
	std::shared_ptr<MsvConfigKeyMapBase<IMsvDefaultValue>> spTempActiveCfgKeyMap(new (std::nothrow) MsvConfigKeyMapBase<IMsvDefaultValue>());
	if (!spTempActiveCfgKeyMap)
	{
		return MSV_ALLOCATION_ERROR;
	}

	//static modules
	MSV_RETURN_FAILED(InsertConfigKey(spTempActiveCfgKeyMap, MsvActiveCfgKey::MSV_STATIC_MODULE1_INSTALLED, new (std::nothrow) MsvDefaultValue(true)));
	MSV_RETURN_FAILED(InsertConfigKey(spTempActiveCfgKeyMap, MsvActiveCfgKey::MSV_STATIC_MODULE1_ENABLED, new (std::nothrow) MsvDefaultValue(true)));
	MSV_RETURN_FAILED(InsertConfigKey(spTempActiveCfgKeyMap, MsvActiveCfgKey::MSV_STATIC_MODULE2_INSTALLED, new (std::nothrow) MsvDefaultValue(true)));
	MSV_RETURN_FAILED(InsertConfigKey(spTempActiveCfgKeyMap, MsvActiveCfgKey::MSV_STATIC_MODULE2_ENABLED, new (std::nothrow) MsvDefaultValue(true)));

	//dynamic modules
	MSV_RETURN_FAILED(InsertConfigKey(spTempActiveCfgKeyMap, MsvActiveCfgKey::MSV_DYNAMIC_MODULE1_INSTALLED, new (std::nothrow) MsvDefaultValue(true)));
	MSV_RETURN_FAILED(InsertConfigKey(spTempActiveCfgKeyMap, MsvActiveCfgKey::MSV_DYNAMIC_MODULE1_ENABLED, new (std::nothrow) MsvDefaultValue(true)));
	MSV_RETURN_FAILED(InsertConfigKey(spTempActiveCfgKeyMap, MsvActiveCfgKey::MSV_DYNAMIC_MODULE2_INSTALLED, new (std::nothrow) MsvDefaultValue(true)));
	MSV_RETURN_FAILED(InsertConfigKey(spTempActiveCfgKeyMap, MsvActiveCfgKey::MSV_DYNAMIC_MODULE2_ENABLED, new (std::nothrow) MsvDefaultValue(true)));

	spActiveCfgKeyMap = spTempActiveCfgKeyMap;

	return MSV_SUCCESS;
}

MsvErrorCode MsvMainInitializer::InitializeAndGetDllList(std::shared_ptr<IMsvDllList>& spDllList) const
{
	std::shared_ptr<MsvDllList> spTempDllList(new (std::nothrow) MsvDllList());
	if (!spTempDllList)
	{
		return MSV_ALLOCATION_ERROR;
	}

	MSV_RETURN_FAILED(spTempDllList->AddDll(MSV_SYS_OBJECT_ID_LAST, "msys.dll"));
	MSV_RETURN_FAILED(spTempDllList->AddDll(MSV_EXAMPLEMODULE1_OBJECT_ID, "msvexamplemodule.dll"));
	MSV_RETURN_FAILED(spTempDllList->AddDll(MSV_EXAMPLEMODULE2_OBJECT_ID, "msvexamplemodule.dll"));

	spDllList = spTempDllList;

	return MSV_SUCCESS;
}

MsvErrorCode MsvMainInitializer::InitializeAndGetPassiveConfigKeyMap(std::shared_ptr<IMsvConfigKeyMap<IMsvConfigKey>>& spPassiveCfgKeyMap) const
{
	std::shared_ptr<MsvConfigKeyMapBase<IMsvConfigKey>> spTempPassiveCfgKeyMap(new (std::nothrow) MsvConfigKeyMapBase<IMsvConfigKey>());
	if (!spTempPassiveCfgKeyMap)
	{
		return MSV_ALLOCATION_ERROR;
	}
	
	//MsvMain: logging settings
	MSV_RETURN_FAILED(InsertConfigKey(spTempPassiveCfgKeyMap, MsvPassiveCfgKey::MAIN_LOG_FOLDER, PCFG_LOGGING_GROUP, "LogFolder", new (std::nothrow) MsvDefaultValue("./log")));
	MSV_RETURN_FAILED(InsertConfigKey(spTempPassiveCfgKeyMap, MsvPassiveCfgKey::MAIN_LOG_FILE, PCFG_LOGGING_GROUP, "LogFile", new (std::nothrow) MsvDefaultValue("msvlog.txt")));
	MSV_RETURN_FAILED(InsertConfigKey(spTempPassiveCfgKeyMap, MsvPassiveCfgKey::MAIN_LOG_FILEMAXSIZE, PCFG_LOGGING_GROUP, "MaxLogFileSize", new (std::nothrow) MsvDefaultValue(10485760ull)));
	MSV_RETURN_FAILED(InsertConfigKey(spTempPassiveCfgKeyMap, MsvPassiveCfgKey::MAIN_LOG_MAXFILES, PCFG_LOGGING_GROUP, "MaxLogFiles", new (std::nothrow) MsvDefaultValue(3ull)));

	//MsvMain: active config settings
	MSV_RETURN_FAILED(InsertConfigKey(spTempPassiveCfgKeyMap, MsvPassiveCfgKey::MAIN_ACTIVECFG_PATH, PCFG_ACTIVECFG_GROUP, "ConfigPath", new (std::nothrow) MsvDefaultValue("./config.db")));
	MSV_RETURN_FAILED(InsertConfigKey(spTempPassiveCfgKeyMap, MsvPassiveCfgKey::MAIN_ACTIVECFG_GROUP, PCFG_ACTIVECFG_GROUP, "ConfigGroup", new (std::nothrow) MsvDefaultValue("MsvConfig")));

	spPassiveCfgKeyMap = spTempPassiveCfgKeyMap;

	return MSV_SUCCESS;
}




/** @} */	//End of group MSVEXAMPLE.
