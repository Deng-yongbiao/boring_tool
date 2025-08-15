@echo off
setlocal enabledelayedexpansion

REM 构建脚本 - Windows
REM 用法: build.bat [Debug|Release]

REM 默认构建类型
if "%1"=="" (
    set BUILD_TYPE=Release
) else (
    set BUILD_TYPE=%1
)

set BUILD_DIR=build_%BUILD_TYPE%

echo 构建类型: %BUILD_TYPE%
echo 构建目录: %BUILD_DIR%

REM 创建构建目录
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

REM 配置CMake - 使用Visual Studio生成器
cmake -G "Visual Studio 17 2022" -A x64 -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ..

if %ERRORLEVEL% neq 0 (
    echo CMake配置失败！
    pause
    exit /b 1
)

REM 构建
cmake --build . --config %BUILD_TYPE%

if %ERRORLEVEL% neq 0 (
    echo 构建失败！
    pause
    exit /b 1
)

echo 构建完成！
echo 可执行文件位置: %BUILD_DIR%\bin\%BUILD_TYPE%\
echo 库文件位置: %BUILD_DIR%\lib\%BUILD_TYPE%\

pause
