

#ifndef MARSTECH_SYS_LOGGING_MOCK_H
#define MARSTECH_SYS_LOGGING_MOCK_H


#include "..\IMsvLogging.h"

MSV_DISABLE_ALL_WARNINGS

#include <gmock\gmock.h>

MSV_ENABLE_WARNINGS


class MsvLogging_Mock:
	public IMsvLogging
{
public:
	MOCK_CONST_METHOD2(GetLogger, MsvErrorCode(std::shared_ptr<MsvLogger>& spLogger, const char* loggerName = "MsvLogger"));
	MOCK_CONST_METHOD2(GetLogger, MsvErrorCode(std::shared_ptr<MsvLogger>& spLogger, const char* loggerName, const char* logFile, int maxLogFileSize, int maxLogFiles));
	MOCK_CONST_METHOD5(GetLoggerProvider, MsvErrorCode(std::shared_ptr<IMsvLoggerProvider>& spLoggerProvider, const char* logFolder = "", const char* logFile = "msvlog.txt", int maxLogFileSize = 10485760, int maxLogFiles = 3));
};


#endif // MARSTECH_SYS_LOGGING_MOCK_H
