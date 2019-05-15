/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Threading Interface
* @details		Contains definition of @ref IMsvThreading interface.
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


#ifndef MARSTECH_ITHREADING_H
#define MARSTECH_ITHREADING_H


#include "mthreading/IMsvEvent.h"
#include "mthreading/IMsvThreadPool.h"
#include "mthreading/IMsvUniqueWorker.h"
#include "mthreading/IMsvWorker.h"

MSV_DISABLE_ALL_WARNINGS

#include <mutex>

MSV_ENABLE_WARNINGS


/**************************************************************************************************//**
* @brief		MarsTech Threading Interface.
* @details	Threading interface for easy access to threading interfaces and its implementations.
******************************************************************************************************/
class IMsvThreading
{
public:
	/**************************************************************************************************//**
	* @brief		Virtual destructor.
	******************************************************************************************************/
	virtual ~IMsvThreading() {}	

	/**************************************************************************************************//**
	* @brief			Get event interface.
	* @details		Returns event interface for thread synchronization.
	* @param[out]	spEvent							Shared pointer to event interface @ref IMsvEvent.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @see			IMsvEvent
	******************************************************************************************************/
	virtual MsvErrorCode GetEvent(std::shared_ptr<IMsvEvent>& spEvent) const = 0;

	/**************************************************************************************************//**
	* @brief			Get shared thread pool interface.
	* @details		Returns shared thread pool interface for asynchronous tasks.
	*					Each call of this method returns same interface (same shared pointer).
	* @param[out]	spThreadPool					Shared pointer to thread pool interface @ref IMsvThreadPool.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @note			When @ref IMsvThreading is singleton, shared thread pool interface is singleton too.
	* @warning		It might be good practice to get and initialize this interface in main function or class
	*					and just use in all other classes/objects/functions.
	* @see			IMsvThreadPool
	******************************************************************************************************/
	virtual MsvErrorCode GetSharedThreadPool(std::shared_ptr<IMsvThreadPool>& spThreadPool) const = 0;

	/**************************************************************************************************//**
	* @brief			Get thread pool interface.
	* @details		Returns thread pool interface for asynchronous tasks. It might be usefull when independent
	*					thread pool is needed.
	* @param[out]	spThreadPool					Shared pointer to thread pool interface @ref IMsvThreadPool.
	* @retval		MSV_ALLOCATION_ERROR			When memory allocation failed.
	* @retval		MSV_SUCCESS						On success.
	* @note			Use it when you need your own independent thread pool.
	* @see			IMsvThreadPool
	******************************************************************************************************/
	virtual MsvErrorCode GetThreadPool(std::shared_ptr<IMsvThreadPool>& spThreadPool) const = 0;

	/**************************************************************************************************//**
	* @brief			Get unique worker interface.
	* @details		Returns unique worker interface for asynchronous tasks. It is thread which executes
	*					one task. It might be usefull for threads which read data from queue and process them.
	*					See implementation @ref IMsvThreadPool for usage example.
	* @param[out]	spUniqueWorker						Shared pointer to unique worker interface @ref IMsvUniqueWorker.
	* @param[in]	spConditionVariable				Shared condition variable.
	* @param[in]	spConditionVariableMutex		Shared condition variable mutex.
	* @param[in]	spConditionVariablePredicate	Shared condition variable predicate.
	* @retval		MSV_ALLOCATION_ERROR				When memory allocation failed.
	* @retval		MSV_SUCCESS							On success.
	* @note			In parameters are required when more unique workers process one queue. They are synchronization
	*					objects for unique workers.
	* @note			In parameters might be shared by any thread implementation, but it is not good practice.
	* @see			IMsvUniqueWorker
	******************************************************************************************************/
	virtual MsvErrorCode GetUniqueWorker(std::shared_ptr<IMsvUniqueWorker>& spUniqueWorker, std::shared_ptr<std::condition_variable> spConditionVariable = nullptr, std::shared_ptr<std::mutex> spConditionVariableMutex = nullptr, std::shared_ptr<uint64_t> spConditionVariablePredicate = nullptr) const = 0;

	/**************************************************************************************************//**
	* @brief			Get worker interface.
	* @details		Returns worker interface for asynchronous tasks. It is thread which executes
	*					pushed tasks. When task is executed, it is removed from queue.
	* @param[out]	spWorker								Shared pointer to worker interface @ref IMsvWorker.
	* @param[in]	spConditionVariable				Shared condition variable.
	* @param[in]	spConditionVariableMutex		Shared condition variable mutex.
	* @param[in]	spConditionVariablePredicate	Shared condition variable predicate.
	* @retval		MSV_ALLOCATION_ERROR				When memory allocation failed.
	* @retval		MSV_SUCCESS							On success.
	* @note			In parameters are required when more workers synchronization is needed. They are synchronization
	*					objects for unique workers.
	* @note			In parameters might be shared by any thread implementation, but it is not good practice.
	* @see			IMsvWorker
	******************************************************************************************************/
	virtual MsvErrorCode GetWorker(std::shared_ptr<IMsvWorker>& spWorker, std::shared_ptr<std::condition_variable> spConditionVariable = nullptr, std::shared_ptr<std::mutex> spConditionVariableMutex = nullptr, std::shared_ptr<uint64_t> spConditionVariablePredicate = nullptr) const = 0;
};



#endif // !MARSTECH_ITHREADING_H

/** @} */	//End of group MSYS.
