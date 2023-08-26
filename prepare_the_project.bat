@echo off
setlocal enabledelayedexpansion

pushd %~dp0

echo ===========================
echo Getting all the submodules
echo ===========================
call %~dp0\get_submodules.bat

echo ===========================
echo Building bgfx
echo ===========================
call %~dp0\SDKs\bgfx\build_bgfx.bat

popd

echo ===========================
echo All is done!!!
echo ===========================

pause
