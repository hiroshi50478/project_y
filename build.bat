@echo off

rmdir build /q /s
mkdir build

cmake -S . -B build -G "MinGW Makefiles"
cmake --build build --config Release
game.exe