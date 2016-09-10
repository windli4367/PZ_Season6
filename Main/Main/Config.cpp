#include "stdafx.h"
#include "Config.h"

cConfig gConfig;

cConfig::cConfig()
{
	this->Load();
}

void cConfig::Load()
{
	this->CSPort		= GetPrivateProfileInt("MAIN","Port",44405,CONFIG_MAIN_FILE);
	this->DecryptLog	= GetPrivateProfileInt("MAIN","DecryptLog",TRUE,CONFIG_MAIN_FILE);
	
	GetPrivateProfileString("MAIN","Address","192.168.1.2",this->IP,sizeof(this->IP),CONFIG_MAIN_FILE);
	GetPrivateProfileString("MAIN","Version","22749",this->Version,sizeof(this->Version),CONFIG_MAIN_FILE);
	GetPrivateProfileString("MAIN","Serial","k1Pk2jcET48mxL3b",this->Serial,sizeof(this->Serial),CONFIG_MAIN_FILE);
	GetPrivateProfileString("MAIN","Title","MU (PerfectZone)",this->Title,sizeof(this->Title),CONFIG_MAIN_FILE);
}