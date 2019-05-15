/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Threading Implementation
* @details		Contains implementation @ref MsvThreading of @ref IMsvThreading interface.
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


#ifndef MARSTECH_THREADING_H
#define MARSTECH_THREADING_H


#include "IMsvThreading.h"


/**************************************************************************************************//**
* @brief		MarsTech Threading Implementation.
* @details	Implementation of threading interface for easy access to threading interfaces and its implementations.
* @see		IMsvThreading
******************************************************************************************************/
class MsvThreading:
	public IMsvThreading
{
public:
	/**************************************************************************************************//**
	* @brief		Constructor.
	******************************************************************************************************/
	MsvThreading();

	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~MsvThreading();

	/**************************************************************************************************//**
	* @copydoc IMsvThreading::GetEvent(std::shared_ptr<IMsvEvent>& spEvent) const
	******************************************************************************************************/
	virtual MsvErrorCode GetEvent(std::shared_ptr<IMsvEvent>& spEvent) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvThreading::GetSharedThreadPool(std::shared_ptr<IMsvThreadPool>& spThreadPool) const
	******************************************************************************************************/
	virtual MsvErrorCode GetSharedThreadPool(std::shared_ptr<IMsvThreadPool>& spThreadPool) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvThreading::GetThreadPool(std::shared_ptr<IMsvThreadPool>& spThreadPool) const
	******************************************************************************************************/
	virtual MsvErrorCode GetThreadPool(std::shared_ptr<IMsvThreadPool>& spThreadPool) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvThreading::GetUniqueWorker(std::shared_ptr<IMsvUniqueWorker>& spUniqueWorker, std::shared_ptr<std::condition_variable> spConditionVariable = nullptr, std::shared_ptr<std::mutex> spConditionVariableMutex = nullptr, std::shared_ptr<uint64_t> spConditionVariablePredicate = nullptr) const
	******************************************************************************************************/
	virtual MsvErrorCode GetUniqueWorker(std::shared_ptr<IMsvUniqueWorker>& spUniqueWorker, std::shared_ptr<std::condition_variable> spConditionVariable = nullptr, std::shared_ptr<std::mutex> spConditionVariableMutex = nullptr, std::shared_ptr<uint64_t> spConditionVariablePredicate = nullptr) const override;

	/**************************************************************************************************//**
	* @copydoc IMsvThreading::GetWorker(std::shared_ptr<IMsvWorker>& spWorker, std::shared_ptr<std::condition_variable> spConditionVariable = nullptr, std::shared_ptr<std::mutex> spConditionVariableMutex = nullptr, std::shared_ptr<uint64_t> spConditionVariablePredicate = nullptr) const
	******************************************************************************************************/
	virtual MsvErrorCode GetWorker(std::shared_ptr<IMsvWorker>& spWorker, std::shared_ptr<std::condition_variable> spConditionVariable = nullptr, std::shared_ptr<std::mutex> spConditionVariableMutex = nullptr, std::shared_ptr<uint64_t> spConditionVariablePredicate = nullptr) const override;

protected:
	/**************************************************************************************************//**
	* @brief		Thread mutex.
	* @details	Locks this object for thread safety access.
	******************************************************************************************************/
	mutable std::recursive_mutex m_lock;

	/**************************************************************************************************//**
	* @brief		Shared thread pool.
	* @details	It is returned by @ref GetSharedThreadPool.
	******************************************************************************************************/
	mutable std::shared_ptr<IMsvThreadPool> m_spSharedThreadPool;
};



#endif // !MARSTECH_THREADING_H

/** @} */	//End of group MSYS.
