cd bgfx\
..\bx\tools\bin\windows\genie vs2022
cd ..

setlocal enabledelayedexpansion
for /f "delims=" %%i in ('"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -latest -requires Microsoft.Component.MSBuild -find MSBuild\**\Bin\MSBuild.exe') do set msbuild_path=%%i

SET CL=/std:c++17 /MDd
SET _CL_=/std:c++17 /MDd

"%msbuild_path%" bgfx\.build\projects\vs2022\bgfx.sln /p:Configuration=Debug /p:Platform=Win32
"%msbuild_path%" bgfx\.build\projects\vs2022\bgfx.sln /p:Configuration=Debug /p:Platform=x64

SET CL=/std:c++17 /MD
SET _CL_=/std:c++17 /MD

"%msbuild_path%" bgfx\.build\projects\vs2022\bgfx.sln /p:Configuration=Release /p:Platform=Win32
"%msbuild_path%" bgfx\.build\projects\vs2022\bgfx.sln /p:Configuration=Release /p:Platform=x64

xcopy bgfx\.build\win64_vs2022\bin lib\x64 /Y
xcopy bgfx\.build\win32_vs2022\bin lib\Win32 /Y