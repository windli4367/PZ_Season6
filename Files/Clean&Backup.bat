@ECHO OFF

DEL MuServer.rar

DEL ConnectServer\*.dmp					/Q /F
DEL ConnectServer\ConnectServer.v11.suo			/Q /F
RMDIR ConnectServer\LOG					/S /Q

DEL DataServer\*.dmp					/Q /F
DEL DataServer\DataServer.v11.suo			/Q /F
RMDIR DataServer\LOG					/S /Q

DEL JoinServer\*.dmp					/Q /F
DEL JoinServer\JoinServer.v11.suo			/Q /F
RMDIR JoinServer\LOG					/S /Q
RMDIR JoinServer\LOG_ACCOUNT				/S /Q

DEL GameServer\*.dmp					/Q /F
DEL GameServer\GameServer.v11.suo			/Q /F
RMDIR GameServer\LOG					/S /Q
RMDIR GameServer\CONNECT_LOG				/S /Q
RMDIR GameServer\HACK_LOG				/S /Q

DEL GameServerCS\*.dmp					/Q /F
DEL GameServerCS\GameServer.v11.suo			/Q /F
RMDIR GameServerCS\LOG					/S /Q
RMDIR GameServerCS\CONNECT_LOG				/S /Q
RMDIR GameServerCS\HACK_LOG				/S /Q

DEL Tools\StartUp\Configuration\bor_StartUp.xml.bak 	/Q /F
RMDIR Tools\Startup\Logs				/S /Q


"%ProgramFiles%\Winrar\rar.exe" a -r -m5 "MuServer"