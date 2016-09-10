FOR /F %%i in (release.ver) do set /a v=%%i+1
echo %v% > release.ver
echo #pragma once > versionRelease.h
echo #define RELEASE_NUM %v% >> versionRelease.h

copy ..\Release\DataServer.exe ..\..\Files\DataServer\DataServer.exe
copy ..\Release\DataServer.pdb ..\..\PDB\DataServer_%v%.pdb