// CriticalSection.cpp: implementation of the CCriticalSection class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CriticalSection.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCriticalSection::CCriticalSection()
{
	InitializeCriticalSection(&this->m_critical);
}

CCriticalSection::~CCriticalSection()
{
	DeleteCriticalSection(&this->m_critical);
}

void CCriticalSection::lock()
{
	EnterCriticalSection(&this->m_critical);
}

void CCriticalSection::unlock()
{
	LeaveCriticalSection(&this->m_critical);
}
