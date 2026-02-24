@ECHO off
cls

@echo ---------------------------------------------------
@echo                 Premake ShowDown
@echo ---------------------------------------------------
@echo            Proceso por lotes iniciado.
@echo ---------------------------------------------------

.\Premake5 --file=premake.lua vs2022

@echo ---------------------------------------------------
@echo            Authors: Pau Leandrez
@echo                     Nicolas Ferrando
@echo                     Sergio Tordera
@echo ---------------------------------------------------

pause
