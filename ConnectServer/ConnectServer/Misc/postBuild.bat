FOR /F %%i in (build.ver) do set /a v=%%i+1
echo %v% > build.ver
echo #pragma once > versionBuild.h
echo #define BUILD_NUM %v% >> versionBuild.h

COPY ..\Debug\ConnectServer.exe ..\..\Files\ConnectServer\ConnectServer.exe