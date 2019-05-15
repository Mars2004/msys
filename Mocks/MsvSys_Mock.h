

#ifndef MARSTECH_SYS_MOCK_H
#define MARSTECH_SYS_MOCK_H


#include "..\IMsvSys.h"

MSV_DISABLE_ALL_WARNINGS

#include <gmock\gmock.h>

MSV_ENABLE_WARNINGS


class MsvSys_Mock:
	public IMsvSys
{
public:
	MOCK_CONST_METHOD1(GetMsvConfiguration, MsvErrorCode(std::shared_ptr<IMsvConfiguration>& spConfiguration));
	MOCK_CONST_METHOD1(GetMsvLogging, MsvErrorCode(std::shared_ptr<IMsvLogging>& spLogging));
	MOCK_CONST_METHOD1(GetMsvThreading, MsvErrorCode(std::shared_ptr<IMsvThreading>& spThreading));
};


#endif // MARSTECH_SYS_MOCK_H
