
#include "pch.h"

#include "msys/msys_lib/MsvSys.h"

#include "merror/MsvErrorCodes.h"


using namespace ::testing;


class MsvThreading_Integration:
	public MsvSys_IntegrationBase
{
public:
	MsvThreading_Integration()
	{

	}

	virtual void SetUp()
	{
		InitializeSys();

		EXPECT_EQ(m_spSys->GetMsvThreading(m_spThreading), MSV_SUCCESS);
		EXPECT_TRUE(m_spThreading != nullptr);
	}

	virtual void TearDown()
	{
		m_spThreading.reset();
		
		UninitializeSys();
	}

	//tested functions and classes
	std::shared_ptr<IMsvThreading> m_spThreading;
};


TEST_F(MsvThreading_Integration, ItShouldCreateTwoEventInterface)
{
	std::shared_ptr<IMsvEvent> spEvent1;
	EXPECT_EQ(m_spThreading->GetEvent(spEvent1), MSV_SUCCESS);
	EXPECT_TRUE(spEvent1 != nullptr);

	std::shared_ptr<IMsvEvent> spEvent2;
	EXPECT_EQ(m_spThreading->GetEvent(spEvent2), MSV_SUCCESS);
	EXPECT_TRUE(spEvent2 != nullptr);

	EXPECT_TRUE(spEvent1 != spEvent2);
}

TEST_F(MsvThreading_Integration, ItShouldCreateOneThreadPoolInterface)
{
	std::shared_ptr<IMsvThreadPool> spThreadPool1;
	EXPECT_EQ(m_spThreading->GetSharedThreadPool(spThreadPool1), MSV_SUCCESS);
	EXPECT_TRUE(spThreadPool1 != nullptr);

	std::shared_ptr<IMsvThreadPool> spThreadPool2;
	EXPECT_EQ(m_spThreading->GetSharedThreadPool(spThreadPool2), MSV_SUCCESS);
	EXPECT_TRUE(spThreadPool2 != nullptr);

	EXPECT_TRUE(spThreadPool1 == spThreadPool2);
}

TEST_F(MsvThreading_Integration, ItShouldCreateTwoThreadPoolInterface)
{
	std::shared_ptr<IMsvThreadPool> spThreadPool1;
	EXPECT_EQ(m_spThreading->GetThreadPool(spThreadPool1), MSV_SUCCESS);
	EXPECT_TRUE(spThreadPool1 != nullptr);

	std::shared_ptr<IMsvThreadPool> spThreadPool2;
	EXPECT_EQ(m_spThreading->GetThreadPool(spThreadPool2), MSV_SUCCESS);
	EXPECT_TRUE(spThreadPool2 != nullptr);

	EXPECT_TRUE(spThreadPool1 != spThreadPool2);
}

TEST_F(MsvThreading_Integration, ItShouldCreateTwoUniqueWorkerInterface)
{
	std::shared_ptr<IMsvUniqueWorker> spUniqueWorker1;
	EXPECT_EQ(m_spThreading->GetUniqueWorker(spUniqueWorker1), MSV_SUCCESS);
	EXPECT_TRUE(spUniqueWorker1 != nullptr);

	std::shared_ptr<IMsvUniqueWorker> spUniqueWorker2;
	EXPECT_EQ(m_spThreading->GetUniqueWorker(spUniqueWorker2), MSV_SUCCESS);
	EXPECT_TRUE(spUniqueWorker2 != nullptr);

	EXPECT_TRUE(spUniqueWorker1 != spUniqueWorker2);
}

TEST_F(MsvThreading_Integration, ItShouldCreateTwoWorkerInterface)
{
	std::shared_ptr<IMsvWorker> spWorker1;
	EXPECT_EQ(m_spThreading->GetWorker(spWorker1), MSV_SUCCESS);
	EXPECT_TRUE(spWorker1 != nullptr);

	std::shared_ptr<IMsvWorker> spWorker2;
	EXPECT_EQ(m_spThreading->GetWorker(spWorker2), MSV_SUCCESS);
	EXPECT_TRUE(spWorker2 != nullptr);

	EXPECT_TRUE(spWorker1 != spWorker2);
}
