/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Example Module Implementation
* @details		Contains implementation @ref MsvExampleModule of @ref IMsvDllModule interface.
* @author		Martin Svoboda
* @date			19.05.2019
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


#ifndef MARSTECH_EXAMPLEMODULE_H
#define MARSTECH_EXAMPLEMODULE_H


#include "mmodule/MsvDllModuleBase.h"

#include "mlogging/mlogging.h"


/**************************************************************************************************//**
* @brief		MarsTech Example Module.
* @details	Example module.
* @note		This example module will be used as static and dynamic module.
******************************************************************************************************/
class MsvExampleModule:
	public MsvDllModuleBase
{
public:
	/**************************************************************************************************//**
	* @brief			Constructor.
	* @param[in]	moduleName			Example module name.
	* @param[in]	moduleLoggerName	Name of logger used for logging.
	* @param[in]	spDllFactory		Shared pointer to DLL factory.
	* @note			Parameter spDllFactory will be used for static versions of this module.
	******************************************************************************************************/
	MsvExampleModule(const char* moduleName = "MsvDllModule", const char* moduleLoggerName = "MsvDllModule", std::shared_ptr<IMsvDllFactory> spDllFactory = nullptr);

	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~MsvExampleModule();

	/*-----------------------------------------------------------------------------------------------------
	**											IMsvModule public methods
	**---------------------------------------------------------------------------------------------------*/
public:
	/**************************************************************************************************//**
	* @copydoc IMsvModule::Initialize()
	******************************************************************************************************/
	virtual MsvErrorCode Initialize() override;

	/**************************************************************************************************//**
	* @copydoc IMsvModule::Uninitialize()
	******************************************************************************************************/
	virtual MsvErrorCode Uninitialize() override;

	/**************************************************************************************************//**
	* @copydoc IMsvModule::Start()
	******************************************************************************************************/
	virtual MsvErrorCode Start() override;

	/**************************************************************************************************//**
	* @copydoc IMsvModule::Stop()
	******************************************************************************************************/
	virtual MsvErrorCode Stop() override;

protected:
	/**************************************************************************************************//**
	* @brief		Thread entry point.
	* @details	This method will be called by @ref m_spUniqueWorker to execute task/job in interval.
	* @see		m_spUniqueWorker
	******************************************************************************************************/
	void OnTask();

protected:
	/**************************************************************************************************//**
	* @brief		Example module name.
	* @details	Example module name used for logging.
	******************************************************************************************************/
	std::string m_moduleName;

	/**************************************************************************************************//**
	* @brief		Example module logger name.
	* @details	Example module logger name used for logging.
	******************************************************************************************************/
	std::string m_moduleLoggerName;

	/**************************************************************************************************//**
	* @brief		Unique worker.
	* @details	Thread which wil execute job of example module.
	* @see		OnTask
	******************************************************************************************************/
	std::shared_ptr<IMsvUniqueWorker> m_spUniqueWorker;
};


#endif // !MARSTECH_EXAMPLEMODULE_H

/** @} */	//End of group MSVEXAMPLE.
