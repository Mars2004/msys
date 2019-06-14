/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Module Example Implementation
* @details		Contains implementation of @ref MsvExampleModule.
* @author		Martin Svoboda
* @date			26.05.2019
* @copyright	GNU General Public License (GPLv3).
******************************************************************************************************/


/*
This file is part of MarsTech Module C++ SYS Library.

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


#include "MsvExampleModule.h"


/********************************************************************************************************************************
*															Constructors and destructors
********************************************************************************************************************************/


MsvExampleModule::MsvExampleModule(const char* moduleName, const char* moduleLoggerName, std::shared_ptr<IMsvDllFactory> spDllFactory):
	MsvDllModuleBase(),
	m_moduleName(moduleName),
	m_moduleLoggerName(moduleLoggerName)
{
	m_spDllFactory = spDllFactory;
}


MsvExampleModule::~MsvExampleModule()
{
	Stop();
	Uninitialize();

	m_spUniqueWorker.reset();
	m_spLogger.reset();
	m_spSys.reset();
	m_spDllFactory.reset();
}


/********************************************************************************************************************************
*															IMsvModule public methods
********************************************************************************************************************************/


MsvErrorCode MsvExampleModule::Initialize()
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (Initialized())
	{
		MSV_LOG_INFO(m_spLogger, "Module {} has been already initialized.", m_moduleName);
		return MSV_ALREADY_INITIALIZED_INFO;
	}

	//initialize DLL module base (m_spSys and m_spLogger)
	MSV_RETURN_FAILED(InitializeDllModuleBase(m_moduleLoggerName.c_str()));

	MSV_LOG_INFO(m_spLogger, "Initializing module {}.", m_moduleName);

	//it is just example -> without logging (real implementation should log errors)
	std::shared_ptr<IMsvThreading> spThreading;
	MSV_RETURN_FAILED(m_spSys->GetMsvThreading(spThreading));
	MSV_RETURN_FAILED(spThreading->GetUniqueWorker(m_spUniqueWorker));

	std::function<void(void*)> voidContextFunction = [](void* pContext) { static_cast<MsvExampleModule*>(pContext)->OnTask(); };
	m_spUniqueWorker->SetTask(voidContextFunction, this);

	m_initialized = true;

	MSV_LOG_INFO(m_spLogger, "Module {} has been successfully initialized.", m_moduleName);

	return MSV_SUCCESS;
}

MsvErrorCode MsvExampleModule::Uninitialize()
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	MSV_LOG_INFO(m_spLogger, "Uninitializing module {}.", m_moduleName);

	if (Running())
	{
		MSV_LOG_ERROR(m_spLogger, "Module {} still running - can not be uninitialized.", m_moduleName);
		return MSV_STILL_RUNNING_ERROR;
	}

	if (!Initialized())
	{
		MSV_LOG_INFO(m_spLogger, "Module {} has not been initialized.", m_moduleName);
		return MSV_NOT_INITIALIZED_INFO;
	}

	//it is just example -> without logging (real implementation should log errors)
	MSV_RETURN_FAILED(m_spUniqueWorker->WaitForThreadStop());

	m_initialized = false;

	MSV_LOG_INFO(m_spLogger, "Module {} has been successfully uninitialized.", m_moduleName);

	return MSV_SUCCESS;
}

MsvErrorCode MsvExampleModule::Start()
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	MSV_LOG_INFO(m_spLogger, "Starting module {}.", m_moduleName);

	if (!Initialized())
	{
		MSV_LOG_ERROR(m_spLogger, "Module {} has not been initialized - failed with error: {0:x}", m_moduleName, MSV_NOT_INITIALIZED_ERROR);
		return MSV_NOT_INITIALIZED_ERROR;
	}

	if (Running())
	{
		MSV_LOG_INFO(m_spLogger, "Module {} has been already started.", m_moduleName);
		return MSV_ALREADY_RUNNING_INFO;
	}

	//it is just example -> without logging (real implementation should log errors)
	MSV_RETURN_FAILED(m_spUniqueWorker->StartThread(100000));		//100 milliseconds

	m_running = true;

	MSV_LOG_INFO(m_spLogger, "Module {} has been successfully started.", m_moduleName);

	return MSV_SUCCESS;
}

MsvErrorCode MsvExampleModule::Stop()
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	MSV_LOG_INFO(m_spLogger, "Stopping module {}.", m_moduleName);

	if (!Running())
	{
		MSV_LOG_INFO(m_spLogger, "Module {} has not been started.", m_moduleName);
		return MSV_NOT_RUNNING_INFO;
	}

	//it is just example -> without logging (real implementation should log errors)
	MSV_RETURN_FAILED(m_spUniqueWorker->StopThread());

	m_running = false;

	MSV_LOG_INFO(m_spLogger, "Module {} has been successfully stopped.", m_moduleName);

	return MSV_SUCCESS;
}


/********************************************************************************************************************************
*															MsvExampleModule protected methods
********************************************************************************************************************************/


void MsvExampleModule::OnTask()
{
	MSV_LOG_INFO(m_spLogger, "Executing task of module {}.", m_moduleName);
}


/** @} */	//End of group MSVEXAMPLE.
