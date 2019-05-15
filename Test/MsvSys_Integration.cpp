
#include "pch.h"


using namespace ::testing;


class MsvSys_Integration:
	public MsvSys_IntegrationBase
{
public:
	MsvSys_Integration()
	{

	}

	virtual void SetUp()
	{
		InitializeSys();
	}

	virtual void TearDown()
	{
		UninitializeSys();
	}
};


TEST_F(MsvSys_Integration, ItShouldCreateOneConfigurationInterface)
{
	std::shared_ptr<IMsvConfiguration> spConfiguration1;
	EXPECT_EQ(m_spSys->GetMsvConfiguration(spConfiguration1), MSV_SUCCESS);
	EXPECT_TRUE(spConfiguration1 != nullptr);

	std::shared_ptr<IMsvConfiguration> spConfiguration2;
	EXPECT_EQ(m_spSys->GetMsvConfiguration(spConfiguration2), MSV_SUCCESS);
	EXPECT_TRUE(spConfiguration2 != nullptr);

	EXPECT_TRUE(spConfiguration1 == spConfiguration2);
}

TEST_F(MsvSys_Integration, ItShouldCreateOneLoggingInterface)
{
	std::shared_ptr<IMsvLogging> spLogging1;
	EXPECT_EQ(m_spSys->GetMsvLogging(spLogging1), MSV_SUCCESS);
	EXPECT_TRUE(spLogging1 != nullptr);

	std::shared_ptr<IMsvLogging> spLogging2;
	EXPECT_EQ(m_spSys->GetMsvLogging(spLogging2), MSV_SUCCESS);
	EXPECT_TRUE(spLogging2 != nullptr);

	EXPECT_TRUE(spLogging2 == spLogging2);
}

TEST_F(MsvSys_Integration, ItShouldCreateOneThreadingInterface)
{
	std::shared_ptr<IMsvThreading> spThreading1;
	EXPECT_EQ(m_spSys->GetMsvThreading(spThreading1), MSV_SUCCESS);
	EXPECT_TRUE(spThreading1 != nullptr);

	std::shared_ptr<IMsvThreading> spThreading2;
	EXPECT_EQ(m_spSys->GetMsvThreading(spThreading2), MSV_SUCCESS);
	EXPECT_TRUE(spThreading2 != nullptr);

	EXPECT_TRUE(spThreading1 == spThreading2);
}
