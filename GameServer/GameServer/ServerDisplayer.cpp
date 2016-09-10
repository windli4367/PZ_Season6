// ServerDisplayer.cpp: implementation of the CServerDisplayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ServerDisplayer.h"
#include "GameMain.h"
#include "Log.h"
#include "ServerInfo.h"
#include "SocketManager.h"
#include "User.h"

CServerDisplayer gServerDisplayer;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CServerDisplayer::CServerDisplayer() // OK
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
}

CServerDisplayer::~CServerDisplayer() // OK
{
	DeleteObject(this->m_font);
	DeleteObject(this->m_brush[0]);
	DeleteObject(this->m_brush[1]);
	DeleteObject(this->m_brush[2]);
}

void CServerDisplayer::Init(HWND hWnd) // OK
{
	this->m_hwnd = hWnd;

	gLog.AddLog(1,"LOG");
	gLog.AddLog(gServerInfo.m_WriteChatLog,"CHAT_LOG");
	gLog.AddLog(gServerInfo.m_WriteCommandLog,"COMMAND_LOG");
	gLog.AddLog(gServerInfo.m_WriteTradeLog,"TRADE_LOG");
	gLog.AddLog(gServerInfo.m_WriteConnectLog,"CONNECT_LOG");
	gLog.AddLog(gServerInfo.m_WriteHackLog,"HACK_LOG");
	gLog.AddLog(gServerInfo.m_WriteCashShopLog,"CASH_SHOP_LOG");
	gLog.AddLog(gServerInfo.m_WriteChaosMixLog,"CHAOS_MIX_LOG");
}

void CServerDisplayer::Run() // OK
{
	this->SetWindowName();
	this->PaintAllInfo();
	this->LogTextPaint();
}

void CServerDisplayer::SetWindowName() // OK
{
	char buff[256];
	wsprintf(buff,"[%s][%s][%d] %s",GAMESERVER_VERSION,gServerInfo.m_ServerVersion,gServerInfo.m_ServerCode,gServerInfo.m_ServerName);

	SetWindowText(this->m_hwnd,buff);
}

void CServerDisplayer::PaintAllInfo() // OK
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

	int left = (rect.right / 2) - ((strlen(gServerInfo.m_ServerName) * 20) + strlen(gServerInfo.m_ServerVersion) * 5);
	TextOut(hdc,left,0,gServerInfo.m_ServerName,strlen(gServerInfo.m_ServerName));

	SelectObject(hdc,OldFont);

	char msg[40]			= {};
	int textPosX			= 5;
	const int textPosY		= 85;
	const int textPaddingX	= 20;

	// DataServer
	sprintf_s(msg,"DataServer:  ");
	SetTextColor(hdc,RGB(130,130,240));
	TextOut(hdc,textPosX,textPosY,msg,sizeof(msg));
	textPosX += (int)(strlen(msg)*6.4);
	memset(msg,0,sizeof(msg));

	if(gDataServerConnection.CheckState())
	{
		sprintf_s(msg,"Online");
		SetTextColor(hdc,RGB(0,150,0));
	}
	else
	{
		sprintf_s(msg,"Offline");
		SetTextColor(hdc,RGB(150,0,0));
	}

	TextOut(hdc,textPosX,textPosY,msg,sizeof(msg));

	textPosX += strlen(msg)*7+textPaddingX;
	memset(msg,0,sizeof(msg));

	// JoinServer
	sprintf_s(msg,"JoinServer: ");
	SetTextColor(hdc,RGB(130,130,240));
	TextOut(hdc,textPosX,textPosY,msg,sizeof(msg));
	textPosX += (int)(strlen(msg)*6.6);
	memset(msg, 0, sizeof(msg));

	if(gJoinServerConnection.CheckState())
	{
		sprintf_s(msg,"Online");
		SetTextColor(hdc,RGB(0,150,0));
	}
	else
	{
		sprintf_s(msg,"Offline");
		SetTextColor(hdc,RGB(150,0,0));
	}

	SetTextColor(hdc,RGB(0,150,0));
	TextOut(hdc,textPosX,textPosY,msg,sizeof(msg));
	//

	//if(gJoinServerConnection.CheckState() == false || gDataServerConnection.CheckState() == false)
	//{
	//	SetTextColor(hdc,RGB(130, 130, 240));
	//	TextOut(hdc,left+strlen(gServerInfo.m_ServerName) * 38, 65,this->m_DisplayerText[0],strlen(this->m_DisplayerText[0]));
	//}
	//else
	//{
	//	SetTextColor(hdc,RGB(0,150,0));
	//	TextOut(hdc,left+strlen(gServerInfo.m_ServerName) * 38, 65,this->m_DisplayerText[1],strlen(this->m_DisplayerText[1]));
	//}
	
	SetBkMode(hdc,OldBkMode);
	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::LogTextPaint() // OK
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

		if (n<0)
		{
			n = MAX_LOG_TEXT_LINE - 1;
		}
	}

	char szTemp[128];

	wsprintf
	(
		szTemp,
		"Jogadores: [%d / %d] Monstros + NPCs: [%d / %d] Castle Siege [%d]",
		gObjTotalUser,
		gServerInfo.m_ServerMaxUserNumber,
		gObjTotalMonster,
		MAX_OBJECT_MONSTER,
		gServerInfo.m_CastleSiegeEvent
	);

	TextOut(hdc,0,rect.bottom + 3,szTemp,strlen(szTemp));

	ReleaseDC(this->m_hwnd,hdc);
}

void CServerDisplayer::LogAddText(eLogColor color,char* text,int size) // OK
{
	size = ((size>=MAX_LOG_TEXT_SIZE)?(MAX_LOG_TEXT_SIZE-1):size);

	memset(&this->m_log[this->m_count].text,0,sizeof(this->m_log[this->m_count].text));

	memcpy(&this->m_log[this->m_count].text,text,size);

	this->m_log[this->m_count].color = color;

	this->m_count = (((++this->m_count)>=MAX_LOG_TEXT_LINE)?0:this->m_count);

	gLog.Output(LOG_GENERAL,"%s",&text[9]);
}
