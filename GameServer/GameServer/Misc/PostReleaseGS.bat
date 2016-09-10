FOR /F %%i in (release.ver) do set /a v=%%i+1
echo %v% > release.ver
echo #pragma once > versionRelease.h
echo #define RELEASE_NUM %v% >> versionRelease.h

copy ..\Release\GameServer_EX603\GameServer.exe ..\..\Files\GameServer\GameServer.exe
copy ..\Release\GameServer_EX603\GameServer.pdb ..\..\PDB\GameServer_%v%.pdb