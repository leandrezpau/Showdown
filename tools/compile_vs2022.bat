@ECHO off
cls

@echo ---------------------------------------------------
@echo            Premakeando Todo que locura
@echo ---------------------------------------------------
@echo            Proceso por lotes iniciado.
@echo ---------------------------------------------------

.\Premake5 --file=premake.lua vs2022

@echo ---------------------------------------------------
@echo            Authors: Pau Leandrez
@echo                     Nicolás Ferrando
@echo                     Sergio Tordera
@echo ---------------------------------------------------

pause
