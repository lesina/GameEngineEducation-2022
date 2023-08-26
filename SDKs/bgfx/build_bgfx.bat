pushd %~dp0

cd bgfx\
..\bx\tools\bin\windows\genie --with-windows=10 vs2022
cd ..

setlocal enabledelayedexpansion

echo ===========================
echo Looking for MSBuild
echo ===========================
set "PATH=%PATH%;%ProgramFiles(x86)%\Microsoft Visual Studio\Installer"
set MSBUILD_PATH=""
for /f "tokens=* USEBACKQ" %%i in (`vswhere.exe -version "[17.0,)" -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe`) do (
    set MSBUILD_PATH=%%i
)

if "%MSBUILD_PATH%" == """" (
    echo "VS2022 wasn't found"
    pause
    popd
    exit
)
echo "MSbuild path is: %MSBUILD_PATH%"

SET CL=/std:c++17 /MDd
SET _CL_=/std:c++17 /MDd

"%MSBUILD_PATH%" bgfx\.build\projects\vs2022\bgfx.sln /p:Configuration=Debug /p:Platform=Win32 /p:PlatformToolset=v143
"%MSBUILD_PATH%" bgfx\.build\projects\vs2022\bgfx.sln /p:Configuration=Debug /p:Platform=x64 /p:PlatformToolset=v143

SET CL=/std:c++17 /MD
SET _CL_=/std:c++17 /MD

"%MSBUILD_PATH%" bgfx\.build\projects\vs2022\bgfx.sln /p:Configuration=Release /p:Platform=Win32 /p:PlatformToolset=v143
"%MSBUILD_PATH%" bgfx\.build\projects\vs2022\bgfx.sln /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143

xcopy bgfx\.build\win64_vs2022\bin lib\x64 /Y
xcopy bgfx\.build\win32_vs2022\bin lib\Win32 /Y

popd