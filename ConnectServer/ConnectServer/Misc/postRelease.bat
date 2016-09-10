FOR /F %%i in (release.ver) do set /a v=%%i+1
echo %v% > release.ver
echo #pragma once > versionRelease.h
echo #define RELEASE_NUM %v% >> versionRelease.h

copy ..\Release\ConnectServer.exe ..\..\Files\ConnectServer\ConnectServer.exe
copy ..\Release\ConnectServer.pdb ..\..\PDB\ConnectServer_%v%.pdb