/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Configuration Interface
* @details		Contains definition of @ref IMsvConfiguration interface.
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


#ifndef MARSTECH_ICONFIGURATION_H
#define MARSTECH_ICONFIGURATION_H


#include "mconfig/mactivecfg/IMsvActiveConfig.h"
#include "mconfig/mpassivecfg/IMsvPassiveConfig.h"
#include "mconfig/msqlitewrapper/IMsvSQLite.h"

#include "mlogging/mlogging.h"


/**************************************************************************************************//**
* @brief		MarsTech Configuration Interface.
* @details	Configuration interface for easy access to configuration interfaces and its implementations.
******************************************************************************************************/
class IMsvConfiguration
{
public:
	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~IMsvConfiguration() {}

	/**************************************************************************************************//**
	* @brief			Get SQLite active config interface.
	* @details		Returns SQLite active interface for active configuration stored in SQLite database.
	* @param[out]	spActiveConfig					Shared pointer to SQLite active config interface @ref IMsvActiveConfig.
	* @param[in]	spLogger							Shared pointer to logger for logging.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @see			IMsvActiveConfig
	******************************************************************************************************/
	virtual MsvErrorCode GetActiveConfigSQLite(std::shared_ptr<IMsvActiveConfig>& spActiveConfig, std::shared_ptr<MsvLogger> spLogger = nullptr) const = 0;

	/**************************************************************************************************//**
	* @brief			Get INI file passive config interface.
	* @details		Returns INI file passive interface for passive configuration stored in INI file.
	* @param[out]	spPassiveConfig				Shared pointer to INI file passive config interface @ref IMsvPassiveConfig.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @see			IMsvPassiveConfig
	******************************************************************************************************/
	virtual MsvErrorCode GetPassiveConfigIniFile(std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig) const = 0;

	/**************************************************************************************************//**
	* @brief			Get SQLite shared active config interface.
	* @details		Returns shared SQLite active interface for active configuration stored in SQLite database.
	*					Each call of this method returns same interface (same shared pointer).
	* @param[out]	spActiveConfig					Shared pointer to SQLite active config interface @ref IMsvActiveConfig.
	* @param[in]	spLogger							Shared pointer to logger for logging.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @note			When @ref IMsvConfiguration is singleton, shared SQLite active config interface is singleton too.
	* @warning		It might be good practice to get and initialize this interface in main function or class
	*					and just use in all other classes/objects/functions.
	* @see			IMsvActiveConfig
	******************************************************************************************************/
	virtual MsvErrorCode GetSharedActiveConfigSQLite(std::shared_ptr<IMsvActiveConfig>& spActiveConfig, std::shared_ptr<MsvLogger> spLogger = nullptr) const = 0;

	/**************************************************************************************************//**
	* @brief			Get INI file shared passive config interface.
	* @details		Returns shared INI file passive interface for passive configuration stored in INI file.
	* @param[out]	spPassiveConfig				Shared pointer to INI file passive config interface @ref IMsvPassiveConfig.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @note			When @ref IMsvConfiguration is singleton, shared INI file passive config interface is singleton too.
	* @warning		It might be good practice to get and initialize this interface in main function or class
	*					and just use in all other classes/objects/functions.
	* @see			IMsvPassiveConfig
	******************************************************************************************************/
	virtual MsvErrorCode GetSharedPassiveConfigIniFile(std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig) const = 0;

	/**************************************************************************************************//**
	* @brief			Get SQLite interface.
	* @details		Returns SQLite interface for any supported operations over SQLite database (it is SQLite wrapper).
	* @param[out]	spSQLite							Shared pointer to SQLite interface @ref IMsvSQLite.
	* @param[in]	spLogger							Shared pointer to logger for logging.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @warning		SQLite value change notification over one SQLite database file are supported only in
	*					one shared instance. When two instances share one SQLite database file, notifications
	*					don't work properly (callbacks will be called for instance which changed database only).
	*					Other instance won't call its callbacks.
	* @warning		Two instances which shares one SQLite database file might not work properly. There is
	*					no locking for SQLite database file.
	* @see			IMsvSQLite
	******************************************************************************************************/
	virtual MsvErrorCode GetSQLite(std::shared_ptr<IMsvSQLite>& spSQLite, std::shared_ptr<MsvLogger> spLogger = nullptr) const = 0;
};


#endif // !MARSTECH_ICONFIGURATION_H

/** @} */	//End of group MSYS.
