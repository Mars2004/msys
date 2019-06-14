/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Main Implementation
* @details		Contains implementation @ref MsvMain of @ref IMsvMain interface.
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


#ifndef MARSTECH_MAIN_H
#define MARSTECH_MAIN_H


#include "IMsvMain.h"
#include "mheaders/MsvObject.h"
#include "IMsvMainInitializer.h"

#include "msys/msys/MsvSysDll_Interface.h"


//forward declaration of MarsTech Main Dependency Injection Factory
class MsvMain_Factory;


/**************************************************************************************************//**
* @brief		MarsTech Main Implementation.
* @details	Main implementation which creates and initializes all objects/classes/data
*				required by a program.
******************************************************************************************************/
class MsvMain:
	public MsvObject<IMsvMain>
{
public:
	/**************************************************************************************************//**
	* @brief			Constructor.
	* @param[in]	argc						Argument count.
	* @param[in]	argv						Argument vector.
	* @param[in]	spMainInitializer		Shared pointer to main initializer with main data.
	* @param[in]	spFactory				Shared pointer to dependency injection factory.
	* @see			MsvMain_Factory
	* @see			IMsvMainInitializer
	******************************************************************************************************/
	MsvMain(int argc, char *argv[], std::shared_ptr<IMsvMainInitializer> spMainInitializer, std::shared_ptr<MsvMain_Factory> spFactory = nullptr);

	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~MsvMain();

	/*-----------------------------------------------------------------------------------------------------
	**											IMsvMain public methods
	**---------------------------------------------------------------------------------------------------*/
public:
	/**************************************************************************************************//**
	* @copydoc IMsvMain::OnSignal(int signal)
	******************************************************************************************************/
	virtual void OnSignal(int signal) override;

	/**************************************************************************************************//**
	* @copydoc IMsvMain::WaitForStopRequest()
	******************************************************************************************************/
	virtual MsvErrorCode WaitForStopRequest() override;

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

	/*-----------------------------------------------------------------------------------------------------
	**											MsvMain protected methods
	**---------------------------------------------------------------------------------------------------*/
protected:
	/**************************************************************************************************//**
	* @brief			Initialize passive config.
	* @details		Initializes passive config @ref m_spPassiveConfig.
	* @retval		other_error_code					When failed.
	* @retval		MSV_SUCCESS							On success.
	* @warning		Must be called as the first of protected Initialize methods.
	******************************************************************************************************/
	MsvErrorCode InitializePassiveConfig();

	/**************************************************************************************************//**
	* @brief			Initialize logging.
	* @details		Initializes logger provider @ref m_spLoggerProvider and @ref m_spLogger.
	* @retval		other_error_code					When failed.
	* @retval		MSV_SUCCESS							On success.
	* @warning		@ref InitializePassiveConfig must be called before calling this method.
	******************************************************************************************************/
	MsvErrorCode InitializeLogging();

	/**************************************************************************************************//**
	* @brief			Initialize MasTech SYS.
	* @details		Initializes SYS @ref m_spSys and DLL factory @ref m_spDllFactory.
	* @retval		other_error_code					When failed.
	* @retval		MSV_SUCCESS							On success.
	* @warning		@ref InitializeLogging must be called before calling this method.
	******************************************************************************************************/
	MsvErrorCode InitializeSys();

	/**************************************************************************************************//**
	* @brief			Initialize active config.
	* @details		Initializes SYS @ref m_spActiveConfig.
	* @retval		other_error_code					When failed.
	* @retval		MSV_SUCCESS							On success.
	* @warning		@ref InitializeSys must be called before calling this method.
	******************************************************************************************************/
	MsvErrorCode InitializeActiveConfig();

	/**************************************************************************************************//**
	* @brief			Initialize threading.
	* @details		Initializes threading @ref m_spThreading and stop event @ref m_spStopEvent.
	* @retval		other_error_code					When failed.
	* @retval		MSV_SUCCESS							On success.
	* @warning		@ref InitializeActiveConfig must be called before calling this method.
	******************************************************************************************************/
	MsvErrorCode InitializeThreading();

	/**************************************************************************************************//**
	* @brief			Initialize module manager.
	* @details		Initializes modules @ref m_spModules and module manager @ref m_spModuleManager.
	* @retval		other_error_code					When failed.
	* @retval		MSV_SUCCESS							On success.
	* @warning		@ref InitializeThreading must be called before calling this method.
	******************************************************************************************************/
	MsvErrorCode InitializeModuleManager();

protected:
	/**************************************************************************************************//**
	* @brief		Active config.
	* @details	Active config object with whole active configuration (can be changed by application).
	******************************************************************************************************/
	std::shared_ptr<IMsvActiveConfig> m_spActiveCfg;

	/**************************************************************************************************//**
	* @brief		Object Configuration.
	* @details	Provides methods to get configuration objects.
	******************************************************************************************************/
	std::shared_ptr<IMsvConfiguration> m_spConfiguration;

	/**************************************************************************************************//**
	* @brief		DLL factory.
	* @details	Contains get method for all DLLs and DLL objects.
	******************************************************************************************************/
	std::shared_ptr<IMsvDllFactory> m_spDllFactory;

	/**************************************************************************************************//**
	* @brief		Passive config.
	* @details	Passive config object which is always statically linked.
	* @note		We need it as soon as possible and before any DLL is loaded - contains configuration for logging.
	******************************************************************************************************/
	std::shared_ptr<IMsvPassiveConfig> m_spPassiveCfg;

	/**************************************************************************************************//**
	* @brief		Logger provider.
	* @details	Logger provider to obtain loggers.
	* @note		We need it as soon as possible and before any DLL is loaded - we want to log as soon as possible.
	******************************************************************************************************/
	std::shared_ptr<IMsvLoggerProvider> m_spLoggerProvider;

	/**************************************************************************************************//**
	* @brief		Main initializer.
	* @details	Provides methods to get and initialize main.
	******************************************************************************************************/
	std::shared_ptr<IMsvMainInitializer> m_spMainInitializer;

	/**************************************************************************************************//**
	* @brief		Module manager.
	* @details	Provides methods to manage all appliacation modules.
	******************************************************************************************************/
	std::shared_ptr<IMsvModuleManager> m_spModuleManager;

	/**************************************************************************************************//**
	* @brief		Object Modules.
	* @details	Provides methods to get module manager and modules.
	******************************************************************************************************/
	std::shared_ptr<IMsvModules> m_spModules;
	
	/**************************************************************************************************//**
	* @brief		Stop event.
	* @details	@ref WaitForStopRequest waits for this event. It is set in @ref OnSignal.
	******************************************************************************************************/
	std::shared_ptr<IMsvEvent> m_spStopEvent;

	/**************************************************************************************************//**
	* @brief		MarsTech SYS.
	* @details	SYS object - can be statically linked or dynamically loaded.
	******************************************************************************************************/
	std::shared_ptr<IMsvSys_Last> m_spSys;

	/**************************************************************************************************//**
	* @brief		Object Threading.
	* @details	Provides methods to get threads/workers/events/etc.
	******************************************************************************************************/
	std::shared_ptr<IMsvThreading> m_spThreading;

	/**************************************************************************************************//**
	* @brief		Dependency injection factory.
	* @details	Contains get method for all injected objects.
	* @see		MsvMain_Factory
	******************************************************************************************************/
	std::shared_ptr<MsvMain_Factory> m_spFactory;	
};


#endif // !MARSTECH_MAIN_H

/** @} */	//End of group MSVEXAMPLE.
