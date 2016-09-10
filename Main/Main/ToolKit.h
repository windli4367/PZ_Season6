#pragma once

#include "StdAfx.h"

namespace ASM
{
	enum T
	{
		EAX		= 0x50,
		JMP		= 0xE9,
		JMPS	= 0xEB,
		JE		= 0x74,
		JNE		= 0x75,
		JGE		= 0x7D,
		NOP		= 0x90,
		CALL	= 0xE8,
		PUSH	= 0x68,
		RETN	= 0xC3,
	};
};

struct tJMP
{
	BYTE op;
	DWORD Address;
};

class cToolKit
{
	public:
		cToolKit();
		virtual ~cToolKit();

		void SetNop(DWORD dwSrcOffset, int Size);
		void SetByte(DWORD dwSrcOffset, BYTE bOpCode);
		void WriteJmp(DWORD dwSrcOffset, DWORD dwDstOffset);
		void HookThis(DWORD dwDstOffset, DWORD dwSrcOffset);
		void Protect(DWORD dwSrcOffset, int Size, DWORD dwNewProtect);
		DWORD UnProtect(DWORD dwSrcOffset, int Size);
		void UnProtectEx(DWORD *dwpAddress, float pBuffer);
		void HookOffset(DWORD my, DWORD tohook, BYTE type);
		void HookExactOffset(DWORD my, DWORD tohook, BYTE type);
		DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize);
		DWORD ReadMemory(const LPVOID lpAddress, LPVOID lpBuf, const UINT uSize);
		DWORD SetByte(const LPVOID dwOffset, const BYTE btValue);
		DWORD GetByte(const LPVOID dwOffset, BYTE & btValue);
		DWORD SetWord(const LPVOID dwOffset, const WORD wValue);
		DWORD GetWord(const LPVOID dwOffset, WORD & wValue);
		DWORD SetDword(const LPVOID dwOffset, const DWORD dwValue);
		DWORD GetDword(const LPVOID dwOffset, DWORD & dwValue);
		DWORD SetFloat(const LPVOID dwOffset, const float fValue);
		DWORD GetFloat(const LPVOID dwOffset, float & fValue);
		DWORD SetDouble(const LPVOID dwOffset, double dValue);
		DWORD SetJmp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
		DWORD SetJg(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
		DWORD SetJa(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress);
		DWORD SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd);
		DWORD SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue);
		DWORD SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd);
		LPVOID HookFunction(LPVOID origf, LPVOID callbackf, DWORD copylen);
		void Access(DWORD dwOffset, int t_size);
		void HookAddress(DWORD dwAddrOffst, DWORD dwNewOffst, BYTE new_Cmd);
};

extern cToolKit gToolKit;