
#include "pch.h"

#include "msys/msys_lib/MsvSys.h"

#include "merror/MsvErrorCodes.h"


using namespace ::testing;


class MsvModules_Integration:
	public MsvSys_IntegrationBase
{
public:
	virtual void SetUp()
	{
		InitializeSys();

		EXPECT_EQ(m_spSys->GetMsvModules(m_spModules), MSV_SUCCESS);
		EXPECT_TRUE(m_spModules != nullptr);
	}

	virtual void TearDown()
	{
		m_spModules.reset();
		
		UninitializeSys();
	}

	//tested functions and classes
	std::shared_ptr<IMsvModules> m_spModules;
};


TEST_F(MsvModules_Integration, ItShouldCreateTwoDllModuleInterfaces)
{
	std::shared_ptr<IMsvModule> spModule1;
	EXPECT_EQ(m_spModules->GetDllModule(spModule1, "{23CD6676-0967-4796-9E08-08722EA19BA9}", m_spDllFactory), MSV_SUCCESS);
	EXPECT_TRUE(spModule1 != nullptr);

	std::shared_ptr<IMsvModule> spModule2;
	EXPECT_EQ(m_spModules->GetDllModule(spModule2, "{23CD6676-0967-4796-9E08-08722EA19BA9}", m_spDllFactory), MSV_SUCCESS);
	EXPECT_TRUE(spModule2 != nullptr);

	EXPECT_TRUE(spModule1 != spModule2);
}

TEST_F(MsvModules_Integration, ItShouldFailedToCreateDllModule_WhenDllFactoryEmpty)
{
	std::shared_ptr<IMsvModule> spModule1;
	EXPECT_EQ(m_spModules->GetDllModule(spModule1, "{23CD6676-0967-4796-9E08-08722EA19BA9}", nullptr), MSV_INVALID_DATA_ERROR);
	EXPECT_TRUE(spModule1 == nullptr);
}

TEST_F(MsvModules_Integration, ItShouldCreateTwoModuleConfiguratorInterfaces)
{
	std::shared_ptr<IMsvConfiguration> spConfiguration;
	EXPECT_EQ(m_spSys->GetMsvConfiguration(spConfiguration), MSV_SUCCESS);
	EXPECT_TRUE(spConfiguration != nullptr);

	std::shared_ptr<IMsvActiveConfig> spActiveConfig;
	EXPECT_EQ(spConfiguration->GetSharedActiveConfigSQLite(spActiveConfig), MSV_SUCCESS);
	EXPECT_TRUE(spActiveConfig != nullptr);

	std::shared_ptr<IMsvModuleConfigurator> spModuleConfigurator1;
	EXPECT_EQ(m_spModules->GetModuleConfigurator(spModuleConfigurator1, spActiveConfig, 0, 1), MSV_SUCCESS);
	EXPECT_TRUE(spModuleConfigurator1 != nullptr);

	std::shared_ptr<IMsvModuleConfigurator> spModuleConfigurator2;
	EXPECT_EQ(m_spModules->GetModuleConfigurator(spModuleConfigurator2, spActiveConfig, 0, 1), MSV_SUCCESS);
	EXPECT_TRUE(spModuleConfigurator2 != nullptr);

	EXPECT_TRUE(spModuleConfigurator1 != spModuleConfigurator2);
}

TEST_F(MsvModules_Integration, ItShouldFailedToCreateModuleConfigurator_WhenConfigEmpty)
{
	std::shared_ptr<IMsvModuleConfigurator> spModuleConfigurator1;
	EXPECT_EQ(m_spModules->GetModuleConfigurator(spModuleConfigurator1, nullptr, 0, 1), MSV_INVALID_DATA_ERROR);
	EXPECT_TRUE(spModuleConfigurator1 == nullptr);
}

TEST_F(MsvModules_Integration, ItShouldCreateTwoModuleManagerInterfaces)
{
	std::shared_ptr<IMsvModuleManager> spModuleManager1;
	EXPECT_EQ(m_spModules->GetModuleManager(spModuleManager1), MSV_SUCCESS);
	EXPECT_TRUE(spModuleManager1 != nullptr);

	std::shared_ptr<IMsvModuleManager> spModuleManager2;
	EXPECT_EQ(m_spModules->GetModuleManager(spModuleManager2), MSV_SUCCESS);
	EXPECT_TRUE(spModuleManager2 != nullptr);

	EXPECT_TRUE(spModuleManager1 != spModuleManager2);
}

TEST_F(MsvModules_Integration, ItShouldCreateOneModuleManagerInterface)
{
	std::shared_ptr<IMsvModuleManager> spModuleManager1;
	EXPECT_EQ(m_spModules->GetSharedModuleManager(spModuleManager1), MSV_SUCCESS);
	EXPECT_TRUE(spModuleManager1 != nullptr);

	std::shared_ptr<IMsvModuleManager> spModuleManager2;
	EXPECT_EQ(m_spModules->GetSharedModuleManager(spModuleManager2), MSV_SUCCESS);
	EXPECT_TRUE(spModuleManager2 != nullptr);

	EXPECT_TRUE(spModuleManager1 == spModuleManager2);
}
