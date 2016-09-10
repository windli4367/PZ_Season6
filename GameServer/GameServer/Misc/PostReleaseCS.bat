FOR /F %%i in (release.ver) do set /a v=%%i+1
echo %v% > release.ver
echo #pragma once > versionRelease.h
echo #define RELEASE_NUM %v% >> versionRelease.h

copy ..\Release\GameServer_EX603CS\GameServer.exe ..\..\Files\GameServerCS\GameServer.exe
copy ..\Release\GameServer_EX603CS\GameServer.pdb ..\..\PDB\GameServerCS_%v%.pdb