@REM @file
@REM
@REM Copyright (c) 2017, Intel Corporation. All rights reserved.<BR>
@REM This program and the accompanying materials
@REM are licensed and made available under the terms and conditions of the BSD License
@REM which accompanies this distribution.  The full text of the license may be found at
@REM http://opensource.org/licenses/bsd-license.php
@REM
@REM THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
@REM WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
@REM

@echo off
echo.
echo Run build cleanall...
echo.

cd ..

if not defined WORKSPACE set WORKSPACE=%cd%
if not defined WORKSPACE_PLATFORM set WORKSPACE_PLATFORM=%cd%
if not defined WORKSPACE_SILICON set WORKSPACE_SILICON=%cd%

REM build cleanall

echo.
echo Directories to clean...
echo.

if exist %WORKSPACE%\build rmdir /q /s %WORKSPACE%\build
if exist %WORKSPACE%\conf\.cache rmdir /q /s %WORKSPACE%\conf\.cache

echo.
echo Files to clean...
echo.

if exist %WORKSPACE%\edk2.log del %WORKSPACE%\edk2.log
if exist %WORKSPACE%\Conf\build_rule.txt del %WORKSPACE%\Conf\build_rule.txt
if exist %WORKSPACE%\Conf\FrameworkDatabase.db del %WORKSPACE%\Conf\FrameworkDatabase.db
if exist %WORKSPACE%\Conf\target.txt del %WORKSPACE%\Conf\target.txt
if exist %WORKSPACE%\Conf\tools_def.txt del %WORKSPACE%\Conf\tools_def.txt
@REM *.c.c is generated by Catalog Debug feature across code tree.
@REM
del /s *.c.c > nul 2>&1

cd %WORKSPACE_PLATFORM%\%PROJECT%

del /f /q Prep.log > nul 2>&1
del /f /q ..\Build.log > nul 2>&1

echo.
echo All done...
echo.
@echo on
