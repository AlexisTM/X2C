@echo off

:: ATTENTION: Adapt the line below to match your system setting!
set MPLABX_ROOT=C:\Program Files (x86)\Microchip\MPLABX\v3.35

:: project settings
set PROJECT_ROOT=%X2C_Root%DemoApplication\Blinky_Microchip_dsPIC33Fxxxx_MicrostickPlus
set DEVICE=P33FJ128MC802
set TOOL=PPKOB
set HEXFILE=/dist/Debug/production/Blinky_Microchip_dsPIC33Fxxxx_MicrostickPlus.production.hex
set MAKEFILE=%PROJECT_ROOT%\Makefile

:: put log file to project directory
set BATCHLOG=%PROJECT_ROOT%\batchlog.txt
:: make command
set MAKECMD="%MPLABX_ROOT%\gnuBins\GnuWin32\bin\make" -f %MAKEFILE%

:: program command
set PRGCMD=java -jar "%MPLABX_ROOT%\mplab_ipe\ipecmd.jar" /%DEVICE% /"F.%HEXFILE%" /T%TOOL% /M /OL

:: log informations
echo ===================================================== > %BATCHLOG%
echo Output log of %~n0 script >> %BATCHLOG%
echo ===================================================== >> %BATCHLOG%
echo Date: >> %BATCHLOG%
date /T >> %BATCHLOG%
echo Time: >> %BATCHLOG%
time /T >> %BATCHLOG%
echo ===================================================== >> %BATCHLOG%
echo. >> %BATCHLOG%
echo Current directory: %cd% >> %BATCHLOG%
echo Project directory: %PROJECT_ROOT% >> %BATCHLOG%
echo Makefile: %MAKEFILE% >> %BATCHLOG%
echo Hexfile: %HEXFILE% >> %BATCHLOG%
echo. >> %BATCHLOG%

:: change to working directory (project root)
cd %PROJECT_ROOT%

:: execute compile and flash
echo *****************************************************
echo ** make the project                                **
echo *****************************************************
echo Execute make: >> %BATCHLOG%
echo %MAKECMD% >> %BATCHLOG%
%MAKECMD%
echo *****************************************************
echo ** program the device                              **
echo *****************************************************
echo Execute program: >> %BATCHLOG%
echo %PRGCMD% >> %BATCHLOG%
%PRGCMD%