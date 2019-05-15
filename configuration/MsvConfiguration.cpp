/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Configuration Implementation
* @details		Contains implementation of @ref MsvConfiguration.
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


#include "MsvConfiguration.h"

#include "mconfig/mactivecfg/MsvActiveConfig.h"
#include "mconfig/mpassivecfg/MsvPassiveConfig.h"
#include "mconfig/msqlitewrapper/MsvSQLite.h"

#include "merror/MsvErrorCodes.h"


/********************************************************************************************************************************
*															Constructors and destructors
********************************************************************************************************************************/


MsvConfiguration::MsvConfiguration()
{

}


MsvConfiguration::~MsvConfiguration()
{
	
}


/********************************************************************************************************************************
*															IMsvConfiguration public methods
********************************************************************************************************************************/


MsvErrorCode MsvConfiguration::GetActiveConfigSQLite(std::shared_ptr<IMsvActiveConfig>& spActiveConfig, std::shared_ptr<MsvLogger> spLogger) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	std::shared_ptr<IMsvActiveConfig> spTempActiveConfig(new (std::nothrow) MsvActiveConfig(spLogger));

	if (!spTempActiveConfig)
	{
		return MSV_ALLOCATION_ERROR;
	}

	spActiveConfig = spTempActiveConfig;

	return MSV_SUCCESS;
}

MsvErrorCode MsvConfiguration::GetPassiveConfigIniFile(std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	std::shared_ptr<IMsvPassiveConfig> spTempPassiveConfig(new (std::nothrow) MsvPassiveConfig());

	if (!spTempPassiveConfig)
	{
		return MSV_ALLOCATION_ERROR;
	}

	spPassiveConfig = spTempPassiveConfig;

	return MSV_SUCCESS;
}

MsvErrorCode MsvConfiguration::GetSharedActiveConfigSQLite(std::shared_ptr<IMsvActiveConfig>& spActiveConfig, std::shared_ptr<MsvLogger> spLogger) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (!spSharedActiveConfigSQLite)
	{
		//if GetActiveConfigSQLite fails it does not set out shared pointer -> spSharedActiveConfigSQLite is unset when failed
		MSV_RETURN_FAILED(GetActiveConfigSQLite(spSharedActiveConfigSQLite, spLogger));
	}

	spActiveConfig = spSharedActiveConfigSQLite;

	return MSV_SUCCESS;
}

MsvErrorCode MsvConfiguration::GetSharedPassiveConfigIniFile(std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (!m_spSharedPassiveConfigIniFile)
	{
		//if GetPassiveConfigIniFile fails it does not set out shared pointer -> m_spSharedPassiveConfigIniFile is unset when failed
		MSV_RETURN_FAILED(GetPassiveConfigIniFile(m_spSharedPassiveConfigIniFile));
	}

	spPassiveConfig = m_spSharedPassiveConfigIniFile;

	return MSV_SUCCESS;
}

MsvErrorCode MsvConfiguration::GetSQLite(std::shared_ptr<IMsvSQLite>& spSQLite, std::shared_ptr<MsvLogger> spLogger) const
{
	std::shared_ptr<IMsvSQLite> spTempSQLite(new (std::nothrow) MsvSQLite(spLogger));

	if (!spTempSQLite)
	{
		return MSV_ALLOCATION_ERROR;
	}

	spSQLite = spTempSQLite;

	return MSV_SUCCESS;
}


/** @} */	//End of group MSYS.
