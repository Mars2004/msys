/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Configuration Implementation
* @details		Contains implementation @ref MsvConfiguration of @ref IMsvConfiguration interface.
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


#ifndef MARSTECH_CONFIGURATION_H
#define MARSTECH_CONFIGURATION_H


#include "IMsvConfiguration.h"


/**************************************************************************************************//**
* @brief		MarsTech Configuration Implementation.
* @details	Implementation of configuration interface for easy access to configuration interfaces and its implementations.
* @see		IMsvConfiguration
******************************************************************************************************/
class MsvConfiguration:
	public IMsvConfiguration
{
public:
	/**************************************************************************************************//**
	* @brief		Constructor.
	******************************************************************************************************/
	MsvConfiguration();

	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~MsvConfiguration();

	/**************************************************************************************************//**
	* @copydoc IMsvConfiguration::GetActiveConfigSQLite(std::shared_ptr<IMsvActiveConfig>& spActiveConfig, std::shared_ptr<MsvLogger> spLogger) const
	******************************************************************************************************/
	virtual MsvErrorCode GetActiveConfigSQLite(std::shared_ptr<IMsvActiveConfig>& spActiveConfig, std::shared_ptr<MsvLogger> spLogger = nullptr) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvConfiguration::GetPassiveConfigIniFile(std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig) const
	******************************************************************************************************/
	virtual MsvErrorCode GetPassiveConfigIniFile(std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvConfiguration::GetSharedActiveConfigSQLite(std::shared_ptr<IMsvActiveConfig>& spActiveConfig, std::shared_ptr<MsvLogger> spLogger) const
	******************************************************************************************************/
	virtual MsvErrorCode GetSharedActiveConfigSQLite(std::shared_ptr<IMsvActiveConfig>& spActiveConfig, std::shared_ptr<MsvLogger> spLogger = nullptr) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvConfiguration::GetSharedPassiveConfigIniFile(std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig) const
	******************************************************************************************************/
	virtual MsvErrorCode GetSharedPassiveConfigIniFile(std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvConfiguration::GetSQLite(std::shared_ptr<IMsvSQLite>& spSQLite, std::shared_ptr<MsvLogger> spLogger) const
	******************************************************************************************************/
	virtual MsvErrorCode GetSQLite(std::shared_ptr<IMsvSQLite>& spSQLite, std::shared_ptr<MsvLogger> spLogger = nullptr) const override;

protected:
	/**************************************************************************************************//**
	* @brief		Thread mutex.
	* @details	Locks this object for thread safety access.
	******************************************************************************************************/
	mutable std::recursive_mutex m_lock;

	/**************************************************************************************************//**
	* @brief		Shared SQLite active config.
	* @details	It is returned by @ref GetActiveConfigSQLite.
	******************************************************************************************************/
	mutable std::shared_ptr<IMsvActiveConfig> spSharedActiveConfigSQLite;

	/**************************************************************************************************//**
	* @brief		Shared INI file passive config.
	* @details	It is returned by @ref GetPassiveConfigIniFile.
	******************************************************************************************************/
	mutable std::shared_ptr<IMsvPassiveConfig> m_spSharedPassiveConfigIniFile;
};


#endif // !MARSTECH_CONFIGURATION_H

/** @} */	//End of group MSYS.
