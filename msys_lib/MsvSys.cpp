/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech SYS Implementation
* @details		Contains implementation of @ref MsvSys.
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


#include "MsvSys.h"
#include "msys/configuration/MsvConfiguration.h"
#include "msys/logging/MsvLogging.h"
#include "msys/threading/MsvThreading.h"

#include "merror/MsvErrorCodes.h"


/********************************************************************************************************************************
*															Constructors and destructors
********************************************************************************************************************************/


MsvSys::MsvSys()
{

}


MsvSys::~MsvSys()
{

}


/********************************************************************************************************************************
*															IMsvSys public methods
********************************************************************************************************************************/


MsvErrorCode MsvSys::GetMsvConfiguration(std::shared_ptr<IMsvConfiguration>& spConfiguration) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (!m_spConfiguration)
	{
		m_spConfiguration.reset(new (std::nothrow) MsvConfiguration());
		if (!m_spConfiguration)
		{
			return MSV_ALLOCATION_ERROR;
		}
	}

	spConfiguration = m_spConfiguration;

	return MSV_SUCCESS;
}

MsvErrorCode MsvSys::GetMsvLogging(std::shared_ptr<IMsvLogging>& spLogging) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (!m_spLogging)
	{
		m_spLogging.reset(new (std::nothrow) MsvLogging());
		if (!m_spLogging)
		{
			return MSV_ALLOCATION_ERROR;
		}
	}

	spLogging = m_spLogging;

	return MSV_SUCCESS;
}

MsvErrorCode MsvSys::GetMsvThreading(std::shared_ptr<IMsvThreading>& spThreading) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (!m_spThreading)
	{
		m_spThreading.reset(new (std::nothrow) MsvThreading());
		if (!m_spThreading)
		{
			return MSV_ALLOCATION_ERROR;
		}
	}

	spThreading = m_spThreading;

	return MSV_SUCCESS;
}


/** @} */	//End of group MSYS.
