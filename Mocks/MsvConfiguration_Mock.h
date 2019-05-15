

#ifndef MARSTECH_SYS_CONFIGURATION_MOCK_H
#define MARSTECH_SYS_CONFIGURATION_MOCK_H


#include "..\IMsvConfiguration.h"

MSV_DISABLE_ALL_WARNINGS

#include <gmock\gmock.h>

MSV_ENABLE_WARNINGS


class MsvConfiguration_Mock:
	public IMsvConfiguration
{
public:
	MOCK_CONST_METHOD2(GetActiveConfigSQLite(std::shared_ptr<IMsvActiveConfig>& spActiveConfig, std::shared_ptr<MsvLogger> spLogger = nullptr));
	MOCK_CONST_METHOD1(GetPassiveConfigIniFile(std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig));
	MOCK_CONST_METHOD2(GetSharedActiveConfigSQLite(std::shared_ptr<IMsvActiveConfig>& spActiveConfig, std::shared_ptr<MsvLogger> spLogger = nullptr));
	MOCK_CONST_METHOD1(GetSharedPassiveConfigIniFile(std::shared_ptr<IMsvPassiveConfig>& spPassiveConfig));
	MOCK_CONST_METHOD2(GetSQLite(std::shared_ptr<IMsvSQLite>& spSQLite, std::shared_ptr<MsvLogger> spLogger = nullptr));
};


#endif // MARSTECH_SYS_CONFIGURATION_MOCK_H
