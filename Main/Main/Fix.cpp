#include "stdafx.h"
#include "Fix.h"
#include "Config.h"
#include "ToolKit.h"
#include "Offset.h"

cFix gFix;

cFix::cFix()
{
	/**/
}

DWORD dwAllowTabSwitchLoginJMP = oAllowTabSwithLoginJMP;

void __declspec(naked) cAllowTabSwitchLogin()
{
	_asm
	{
		PUSH 0
		MOV EAX, DWORD PTR SS:[EBP-0x38]
		MOV ECX, DWORD PTR DS:[EAX+0x354]
		MOV EDX, DWORD PTR SS:[EBP-0x38]
		MOV EAX, DWORD PTR DS:[EDX+0x354]
		MOV EDX, DWORD PTR DS:[EAX]
		CALL DWORD PTR DS:[EDX+0x30]
		
		MOV EAX, DWORD PTR SS:[EBP-0x38]
		MOV ECX, DWORD PTR DS:[EAX+0x354]
		PUSH ECX
		MOV EDX, DWORD PTR SS:[EBP-0x38]
		MOV ECX, DWORD PTR DS:[EDX+0x350]
		MOV EAX, DWORD PTR SS:[EBP-0x38]
		MOV EDX, DWORD PTR DS:[EAX+0x350]
		MOV EAX, DWORD PTR DS:[EDX]
		CALL DWORD PTR DS:[EAX+0x58]
		
		MOV ECX, DWORD PTR SS:[EBP-0x38]
		MOV EDX, DWORD PTR DS:[ECX+0x350]
		PUSH EDX
		MOV EAX, DWORD PTR SS:[EBP-0x38]
		MOV ECX, DWORD PTR DS:[EAX+0x354]
		MOV EDX, DWORD PTR SS:[EBP-0x38]
		MOV EAX, DWORD PTR DS:[EDX+0x354]
		MOV EDX, DWORD PTR DS:[EAX]
		CALL DWORD PTR DS:[EDX+0x58]
		
		JMP dwAllowTabSwitchLoginJMP
	}
}

void cFix::Load()
{
	// Main Configs
	gToolKit.SetWord((PVOID)(oMainCSPort),gConfig.CSPort);
	gToolKit.WriteMemory((LPVOID)oMainAddress,gConfig.IP,sizeof(gConfig.IP));
	gToolKit.WriteMemory((LPVOID)oMainVersion,gConfig.Version,sizeof(gConfig.Version));
	gToolKit.WriteMemory((LPVOID)oMainSerial,gConfig.Serial,sizeof(gConfig.Serial)); 

	// MU Window Title Name
	gToolKit.SetDword((PVOID)(oMainWinTitle),(DWORD)gConfig.Title);

	// Disable CMStarter
	gToolKit.SetWord((PVOID)(oCMStarter1+2),0x350);	
	gToolKit.SetWord((PVOID)(oCMStarter2+2),0x350);
	gToolKit.SetByte((PVOID)(oCMStarter3+2),0x18);

	gToolKit.SetByte((PVOID)oMUExeCall,ASM::JMPS);		// Disable MU.exe call
	gToolKit.SetByte((PVOID)oConfigIni,ASM::JMPS);		// Disable Config.ini
	gToolKit.SetByte((PVOID)oWebCheck,ASM::JMPS);		// Disable web check
	gToolKit.SetByte((PVOID)(oAccountField+1),0x00);	// Enable account field

	// Disable ResourceGuard Call
	gToolKit.SetRange((PVOID)oResGuardCall1,5,ASM::NOP);
	gToolKit.SetRange((PVOID)oResGuardCall2,5,ASM::NOP);
	gToolKit.SetRange((PVOID)oResGuardCall3,5,ASM::NOP);
	gToolKit.SetRange((PVOID)oResGuardCall4,5,ASM::NOP);	

	// ResourceGuard Jumps
	gToolKit.SetByte((PVOID)oResGuardJmps1,ASM::JMPS);
	gToolKit.SetByte((PVOID)oResGuardJmps2,ASM::JMPS);
	gToolKit.SetByte((PVOID)oResGuardJmps3,ASM::JMPS);
	gToolKit.SetByte((PVOID)oResGuardJmps4,ASM::JMPS);

	// Bypass in terrains files
	gToolKit.SetByte((PVOID)oTerrainPass1,ASM::JMPS);
	gToolKit.SetByte((PVOID)oTerrainPass2,ASM::JMPS);
	gToolKit.SetByte((PVOID)oTerrainPass3,ASM::JMPS);
	gToolKit.SetByte((PVOID)oTerrainPass4,ASM::JMPS);
	gToolKit.SetByte((PVOID)oTerrainPass5,ASM::JMPS);
	gToolKit.SetByte((PVOID)oTerrainPass6,ASM::JMPS);

	// Increase terrains amount to 105
	gToolKit.SetByte((PVOID)oTerrainNum1,0x69);
	gToolKit.SetByte((PVOID)oTerrainNum2,0x69);
	gToolKit.SetByte((PVOID)oTerrainNum3,0x69);

	// Bypass in Local folder text .bmd files
	gToolKit.SetByte((PVOID)oTextBmdLocalPass,ASM::JMPS);

	// Fix TAB key on login screen
	gToolKit.SetRange((LPVOID)oFixTabKeyLogin,5,ASM::NOP);
	gToolKit.SetOp((LPVOID)oFixTabKeyLogin,cAllowTabSwitchLogin,ASM::JMP);
}