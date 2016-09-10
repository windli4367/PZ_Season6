#include "stdafx.h"
#include "Main.h"
#include "Fix.h"

extern "C" _declspec(dllexport) void Init()
{
	// Gracefully nothing
}

int APIENTRY DllMain(HINSTANCE hModule,DWORD dwReason,LPVOID lpReserved)
{
	UNREFERENCED_PARAMETER(lpReserved);

	if(dwReason == DLL_PROCESS_ATTACH)
	{
		gFix.Load();
	}
	else if(dwReason == DLL_PROCESS_DETACH)
	{
		/**/
	}

	return 1;
}