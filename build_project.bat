@echo off
echo Cleaning build directory...
if exist build rmdir /s /q build
mkdir build
cd build

echo Configuring with MinGW-w64 (winlibs)...
cmake -G "Ninja" ^
    -DCMAKE_C_COMPILER="C:/MinGW/winlibs/mingw64/bin/gcc.exe" ^
    -DCMAKE_CXX_COMPILER="C:/MinGW/winlibs/mingw64/bin/g++.exe" ^
    ..

if %errorlevel% neq 0 (
    echo CMake configuration failed!
    exit /b %errorlevel%
)

echo Building project...
cmake --build .

if %errorlevel% neq 0 (
    echo Build failed!
    exit /b %errorlevel%
)

echo Build successful!
exit /b 0
