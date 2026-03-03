@ECHO off
cls

echo ---------------------------------------------------
echo            Compilando ShowDown con MSVC
echo ---------------------------------------------------

:: 1. Compilacion y Enlazado
:: Usamos /nologo para limpiar la salida de la consola
cl /std:c++17 /EHsc /O2 ^
    ../src/*.cc ../src/sqlfuncs/*.cc ../src/sprites/*.cc ../include/sqlite/sqlite3.c ^
    /I../include /I../include/SDL3 /I../include/SDL3_image /I../include/SDL3_ttf /I../include/sqlite ^
    /link /LIBPATH:../lib/x64 SDL3.lib SDL3_image.lib SDL3_ttf.lib ^
    /OUT:../bin/ShowDown.exe /MACHINE:X64

:: 2. Verificamos si la compilacion fue exitosa antes de borrar
IF %ERRORLEVEL% EQU 0 (
    echo.
    echo ---------------------------------------------------
    echo            Compilacion EXITOSA
    echo            Borrando archivos temporales .obj...
    del *.obj
    echo ---------------------------------------------------
    echo Ejecutable listo en: /bin/ShowDown.exe
) ELSE (
    echo.
    echo ###################################################
    echo            ERROR EN LA COMPILACION
    echo ###################################################
)

pause