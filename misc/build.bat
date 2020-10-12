@echo off

set DIRECT=..\misc
set TARGET=x64
set TARGET_PATH=x64

:: SDL2 libraries and include paths 
set SDL2_LIB=W:\SDL2

set SDL2_LIBDIR=%SDL2_LIB%\lib\%TARGET_PATH%
set SDL2_LIBINC=%SDL2_LIB%\include

if not exist build mkdir build 
pushd build 

robocopy %SDL2_LIBDIR% . *.dll

cl -Zi -FC -MD %DIRECT%\primitive_test.cpp -I%SDL2_LIBINC% %SDL2_LIBDIR%\SDL2.lib %SDL2_LIBDIR%\SDL2main.lib Shell32.lib -link /machine:%TARGET% -subsystem:CONSOLE
popd
