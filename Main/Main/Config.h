#pragma once

#define CONFIG_MAIN_FILE ".\\config.ini"

class cConfig
{
public:
	cConfig();

	void Load();

	WORD CSPort;
	CHAR IP[16];
	CHAR Version[6];
	CHAR Serial[20];
	CHAR Title[32];
	 
	BOOL DecryptLog;
};

extern cConfig gConfig;