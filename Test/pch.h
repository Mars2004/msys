//
// pch.h
// Header for standard system include files.
//

#pragma once


#include "msys/msys/MsvSysDll_Interface.h"

#include "mdllfactory/MsvDllFactory.h"
#include "mdllfactory/MsvDllList.h"
#include "merror/MsvErrorCodes.h"
#include "mlogging/MsvSpdLogLoggerProvider.h"

MSV_DISABLE_ALL_WARNINGS

#include "gtest/gtest.h"

MSV_ENABLE_WARNINGS


#ifndef MSV_TEST_WITH_LOGGING
#define MSV_TEST_WITH_LOGGING 0
#endif


class MsvSys_IntegrationBase:
	public::testing::Test
{
public:
	MsvSys_IntegrationBase()
	{

	}

	virtual void InitializeSys()
	{
#if defined(MSV_TEST_WITH_LOGGING) && MSV_TEST_WITH_LOGGING != 0
		m_spLoggerProvider.reset(new (std::nothrow) MsvLoggerProvider());
#else
		m_spLoggerProvider.reset(new (std::nothrow) MsvNullLoggerProvider());
#endif
		EXPECT_NE(m_spLoggerProvider, nullptr);
		m_spLogger = m_spLoggerProvider->GetLogger();
		EXPECT_NE(m_spLogger, nullptr);

		//prepare DLL list for factory
		std::shared_ptr<MsvDllList> spDllList(new (std::nothrow) MsvDllList(m_spLogger));
		EXPECT_TRUE(spDllList != nullptr);
		EXPECT_EQ(spDllList->AddDll(MSV_SYS_OBJECT_ID_LAST, "msys.dll"), MSV_SUCCESS);

		//initialize DLL factory
		m_spDllFactory.reset(new (std::nothrow) MsvDllFactory(spDllList, m_spLogger));
		EXPECT_TRUE(m_spDllFactory != nullptr);

		//get DLL object IMsvSys from msys.dll
		EXPECT_EQ(m_spDllFactory->GetDllObject<IMsvSys>(MSV_SYS_OBJECT_ID_LAST, m_spSys), MSV_SUCCESS);
		EXPECT_TRUE(m_spSys != nullptr);
	}

	virtual void UninitializeSys()
	{
		m_spSys.reset();
		m_spDllFactory.reset();
		m_spLogger.reset();
		m_spLoggerProvider.reset();
	}

	//logger
	std::shared_ptr<IMsvLoggerProvider> m_spLoggerProvider;
	std::shared_ptr<MsvLogger> m_spLogger;

	//tested functions and classes
	std::shared_ptr<IMsvDllFactory> m_spDllFactory;
	std::shared_ptr<IMsvSys> m_spSys;
};
