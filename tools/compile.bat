@echo off

cl ..\src\test.cc ^
   /I ..\include ^
   /link ^
   /LIBPATH:..\lib\x64 ^
   SDL3.lib ^
   /OUT:..\bin\test.exe

pause