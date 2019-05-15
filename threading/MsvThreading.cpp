/**************************************************************************************************//**
* @addtogroup	MSYS
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Threading Implementation
* @details		Contains implementation of @ref MsvThreading.
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


#include "MsvThreading.h"

#include "mthreading/MsvEvent.h"
#include "mthreading/MsvThreadPool.h"
#include "mthreading/MsvUniqueWorker.h"
#include "mthreading/MsvWorker.h"

#include "merror/MsvErrorCodes.h"


/********************************************************************************************************************************
*															Constructors and destructors
********************************************************************************************************************************/


MsvThreading::MsvThreading()
{

}


MsvThreading::~MsvThreading()
{
	if (m_spSharedThreadPool)
	{
		//it is called with default timeout (30s)
		m_spSharedThreadPool->StopAndWaitForThreadPoolStop();
	}
}


/********************************************************************************************************************************
*															IMsvThreading public methods
********************************************************************************************************************************/


MsvErrorCode MsvThreading::GetEvent(std::shared_ptr<IMsvEvent>& spEvent) const
{
	std::shared_ptr<IMsvEvent> spTempEvent(new (std::nothrow) MsvEvent());

	if (!spTempEvent)
	{
		return MSV_ALLOCATION_ERROR;
	}

	spEvent = spTempEvent;

	return MSV_SUCCESS;
}

MsvErrorCode MsvThreading::GetSharedThreadPool(std::shared_ptr<IMsvThreadPool>& spThreadPool) const
{
	std::lock_guard<std::recursive_mutex> lock(m_lock);

	if (!m_spSharedThreadPool)
	{
		//if GetThreadPool fails it does not set out shared pointer -> m_spSharedThreadPool is unset when failed
		MSV_RETURN_FAILED(GetThreadPool(m_spSharedThreadPool));
	}

	spThreadPool = m_spSharedThreadPool;

	return MSV_SUCCESS;
}

MsvErrorCode MsvThreading::GetThreadPool(std::shared_ptr<IMsvThreadPool>& spThreadPool) const
{
	std::shared_ptr<IMsvThreadPool> spTempThreadPool(new (std::nothrow) MsvThreadPool());

	if (!spTempThreadPool)
	{
		return MSV_ALLOCATION_ERROR;
	}

	spThreadPool = spTempThreadPool;

	return MSV_SUCCESS;
}

MsvErrorCode MsvThreading::GetUniqueWorker(std::shared_ptr<IMsvUniqueWorker>& spUniqueWorker, std::shared_ptr<std::condition_variable> spConditionVariable, std::shared_ptr<std::mutex> spConditionVariableMutex, std::shared_ptr<uint64_t> spConditionVariablePredicate) const
{
	std::shared_ptr<IMsvUniqueWorker> spTempUniqueWorker(new (std::nothrow) MsvUniqueWorker(spConditionVariable, spConditionVariableMutex, spConditionVariablePredicate));

	if (!spTempUniqueWorker)
	{
		return MSV_ALLOCATION_ERROR;
	}

	spUniqueWorker = spTempUniqueWorker;

	return MSV_SUCCESS;
}

MsvErrorCode MsvThreading::GetWorker(std::shared_ptr<IMsvWorker>& spWorker, std::shared_ptr<std::condition_variable> spConditionVariable, std::shared_ptr<std::mutex> spConditionVariableMutex, std::shared_ptr<uint64_t> spConditionVariablePredicate) const
{
	std::shared_ptr<IMsvWorker> spTempWorker(new (std::nothrow) MsvWorker(spConditionVariable, spConditionVariableMutex, spConditionVariablePredicate));

	if (!spTempWorker)
	{
		return MSV_ALLOCATION_ERROR;
	}

	spWorker = spTempWorker;

	return MSV_SUCCESS;
}


/** @} */	//End of group MSYS.
