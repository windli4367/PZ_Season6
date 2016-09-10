FOR /F %%i in (release.ver) do set /a v=%%i+1
echo %v% > release.ver
echo #pragma once > versionRelease.h
echo #define RELEASE_NUM %v% >> versionRelease.h

copy ..\Release\JoinServer.exe ..\..\Files\JoinServer\JoinServer.exe
copy ..\Release\JoinServer.pdb ..\..\PDB\JoinServer_%v%.pdb