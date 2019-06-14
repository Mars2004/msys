/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech SYS Implementation
* @details		Contains implementation @ref MsvSys of @ref IMsvSys interface.
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


#ifndef MARSTECH_SYS_H
#define MARSTECH_SYS_H


#include "IMsvSys.h"

MSV_DISABLE_ALL_WARNINGS

#include <mutex>

MSV_ENABLE_WARNINGS


/**************************************************************************************************//**
* @brief		MarsTech SYS Implementation.
* @details	Implementation of SYS interface for easy access to all SYS interfaces and its implementations.
* @see		IMsvSys
******************************************************************************************************/
class MsvSys:
	public IMsvSys
{
public:
	/**************************************************************************************************//**
	* @brief		Constructor.
	******************************************************************************************************/
	MsvSys();

	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~MsvSys();

	/**************************************************************************************************//**
	* @copydoc IMsvSys::GetMsvConfiguration(std::shared_ptr<IMsvConfiguration>& spConfiguration) const
	******************************************************************************************************/
	virtual MsvErrorCode GetMsvConfiguration(std::shared_ptr<IMsvConfiguration>& spConfiguration) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvSys::GetMsvLogging(std::shared_ptr<IMsvLogging>& spLogging) const
	******************************************************************************************************/
	virtual MsvErrorCode GetMsvLogging(std::shared_ptr<IMsvLogging>& spLogging) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvSys::GetMsvModules(std::shared_ptr<IMsvModules>& spModules) const
	******************************************************************************************************/
	virtual MsvErrorCode GetMsvModules(std::shared_ptr<IMsvModules>& spModules) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvSys::GetMsvThreading(std::shared_ptr<IMsvThreading>& spThreading) const
	******************************************************************************************************/
	virtual MsvErrorCode GetMsvThreading(std::shared_ptr<IMsvThreading>& spThreading) const override;

protected:
	/**************************************************************************************************//**
	* @brief		Thread mutex.
	* @details	Locks this object for thread safety access.
	******************************************************************************************************/
	mutable std::recursive_mutex m_lock;

	/**************************************************************************************************//**
	* @brief		Shared Configuration.
	* @details	It is returned by @ref GetMsvConfiguration.
	* @see		IMsvConfiguration
	******************************************************************************************************/
	mutable std::shared_ptr<IMsvConfiguration> m_spConfiguration;

	/**************************************************************************************************//**
	* @brief		Shared Logging.
	* @details	It is returned by @ref GetMsvLogging.
	* @see		IMsvLogging
	******************************************************************************************************/
	mutable std::shared_ptr<IMsvLogging> m_spLogging;

	/**************************************************************************************************//**
	* @brief		Shared Modules.
	* @details	It is returned by @ref GetMsvModules.
	* @see		IMsvModules
	******************************************************************************************************/
	mutable std::shared_ptr<IMsvModules> m_spModules;

	/**************************************************************************************************//**
	* @brief		Shared Threading.
	* @details	It is returned by @ref GetMsvThreading.
	* @see		IMsvThreading
	******************************************************************************************************/
	mutable std::shared_ptr<IMsvThreading> m_spThreading;
};


#endif // MARSTECH_SYS_H

/** @} */	//End of group MSYS.
