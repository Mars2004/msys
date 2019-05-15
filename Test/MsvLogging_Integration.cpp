
#include "pch.h"

#include "msys/msys_lib/MsvSys.h"

#include "merror/MsvErrorCodes.h"


using namespace ::testing;


class MsvLogging_Integration:
	public MsvSys_IntegrationBase
{
public:
	MsvLogging_Integration()
	{

	}

	virtual void SetUp()
	{
		InitializeSys();

		EXPECT_EQ(m_spSys->GetMsvLogging(m_spLogging), MSV_SUCCESS);
		EXPECT_TRUE(m_spLogging != nullptr);
	}

	virtual void TearDown()
	{
		m_spLogging.reset();
		
		UninitializeSys();
	}

	//tested functions and classes
	std::shared_ptr<IMsvLogging> m_spLogging;
};


TEST_F(MsvLogging_Integration, ItShouldCreateOneLoggerProviderInterface)
{
	std::shared_ptr<IMsvLoggerProvider> spLoggerProvider1;
	EXPECT_EQ(m_spLogging->GetLoggerProvider(spLoggerProvider1), MSV_SUCCESS);
	EXPECT_TRUE(spLoggerProvider1 != nullptr);

	std::shared_ptr<IMsvLoggerProvider> spLoggerProvider2;
	EXPECT_EQ(m_spLogging->GetLoggerProvider(spLoggerProvider2), MSV_SUCCESS);
	EXPECT_TRUE(spLoggerProvider2 != nullptr);

	EXPECT_TRUE(spLoggerProvider1 == spLoggerProvider2);
}

TEST_F(MsvLogging_Integration, ItShouldFailedToGetLoggerWithoutProvider)
{
	std::shared_ptr<MsvLogger> spLogger1;
	EXPECT_EQ(m_spLogging->GetLogger(spLogger1), MSV_NOT_INITIALIZED_ERROR);
	EXPECT_TRUE(spLogger1 == nullptr);
}

TEST_F(MsvLogging_Integration, ItShouldCreateOneLogger)
{
	std::shared_ptr<IMsvLoggerProvider> spLoggerProvider1;
	EXPECT_EQ(m_spLogging->GetLoggerProvider(spLoggerProvider1), MSV_SUCCESS);
	EXPECT_TRUE(spLoggerProvider1 != nullptr);

	std::shared_ptr<MsvLogger> spLogger1;
	EXPECT_EQ(m_spLogging->GetLogger(spLogger1), MSV_SUCCESS);
	EXPECT_TRUE(spLogger1 != nullptr);

	std::shared_ptr<MsvLogger> spLogger2;
	EXPECT_EQ(m_spLogging->GetLogger(spLogger2), MSV_SUCCESS);
	EXPECT_TRUE(spLogger2 != nullptr);

	EXPECT_TRUE(spLogger1 == spLogger2);
}

TEST_F(MsvLogging_Integration, ItShouldCreateTwoLoggers)
{
	std::shared_ptr<IMsvLoggerProvider> spLoggerProvider1;
	EXPECT_EQ(m_spLogging->GetLoggerProvider(spLoggerProvider1), MSV_SUCCESS);
	EXPECT_TRUE(spLoggerProvider1 != nullptr);

	std::shared_ptr<MsvLogger> spLogger1;
	EXPECT_EQ(m_spLogging->GetLogger(spLogger1, "Logger_1"), MSV_SUCCESS);
	EXPECT_TRUE(spLogger1 != nullptr);

	std::shared_ptr<MsvLogger> spLogger2;
	EXPECT_EQ(m_spLogging->GetLogger(spLogger2, "Logger_2"), MSV_SUCCESS);
	EXPECT_TRUE(spLogger2 != nullptr);

	EXPECT_TRUE(spLogger1 != spLogger2);
}

TEST_F(MsvLogging_Integration, ItShouldFailedToGetLoggerParamsWithoutProvider)
{
	std::shared_ptr<MsvLogger> spLogger1;
	EXPECT_EQ(m_spLogging->GetLogger(spLogger1, "Logger", "log.txt", 10240, 10), MSV_NOT_INITIALIZED_ERROR);
	EXPECT_TRUE(spLogger1 == nullptr);
}

TEST_F(MsvLogging_Integration, ItShouldCreateOneLoggerParams)
{
	std::shared_ptr<IMsvLoggerProvider> spLoggerProvider1;
	EXPECT_EQ(m_spLogging->GetLoggerProvider(spLoggerProvider1), MSV_SUCCESS);
	EXPECT_TRUE(spLoggerProvider1 != nullptr);

	std::shared_ptr<MsvLogger> spLogger1;
	EXPECT_EQ(m_spLogging->GetLogger(spLogger1, "Logger", "log.txt", 10240, 10), MSV_SUCCESS);
	EXPECT_TRUE(spLogger1 != nullptr);

	std::shared_ptr<MsvLogger> spLogger2;
	EXPECT_EQ(m_spLogging->GetLogger(spLogger2, "Logger", "log.txt", 10240, 10), MSV_SUCCESS);
	EXPECT_TRUE(spLogger2 != nullptr);

	EXPECT_TRUE(spLogger1 == spLogger2);
}

TEST_F(MsvLogging_Integration, ItShouldCreateTwoLoggersParams)
{
	std::shared_ptr<IMsvLoggerProvider> spLoggerProvider1;
	EXPECT_EQ(m_spLogging->GetLoggerProvider(spLoggerProvider1), MSV_SUCCESS);
	EXPECT_TRUE(spLoggerProvider1 != nullptr);

	std::shared_ptr<MsvLogger> spLogger1;
	EXPECT_EQ(m_spLogging->GetLogger(spLogger1, "Logger_1", "log.txt", 10240, 10), MSV_SUCCESS);
	EXPECT_TRUE(spLogger1 != nullptr);

	std::shared_ptr<MsvLogger> spLogger2;
	EXPECT_EQ(m_spLogging->GetLogger(spLogger2, "Logger_2", "log.txt", 10240, 10), MSV_SUCCESS);
	EXPECT_TRUE(spLogger2 != nullptr);

	EXPECT_TRUE(spLogger1 != spLogger2);
}
