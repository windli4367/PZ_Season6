#include "StdAfx.h"
#include "ToolKit.h"

cToolKit gToolKit;

cToolKit::cToolKit()
{
	/**/
};

cToolKit::~cToolKit()
{
	/**/
};

void cToolKit::Protect(DWORD dwSrcOffset, int Size, DWORD dwNewProtect)
{
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)dwSrcOffset, Size, dwNewProtect, &OldProtect);
};

DWORD cToolKit::UnProtect(DWORD dwSrcOffset,int Size)
{
	DWORD OldProtect = 0;
	VirtualProtect((LPVOID)dwSrcOffset, Size, PAGE_EXECUTE_READWRITE, &OldProtect);

	return OldProtect;
};

void cToolKit::UnProtectEx(DWORD *dwpAddress, float pBuffer)
{
	DWORD dwOldProtect = 0;
	HANDLE hWnd = GetCurrentProcess();

	VirtualProtectEx(hWnd, dwpAddress, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	WriteProcessMemory(hWnd, dwpAddress, (void*)&pBuffer, 4, 0);
	VirtualProtectEx(hWnd, dwpAddress, 4, PAGE_EXECUTE_READWRITE, &dwOldProtect);
}

void cToolKit::SetNop(DWORD dwSrcOffset,int Size)
{
	for(int i = 0;i < Size;i++)
	{
		*(BYTE*)(dwSrcOffset + i) = 0x90;
	}
};

void cToolKit::SetByte(DWORD dwSrcOffset, BYTE bOpCode)
{
	__try 
	{
		DWORD dwProtect = this->UnProtect(dwSrcOffset, 1);
		*(BYTE*)(dwSrcOffset) = bOpCode;
		this->Protect(dwSrcOffset, 1, dwProtect);
	}
	__finally
	{
		/**/
	}
}

void cToolKit::WriteJmp(DWORD dwSrcOffset, DWORD dwDstOffset)
{
	if (dwSrcOffset)
	{
		__try
		{
			DWORD dwOffset = UnProtect(dwSrcOffset, 10);
			SetByte(dwSrcOffset, 0xE9);
			HookThis(dwDstOffset, dwSrcOffset);
			Protect(dwSrcOffset, 10, dwOffset);
		}
		__finally
		{
			/**/
		}
	}
}

void cToolKit::HookThis(DWORD dwDstOffset, DWORD dwSrcOffset) 
{
	*(DWORD*)(dwSrcOffset + 1) = dwDstOffset - (dwSrcOffset + 5);
}

void cToolKit::HookOffset(DWORD my,DWORD tohook,BYTE type)
{
	*(BYTE*)tohook = type;
	*(DWORD*)(tohook+1) = my - (tohook+5);
}

void cToolKit::HookExactOffset(DWORD my, DWORD tohook, BYTE type)
{
	*(BYTE*)tohook = type;
	*(DWORD*)(tohook+1) = my;
}

DWORD cToolKit::WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
    DWORD dwErrorCode   = 0;
    DWORD dwOldProtect  = 0;

    int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, & dwOldProtect);

    if( iRes == 0 )
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }

    memcpy(lpAddress, lpBuf, uSize);

    DWORD dwBytes   = 0;

    iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, & dwBytes);

    if ( iRes == 0 )
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }

    return 0x00;
}

DWORD cToolKit::ReadMemory(const LPVOID lpAddress, LPVOID lpBuf, const UINT uSize)
{
    DWORD dwErrorCode = 0;
    DWORD dwOldProtect = 0;

    int iRes = VirtualProtect(lpAddress, uSize, PAGE_EXECUTE_READWRITE, & dwOldProtect);

    if(iRes == 0)
    {
        dwErrorCode = GetLastError();
        return dwErrorCode;
    }

    memcpy(lpBuf, lpAddress, uSize);

    DWORD dwBytes = 0;

    iRes = VirtualProtect(lpAddress, uSize, dwOldProtect, & dwBytes);

    if(iRes == 0)
    {
        dwErrorCode = GetLastError();
        
		return dwErrorCode;
    }

    return 0x00;
}

DWORD cToolKit::SetByte(const LPVOID dwOffset, const BYTE btValue)
{
	return WriteMemory(dwOffset, (LPVOID) & btValue, sizeof(BYTE));
}

DWORD cToolKit::GetByte(const LPVOID dwOffset, BYTE & btValue)
{
	return ReadMemory(dwOffset, (LPVOID) btValue, sizeof(BYTE));
}

DWORD cToolKit::SetWord(const LPVOID dwOffset, const WORD wValue)
{
	return WriteMemory(dwOffset, (LPVOID) & wValue, sizeof(WORD));
}

DWORD cToolKit::GetWord(const LPVOID dwOffset, WORD & wValue)
{
	return ReadMemory(dwOffset, (LPVOID) wValue, sizeof(WORD));
}

DWORD cToolKit::SetDword(const LPVOID dwOffset, const DWORD dwValue)
{
	return WriteMemory(dwOffset, (LPVOID) & dwValue, sizeof(DWORD));
}

DWORD cToolKit::GetDword(const LPVOID dwOffset, DWORD & dwValue)
{
	return ReadMemory(dwOffset, (LPVOID) dwValue, sizeof(DWORD));
}

DWORD cToolKit::SetFloat(const LPVOID dwOffset, float fValue)
{
	return WriteMemory(dwOffset, & fValue, sizeof(float));
}

DWORD cToolKit::GetFloat(const LPVOID dwOffset, float & fValue)
{
	return ReadMemory(dwOffset, & fValue, sizeof(float));
}


DWORD cToolKit::SetDouble(const LPVOID dwOffset, double dValue)
{
	return WriteMemory(dwOffset, & dValue, sizeof(double));
}

DWORD cToolKit::SetJmp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[5];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;

	btBuf[0]	= 0xE9;
	memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));

	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}

DWORD cToolKit::SetJg(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[6];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;

	btBuf[0]	= 0x0F;
	btBuf[1]	= 0x8F;
	memcpy( (LPVOID) & btBuf[2], (LPVOID) & dwShift, sizeof(ULONG_PTR));

	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}

DWORD cToolKit::SetJa(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress)
{
	BYTE btBuf[6];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 6;

	btBuf[0]	= 0x0F;
	btBuf[1]	= 0x87;
	memcpy( (LPVOID) & btBuf[2], (LPVOID) & dwShift, sizeof(ULONG_PTR));

	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}

DWORD cToolKit::SetOp(const LPVOID dwEnterFunction, const LPVOID dwJMPAddress, const BYTE cmd)
{
	BYTE btBuf[5];
	DWORD dwShift	= (ULONG_PTR)dwJMPAddress - (ULONG_PTR)dwEnterFunction - 5;

	btBuf[0]		= cmd;
	memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));

	return WriteMemory(dwEnterFunction, (LPVOID) btBuf, sizeof(btBuf));
}

DWORD cToolKit::SetRange(const LPVOID dwAddress, const USHORT wCount, const BYTE btValue)
{
	BYTE * lpBuf	= new BYTE[wCount];

	memset(lpBuf, btValue, wCount);

	return WriteMemory( dwAddress, (LPVOID) lpBuf, wCount);
}

DWORD cToolKit::SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd)
{
	BYTE btBuf[5];

	DWORD dwShift	= (ULONG_PTR)dwMyFuncOffset - ( (ULONG_PTR)dwJmpOffset + 5 );

	btBuf[0] = cmd;

	memcpy( (LPVOID) & btBuf[1], (LPVOID) & dwShift, sizeof(ULONG_PTR));

	return WriteMemory(dwJmpOffset, (LPVOID) btBuf, sizeof(btBuf));
}

LPVOID cToolKit::HookFunction(LPVOID origf, LPVOID callbackf, DWORD copylen)
{
	LPVOID newf = malloc(copylen + 6);
	DWORD dwOld;
	VirtualProtect(origf, copylen, PAGE_EXECUTE_READWRITE, &dwOld);
	memcpy(newf, origf, copylen);
	PBYTE j = (PBYTE)((DWORD)newf + copylen);
	j[0] = 0x68;
	*(DWORD*)&j[1] = (DWORD)((DWORD)origf + copylen);
	j[5] = 0xC3;
	j = (PBYTE)origf;
	j[0] = 0x68;
	*(DWORD*)&j[1] = (DWORD)(DWORD)callbackf;
	j[5] = 0xC3;
	VirtualProtect(origf, copylen, dwOld, &dwOld);

	return newf;
}

void cToolKit::Access(DWORD dwOffset, int t_size)
{
        DWORD OldProtect;
        VirtualProtect((LPVOID)dwOffset, t_size, PAGE_EXECUTE_READWRITE, &OldProtect);
}
 
void cToolKit::HookAddress(DWORD dwAddrOffst, DWORD dwNewOffst, BYTE new_Cmd)
{
        Access(dwAddrOffst, 5);
 
        if(new_Cmd)
                memset((void*)dwAddrOffst, new_Cmd, 1);
       
        *(DWORD*)(dwAddrOffst+1)=dwNewOffst-(dwAddrOffst+5);
}