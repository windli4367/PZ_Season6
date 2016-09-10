#include "stdafx.h"
#include "ServerDisplayer.h"
#include "ConnectServer.h"
#include "Log.h"
#include "ServerList.h"
#include "SocketManager.h"
#include "SocketManagerUdp.h"
#include "ClientManager.h"

#include "versionBuild.h"
#include "versionRelease.h"

CServerDisplayer gServerDisplayer;

CServerDisplayer::CServerDisplayer()
{
	for(int n=0;n < MAX_LOG_TEXT_LINE;n++)
	{
		memset(&this->m_log[n],0,sizeof(this->m_log[n]));
	}

	this->m_font = CreateFont
	(
		80,
		0,
		0,
		0,
		FW_THIN,
		FALSE, 
		TRUE,
		FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_DONTCARE,
		"Arial"
	);

	this->m_brush[0] = CreateSolidBrush(RGB(30,30,30));
	this->m_brush[1] = CreateSolidBrush(RGB(30,30,30));
	this->m_brush[2] = CreateSolidBrush(RGB(30,30,30));

	sprintf_s(m_DisplayerText[0],"ConnectServer");
	sprintf_s(m_DisplayerText[1],"v%d.%02d.%03d",CS_MAJOR_VERSION, RELEASE_NUM, BUILD_NUM);
}

CServerDisplayer::~CServerDisplayer()
{
	DeleteObject(this->m_font);
	DeleteObject(this->m_brush[0]);
	DeleteObject(this->m_brush[1]);
	DeleteObject(this->m_brush[2]);
}

void CServerDisplayer::Init(HWND hWnd)
{
	this->m_hwnd = hWnd;
	gLog.AddLog(1,"LOG");
}

void CServerDisplayer::Run()
{
	this->SetWindowName();
	this->PaintAllInfo();
	this->LogTextPaint();
}

void CServerDisplayer::SetWindowName()
{
	char buff[256];
	wsprintf(buff,"ConnectServer [%s]",m_DisplayerText[1]);
	SetWindowText(this->m_hwnd,buff);
}

void CServerDisplayer::PaintAllInfo()
{
	RECT rect;
	GetClientRect(this->m_hwnd,&rect);

	rect.top	= 0;
	rect.bottom = 100;

	HDC hdc = GetDC(this->m_hwnd);
	int OldBkMode = SetBkMode(hdc,TRANSPARENT);

	SetTextColor(hdc,RGB(200,200,200));
	FillRect(hdc,&rect,this->m_brush[0]);

	HFONT OldFont = (HFONT)SelectObject(hdc,this->m_font);
	SetTextColor(hdc,RGB(250,250,250));

	int left = (rect.right / 2) - ((strlen(this->m_DisplayerText[0]) * 20) + strlen(this->m_DisplayerText[0]) * 5);
	TextOut(hdc,left,0,this->m_DisplayerText[0],strlen(this->m_DisplayerText[0]));

	SelectObject(hdc,OldFont);

	SetTextColor(hdc,RGB(250,250,250));
	TextOut(hdc,left + strlen(this->m_DisplayerText[0]) * 38,65,this->m_DisplayerText[1],strlen(this->m_DisplayerText[1]));
	
	SetBkMode(hdc,OldBkMode);
	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::LogTextPaint()
{
	RECT rect;
	HDC hdc = GetDC(this->m_hwnd);
	GetClientRect(this->m_hwnd, &rect);

	int total = (rect.bottom-150)/15;

	rect.top	= 100;
	rect.bottom -= 20;
	FillRect(hdc,&rect,this->m_brush[2]);

	int n = (((this->m_count-1)>=0)?(this->m_count-1):(MAX_LOG_TEXT_LINE-1));;

	for (int i = total; i > 0 ; i--)
	{
		if(strlen(this->m_log[n].text) <= 0)
		{
			continue;
		}

		switch(this->m_log[n].color)
		{
			case LOG_BLACK:
			{
				SetTextColor(hdc,RGB(130,170,190));
				break;
			}
			case LOG_RED:
			{
				SetTextColor(hdc,RGB(255,0,0));
				break;
			}
			case LOG_GREEN:
			{
				SetTextColor(hdc,RGB(0,255,0));
				break;
			}
			case LOG_BLUE:
			{
				SetTextColor(hdc,RGB(0,240,240));
				break;
			}
		}

		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc,0,i*15 + 100,this->m_log[n].text,strlen(this->m_log[n].text)); 
		n--;

		if(n<0)
		{
			n = MAX_LOG_TEXT_LINE - 1;
		}
	}

	char szTemp[128];
	wsprintf(szTemp,"Portas: [%d TCP - %d UDP] - Conexões por IP: %d - Tempo máximo away: %d segundos",ConnectServerPortTCP,ConnectServerPortUDP,MaxIpConnection,MAX_ONLINE_TIME / 1000);;
	TextOut(hdc,0,rect.bottom + 3,szTemp,strlen(szTemp));

	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::LogAddText(eLogColor color,char* text,int size)
{
	if(size >= MAX_LOG_TEXT_SIZE)
	{
		size = MAX_LOG_TEXT_SIZE;
	}

	memset(&this->m_log[this->m_count].text,0,sizeof(this->m_log[this->m_count].text));
	memcpy(&this->m_log[this->m_count].text,text,size);

	this->m_log[this->m_count].color = color;

	if(++this->m_count >= MAX_LOG_TEXT_LINE)
	{
		this->m_count = 0;
	}

	gLog.Output(LOG_GENERAL,"%s",&text[9]);
}
