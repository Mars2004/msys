
#include "pch.h"

#include "msys/msys_lib/MsvSys.h"

#include "merror/MsvErrorCodes.h"


using namespace ::testing;


class MsvConfiguration_Integration:
	public MsvSys_IntegrationBase
{
public:
	MsvConfiguration_Integration()
	{

	}

	virtual void SetUp()
	{
		InitializeSys();

		EXPECT_EQ(m_spSys->GetMsvConfiguration(m_spConfiguration), MSV_SUCCESS);
		EXPECT_TRUE(m_spConfiguration != nullptr);
	}

	virtual void TearDown()
	{
		m_spConfiguration.reset();
		
		UninitializeSys();
	}

	//tested functions and classes
	std::shared_ptr<IMsvConfiguration> m_spConfiguration;
};


TEST_F(MsvConfiguration_Integration, ItShouldCreateOneActiveConfigInterface)
{
	std::shared_ptr<IMsvActiveConfig> spActiveConfig1;
	EXPECT_EQ(m_spConfiguration->GetSharedActiveConfigSQLite(spActiveConfig1), MSV_SUCCESS);
	EXPECT_TRUE(spActiveConfig1 != nullptr);

	std::shared_ptr<IMsvActiveConfig> spActiveConfig2;
	EXPECT_EQ(m_spConfiguration->GetSharedActiveConfigSQLite(spActiveConfig2), MSV_SUCCESS);
	EXPECT_TRUE(spActiveConfig2 != nullptr);

	EXPECT_TRUE(spActiveConfig1 == spActiveConfig2);
}

TEST_F(MsvConfiguration_Integration, ItShouldCreateTwoActiveConfigInterface)
{
	std::shared_ptr<IMsvActiveConfig> spActiveConfig1;
	EXPECT_EQ(m_spConfiguration->GetActiveConfigSQLite(spActiveConfig1), MSV_SUCCESS);
	EXPECT_TRUE(spActiveConfig1 != nullptr);

	std::shared_ptr<IMsvActiveConfig> spActiveConfig2;
	EXPECT_EQ(m_spConfiguration->GetActiveConfigSQLite(spActiveConfig2), MSV_SUCCESS);
	EXPECT_TRUE(spActiveConfig2 != nullptr);

	EXPECT_TRUE(spActiveConfig1 != spActiveConfig2);
}

TEST_F(MsvConfiguration_Integration, ItShouldCreateOnePassiveConfigInterface)
{
	std::shared_ptr<IMsvPassiveConfig> spPassiveConfig1;
	EXPECT_EQ(m_spConfiguration->GetSharedPassiveConfigIniFile(spPassiveConfig1), MSV_SUCCESS);
	EXPECT_TRUE(spPassiveConfig1 != nullptr);

	std::shared_ptr<IMsvPassiveConfig> spPassiveConfig2;
	EXPECT_EQ(m_spConfiguration->GetSharedPassiveConfigIniFile(spPassiveConfig2), MSV_SUCCESS);
	EXPECT_TRUE(spPassiveConfig2 != nullptr);

	EXPECT_TRUE(spPassiveConfig1 == spPassiveConfig2);
}

TEST_F(MsvConfiguration_Integration, ItShouldCreateTwoPassiveConfigInterface)
{
	std::shared_ptr<IMsvPassiveConfig> spPassiveConfig1;
	EXPECT_EQ(m_spConfiguration->GetPassiveConfigIniFile(spPassiveConfig1), MSV_SUCCESS);
	EXPECT_TRUE(spPassiveConfig1 != nullptr);

	std::shared_ptr<IMsvPassiveConfig> spPassiveConfig2;
	EXPECT_EQ(m_spConfiguration->GetPassiveConfigIniFile(spPassiveConfig2), MSV_SUCCESS);
	EXPECT_TRUE(spPassiveConfig2 != nullptr);

	EXPECT_TRUE(spPassiveConfig1 != spPassiveConfig2);
}

TEST_F(MsvConfiguration_Integration, ItShouldCreateTwoSQLiteInterface)
{
	std::shared_ptr<IMsvSQLite> spSQLite1;
	EXPECT_EQ(m_spConfiguration->GetSQLite(spSQLite1), MSV_SUCCESS);
	EXPECT_TRUE(spSQLite1 != nullptr);

	std::shared_ptr<IMsvSQLite> spSQLite2;
	EXPECT_EQ(m_spConfiguration->GetSQLite(spSQLite2), MSV_SUCCESS);
	EXPECT_TRUE(spSQLite2 != nullptr);

	EXPECT_TRUE(spSQLite1 != spSQLite2);
}
