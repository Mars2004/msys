

#ifndef MARSTECH_SYS_THREADING_MOCK_H
#define MARSTECH_SYS_THREADING_MOCK_H


#include "..\IMsvThreading.h"

MSV_DISABLE_ALL_WARNINGS

#include <gmock\gmock.h>

MSV_ENABLE_WARNINGS


class MsvThreading_Mock:
	public IMsvThreading
{
public:
	MOCK_CONST_METHOD1(GetEvent, MsvErrorCode(std::shared_ptr<IMsvEvent>& spEvent));
	MOCK_CONST_METHOD1(GetSharedThreadPool, MsvErrorCode(std::shared_ptr<IMsvThreadPool>& spThreadPool));
	MOCK_CONST_METHOD1(GetThreadPool, MsvErrorCode(std::shared_ptr<IMsvThreadPool>& spThreadPool));
	MOCK_CONST_METHOD4(GetUniqueWorker, MsvErrorCode(std::shared_ptr<IMsvUniqueWorker>& spUniqueWorker, std::shared_ptr<std::condition_variable> spConditionVariable = nullptr, std::shared_ptr<std::mutex> spConditionVariableMutex = nullptr, std::shared_ptr<uint64_t> spConditionVariablePredicate = nullptr));
	MOCK_CONST_METHOD4(GetWorker, MsvErrorCode(std::shared_ptr<IMsvWorker>& spWorker, std::shared_ptr<std::condition_variable> spConditionVariable = nullptr, std::shared_ptr<std::mutex> spConditionVariableMutex = nullptr, std::shared_ptr<uint64_t> spConditionVariablePredicate = nullptr));
};


#endif // MARSTECH_SYS_THREADING_MOCK_H
