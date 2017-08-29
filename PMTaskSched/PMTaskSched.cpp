// PMTaskSched.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//-----------------------------------------------------------
// Use COM to create a task using the Windows task scheduler
//
// Pat Mancuso - 8/25/2017
//
//-----------------------------------------------------------

#define _WIN32_DCOM

#include <windows.h>

#include <iostream>
#include <string>
using namespace std;

#include <atlstr.h>
#include "TaskSched.h"

#ifdef UNITTEST

unsigned guPass = 0;
unsigned guFail = 0;
unsigned guTotal = 0;

void TestCase(unsigned uCaseNum)
{
	TaskSched theTS;
	HRESULT hrResult;
	unsigned uOrigin;

	theTS.injectError(uCaseNum);

	hrResult = theTS.init();
	if (!FAILED(hrResult))
	{
		hrResult = theTS.CreateTask("executable", "args", "taskname", 1);
	}

	uOrigin = theTS.getFailOrigin();

	// Verify that the failure was reported at the expected location

	if (uCaseNum == uOrigin)
	{
		guPass++;
		cout << "Case " << uCaseNum << " PASS\n";
	}
	else
	{
		guFail++;
		cout << "Case " << uCaseNum << " FAIL - returned " << uOrigin << "\n";
	}

	guTotal++;

}


// Test driver
// Exercise all of the functions and introduce a fail at each one in the program

int main(void)
{

	cout << "Running unit tests:\n";

	TestCase(TaskSched::FAIL_StartCom);
	TestCase(TaskSched::FAIL_CoCreate);
	TestCase(TaskSched::FAIL_CoInitSecurity);
	TestCase(TaskSched::FAIL_InvalidObject);
	TestCase(TaskSched::FAIL_Connect);
	TestCase(TaskSched::FAIL_GetFolder);
	TestCase(TaskSched::FAIL_DeleteTask);
	TestCase(TaskSched::FAIL_NewTask);
	TestCase(TaskSched::FAIL_GetRegistrationInfo);
	TestCase(TaskSched::FAIL_PutAuthor);
	TestCase(TaskSched::FAIL_GetPrincipal);
	TestCase(TaskSched::FAIL_PutLogonType);
	TestCase(TaskSched::FAIL_GetSettings);
	TestCase(TaskSched::FAIL_PutStartWhenAvailable);
	TestCase(TaskSched::FAIL_PutId);
	TestCase(TaskSched::FAIL_PutStartBoundary);
	TestCase(TaskSched::FAIL_PutEndBoundary);
	TestCase(TaskSched::FAIL_GetIdleSettings);
	TestCase(TaskSched::FAIL_PutWaitTimeout);
	TestCase(TaskSched::FAIL_CreateTrigger);
	TestCase(TaskSched::FAIL_QueryInterfaceTT);
	TestCase(TaskSched::FAIL_GetTriggers);
	TestCase(TaskSched::FAIL_GetActions);
	TestCase(TaskSched::FAIL_CreateAction);
	TestCase(TaskSched::FAIL_QueryInterfaceEA);
	TestCase(TaskSched::FAIL_PutArguments);
	TestCase(TaskSched::FAIL_PutPath);
	TestCase(TaskSched::FAIL_RegisterTask);
	TestCase(TaskSched::FAIL_NoError);

	cout << "Total tests: " << guTotal << " Pass: " << guPass << " Fail: " << guFail << "\n";
	return guFail;
}

#else


// Main program - 
// Hardcoded values for args to demo the functionality
int main(void)
{
	HRESULT hrResult = E_FAIL;
	TaskSched theTS;

	theTS.init();

	if (theTS.IsValid() == true)
		hrResult = theTS.CreateTask("c:\\windows\\system32\\msg.exe", "* \"Hire Pat!\"", "PMTask", 10);

	if (FAILED(hrResult))
	{
		cout << "TaskSched failed\n";
		cout << "Location: " << theTS.getFailOrigin();
		return -1;
	}
	else
	{
		cout << "Task has been scheduled\n";
	}

	return hrResult;
}

#endif
