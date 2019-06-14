/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Main Implementation
* @details		Contains implementation of @ref MsvMain.
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


#include "MsvMain.h"
#include "MsvMain_Factory.h"

#include "mlogging/mlogging.h"
#include "merror/MsvErrorCodes.h"


/********************************************************************************************************************************
*															Constructors and destructors
********************************************************************************************************************************/


MsvMain::MsvMain(int argc, char *argv[], std::shared_ptr<IMsvMainInitializer> spMainInitializer, std::shared_ptr<MsvMain_Factory> spFactory):
	MsvObject(nullptr),
	m_spFactory(spFactory ? spFactory : MsvMain_Factory::Get()),
	m_spMainInitializer(spMainInitializer)
{
	//unused parameters
	(void) argc;
	(void) argv;
}


MsvMain::~MsvMain()
{
	Stop();
	Uninitialize();
}


/********************************************************************************************************************************
*															IMsvMain public methods
********************************************************************************************************************************/


void MsvMain::OnSignal(int signal)
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (!Initialized())
	{
		return;
	}

	MSV_LOG_INFO(m_spLogger, "Signal {} has been received.", signal);

	//set stop event
	m_spStopEvent->SetEvent(true);

	MSV_LOG_INFO(m_spLogger, "Stop event has been set.");
}

MsvErrorCode MsvMain::WaitForStopRequest()
{
	return m_spStopEvent->WaitForEvent();
}


/********************************************************************************************************************************
*															IMsvModule public methods
********************************************************************************************************************************/


MsvErrorCode MsvMain::Initialize()
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (Initialized())
	{
		return MSV_ALREADY_INITIALIZED_INFO;
	}

	if (!m_spMainInitializer)
	{
		return MSV_INVALID_DATA_ERROR;
	}

	if (!m_spFactory)
	{
		return MSV_ALLOCATION_ERROR;
	}

	MSV_RETURN_FAILED(InitializePassiveConfig());
	MSV_RETURN_FAILED(InitializeLogging());
	MSV_RETURN_FAILED(InitializeSys());
	MSV_RETURN_FAILED(InitializeActiveConfig());
	MSV_RETURN_FAILED(InitializeThreading());
	MSV_RETURN_FAILED(InitializeModuleManager());

	//these objects are used just in initialize -> release them
	m_spMainInitializer.reset();
	m_spFactory.reset();

	m_initialized = true;

	MSV_LOG_INFO(m_spLogger, "Main has been successfully initialized.");

	return MSV_SUCCESS;

}

MsvErrorCode MsvMain::Uninitialize()
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	MSV_LOG_INFO(m_spLogger, "Uninitializing main.");

	if (Running())
	{
		MSV_LOG_ERROR(m_spLogger, "Main still running - can not be uninitialized.");
		return MSV_STILL_RUNNING_ERROR;
	}

	if (!Initialized())
	{
		MSV_LOG_INFO(m_spLogger, "Main has not been initialized.");
		return MSV_NOT_INITIALIZED_INFO;
	}

	MsvErrorCode errorCode = m_spModuleManager->Uninitialize();

	if (MSV_FAILED(errorCode))
	{
		MSV_LOG_ERROR(m_spLogger, "Uninitialize module manager failed with error: {0:x}", errorCode);
	}

	m_spModuleManager.reset();
	m_spModules.reset();

	if (MSV_FAILED(errorCode = m_spActiveCfg->Uninitialize()))
	{
		MSV_LOG_ERROR(m_spLogger, "Uninitialize active config failed with error: {0:x}", errorCode);
	}

	m_spActiveCfg.reset();
	m_spConfiguration.reset();

	m_spStopEvent.reset();
	m_spThreading.reset();

	m_spSys.reset();

	m_spDllFactory.reset();

	m_spPassiveCfg.reset();

	m_initialized = false;

	MSV_LOG_INFO(m_spLogger, "Main has been successfully uninitialized.");

	return MSV_SUCCESS;
}

MsvErrorCode MsvMain::Start()
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	MSV_LOG_INFO(m_spLogger, "Starting main.");

	if (!Initialized())
	{
		MSV_LOG_ERROR(m_spLogger, "Main has not been initialized - failed with error: {0:x}", MSV_NOT_INITIALIZED_ERROR);
		return MSV_NOT_INITIALIZED_ERROR;
	}

	if (Running())
	{
		MSV_LOG_INFO(m_spLogger, "Main has been already started.");
		return MSV_ALREADY_RUNNING_INFO;
	}

	MsvErrorCode errorCode = m_spModuleManager->Start();

	if (MSV_FAILED(errorCode))
	{
		MSV_LOG_ERROR(m_spLogger, "Start module manager failed with error: {0:x}", errorCode);
		return errorCode;
	}

	m_running = true;

	MSV_LOG_INFO(m_spLogger, "Main has been successfully started.");

	return MSV_SUCCESS;
}

MsvErrorCode MsvMain::Stop()
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	MSV_LOG_INFO(m_spLogger, "Stopping main.");

	if (!Running())
	{
		MSV_LOG_INFO(m_spLogger, "Main has not been started.");
		return MSV_NOT_RUNNING_INFO;
	}

	MsvErrorCode errorCode = m_spModuleManager->Stop();

	if (MSV_FAILED(errorCode))
	{
		MSV_LOG_ERROR(m_spLogger, "Stop module manager failed with error: {0:x}", errorCode);
	}

	m_running = false;

	MSV_LOG_INFO(m_spLogger, "Main has been successfully stopped.");

	return MSV_SUCCESS;
}


/********************************************************************************************************************************
*															MsvMain public methods
********************************************************************************************************************************/


MsvErrorCode MsvMain::InitializePassiveConfig()
{
	std::shared_ptr<IMsvConfigKeyMap<IMsvConfigKey>> spPassiveCfgKeyMap;
	MSV_RETURN_FAILED(m_spMainInitializer->InitializeAndGetPassiveConfigKeyMap(spPassiveCfgKeyMap));

	m_spPassiveCfg = m_spFactory->GetIMsvPassiveConfig();
	if (!m_spPassiveCfg)
	{
		return MSV_ALLOCATION_ERROR;
	} 

	return m_spPassiveCfg->Initialize(spPassiveCfgKeyMap);
}

MsvErrorCode MsvMain::InitializeLogging()
{
	std::string logFolder("."), logFile("MsvExample.log");
	uint32_t maxLogFileSize = 10485760, maxLogFiles = 3;

	MSV_RETURN_FAILED(m_spMainInitializer->GetMsvLoggerProviderData(m_spPassiveCfg, logFolder, logFile, maxLogFileSize, maxLogFiles));
	m_spLoggerProvider = m_spFactory->GetIMsvLoggerProvider(logFolder.c_str(), logFile.c_str(), maxLogFileSize, maxLogFiles);
	if (!m_spLoggerProvider)
	{
		return MSV_ALLOCATION_ERROR;
	}

	m_spLogger = m_spLoggerProvider->GetLogger("MsvMain");
	if (!m_spLogger)
	{
		return MSV_ALLOCATION_ERROR;
	}

	MSV_LOG_INFO(m_spLogger, "Logging has been successfully initialized.");

	return MSV_SUCCESS;
}

MsvErrorCode MsvMain::InitializeSys()
{
	MSV_LOG_INFO(m_spLogger, "Initializing SYS.");

	std::shared_ptr<IMsvDllList> spDllList;
	MsvErrorCode errorCode = m_spMainInitializer->InitializeAndGetDllList(spDllList);
	if (MSV_FAILED(errorCode))
	{
		MSV_LOG_ERROR(m_spLogger, "Initialize and get DLL list failed with error: {0:x}", errorCode);
		return errorCode;
	}

	m_spDllFactory = m_spFactory->GetIMsvDllFactory(spDllList, m_spLogger);
	if (!m_spDllFactory)
	{
		MSV_LOG_ERROR(m_spLogger, "Get DLL factory failed with error: {0:x}", MSV_ALLOCATION_ERROR);
		return MSV_ALLOCATION_ERROR;
	}

	if (MSV_FAILED(errorCode = m_spDllFactory->GetDllObject(MSV_SYS_OBJECT_ID_LAST, m_spSys)))
	{
		MSV_LOG_ERROR(m_spLogger, "Get SYS DLL object failed with error: {0:x}", errorCode);
		return errorCode;
	}

	std::shared_ptr<IMsvLogging> spLogging;
	if (MSV_FAILED(errorCode = m_spSys->GetMsvLogging(spLogging)))
	{
		MSV_LOG_ERROR(m_spLogger, "Get logging from SYS failed with error: {0:x}", errorCode);
		return errorCode;
	}

	if (MSV_FAILED(errorCode = spLogging->SetLoggerProvider(m_spLoggerProvider)))
	{
		MSV_LOG_ERROR(m_spLogger, "Set logger provider failed with error: {0:x}", errorCode);
		return errorCode;
	}

	MSV_LOG_INFO(m_spLogger, "SYS has been successfully initialized.");

	return MSV_SUCCESS;
}

MsvErrorCode MsvMain::InitializeActiveConfig()
{
	MSV_LOG_INFO(m_spLogger, "Initializing active config.");

	MsvErrorCode errorCode = m_spSys->GetMsvConfiguration(m_spConfiguration);
	if (MSV_FAILED(errorCode))
	{
		MSV_LOG_ERROR(m_spLogger, "Get configuration from SYS failed with error: {0:x}", errorCode);
		return errorCode;
	}

	if (MSV_FAILED(errorCode = m_spConfiguration->GetSharedActiveConfigSQLite(m_spActiveCfg, m_spLogger)))
	{
		MSV_LOG_ERROR(m_spLogger, "Get shared SQLite active config failed with error: {0:x}", errorCode);
		return errorCode;
	}

	std::shared_ptr<IMsvConfigKeyMap<IMsvDefaultValue>> spActiveCfgKeyMap;
	if (MSV_FAILED(errorCode = m_spMainInitializer->InitializeAndGetActiveConfigKeyMap(spActiveCfgKeyMap)))
	{
		MSV_LOG_ERROR(m_spLogger, "Initialize and get active config key map failed with error: {0:x}", errorCode);
		return errorCode;
	}

	std::string configPath("config.db"), configGroup("MsvConfig");
	if (MSV_FAILED(errorCode = m_spMainInitializer->GetActiveConfigData(m_spPassiveCfg, configPath, configGroup)))
	{
		MSV_LOG_ERROR(m_spLogger, "Get active config data failed with error: {0:x}", errorCode);
		return errorCode;
	}

	if (MSV_FAILED(errorCode = m_spActiveCfg->Initialize(spActiveCfgKeyMap, configPath.c_str(), configGroup.c_str())))
	{
		MSV_LOG_ERROR(m_spLogger, "Initialize active config failed with error: {0:x}", errorCode);
		return errorCode;
	}

	MSV_LOG_INFO(m_spLogger, "Active config has been successfully initialized.");

	return MSV_SUCCESS;
}

MsvErrorCode MsvMain::InitializeThreading()
{
	MSV_LOG_INFO(m_spLogger, "Initializing threading.");

	MsvErrorCode errorCode = m_spSys->GetMsvThreading(m_spThreading);
	if (MSV_FAILED(errorCode))
	{
		MSV_LOG_ERROR(m_spLogger, "Get threading from SYS failed with error: {0:x}", errorCode);
		return errorCode;
	}

	if (MSV_FAILED(errorCode = m_spThreading->GetEvent(m_spStopEvent)))
	{
		MSV_LOG_ERROR(m_spLogger, "Get stop event failed with error: {0:x}", errorCode);
		return errorCode;
	}

	MSV_LOG_INFO(m_spLogger, "Threading has been successfully initialized.");

	return MSV_SUCCESS;
}

MsvErrorCode MsvMain::InitializeModuleManager()
{
	MSV_LOG_INFO(m_spLogger, "Initializing module manager.");

	MsvErrorCode errorCode = m_spSys->GetMsvModules(m_spModules);
	if (MSV_FAILED(errorCode))
	{
		MSV_LOG_ERROR(m_spLogger, "Get modules from SYS failed with error: {0:x}", errorCode);
		return errorCode;
	}

	if (MSV_FAILED(errorCode = m_spModules->GetSharedModuleManager(m_spModuleManager)))
	{
		MSV_LOG_ERROR(m_spLogger, "Get shared module manager failed with error: {0:x}", errorCode);
		return errorCode;
	}

	if (MSV_FAILED(errorCode = m_spMainInitializer->AddModulesToModuleManager(m_spModuleManager, m_spModules, m_spDllFactory, m_spActiveCfg)))
	{
		MSV_LOG_ERROR(m_spLogger, "Add modules to module manager failed with error: {0:x}", errorCode);
		return errorCode;
	}

	if (MSV_FAILED(errorCode = m_spModuleManager->Initialize()))
	{
		MSV_LOG_ERROR(m_spLogger, "Initialize module module manager failed with error: {0:x}", errorCode);
		return errorCode;
	}

	MSV_LOG_INFO(m_spLogger, "Module manager has been successfully initialized.");

	return MSV_SUCCESS;
}


/** @} */	//End of group MSVEXAMPLE.
