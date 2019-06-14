/**************************************************************************************************//**
* @addtogroup	MSVEXAMPLE
* @{
******************************************************************************************************/

/**************************************************************************************************//**
* @file
* @brief			MarsTech Example Main
* @details		Contains implementation of MarsTech Example @ref main function.
* @author		Martin Svoboda
* @date			26.05.2019
* @copyright	GNU General Public License (GPLv3).
******************************************************************************************************/


/*
This file is part of MarsTech C++ SYS Library.

MarsTech Config is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MarsTech Promise Like Syntax is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar. If not, see <https://www.gnu.org/licenses/>.
*/


#include "MsvMain.h"
#include "MsvMaininitializer.h"
#include "merror/MsvErrorCodes.h"

MSV_DISABLE_ALL_WARNINGS

#include <csignal>

MSV_ENABLE_WARNINGS


/**************************************************************************************************//**
* @brief			Global Main Implementation.
* @details		It is shared pointer to interface of @ref IMsvMain which creates and initializes
*					all objects/classes/data required by a program.
* @see			main
******************************************************************************************************/
std::shared_ptr<IMsvMain> g_spMain;


/**************************************************************************************************//**
* @brief			Signal handler function.
* @details		Handles received signals and executes action for received signal.
* @param[in]	signal					Received signal.
******************************************************************************************************/
void MsvSignalHandler(int signal)
{
	//set signal handlers to default
	std::signal(SIGABRT, SIG_DFL);
	//std::signal(SIGFPE, SIG_DFL);
	//std::signal(SIGILL, SIG_DFL);
	std::signal(SIGINT, SIG_DFL);
	//std::signal(SIGSEGV, SIG_DFL);
	std::signal(SIGTERM, SIG_DFL);

	if (g_spMain && g_spMain->Initialized())
	{
		g_spMain->OnSignal(signal);
	}
}


/**************************************************************************************************//**
* @brief			Main function.
* @details		Program entry point.
* @param[in]	argc						Argument count.
* @param[in]	argv						Arguments vector.
* @retval		other_error_code		When failed.
* @retval		MSV_SUCCESS				On success.
******************************************************************************************************/
int main(int argc, char *argv[])
{
	std::shared_ptr<IMsvMainInitializer> spMainInitializer(new (std::nothrow) MsvMainInitializer());
	if (!spMainInitializer)
	{
		return MSV_ALLOCATION_ERROR;
	}

	g_spMain.reset(new (std::nothrow) MsvMain(argc, argv, spMainInitializer));
	if (!g_spMain)
	{
		return MSV_ALLOCATION_ERROR;
	}

	MSV_RETURN_FAILED(g_spMain->Initialize());

	//logger is initialized in initialize (can not set earlier)
	std::signal(SIGABRT, MsvSignalHandler);
	//std::signal(SIGFPE, MsvSignalHandler);
	//std::signal(SIGILL, MsvSignalHandler);
	std::signal(SIGINT, MsvSignalHandler);
	//std::signal(SIGSEGV, MsvSignalHandler);
	std::signal(SIGTERM, MsvSignalHandler);

	MSV_RETURN_FAILED(g_spMain->Start());

	//just wait (do not check returned error code, stop and unitialize will be executed even if failed)
	g_spMain->WaitForStopRequest();

	MSV_RETURN_FAILED(g_spMain->Stop());
	MSV_RETURN_FAILED(g_spMain->Uninitialize());

	//release MSV MAIN
	g_spMain.reset();

	return MSV_SUCCESS;
}


/** @} */	//End of group MSVEXAMPLE.
