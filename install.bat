@echo off


rmdir external /q /s
mkdir external

mkdir external\glfw
mkdir external\glfw\lib
mkdir external\glfw\include

mkdir external\glew
mkdir external\glew\lib
mkdir external\glew\include


rmdir temp /q /s
mkdir temp

git clone https://github.com/glfw/glfw.git temp\glfw
cmake -S temp\glfw -B temp\glfw\build -G "MinGW Makefiles"
cmake --build temp\glfw\build --config Release
copy temp\glfw\build\src\libglfw3.a external\glfw\lib
xcopy temp\glfw\include external\glfw\include /e /h /c /i

rem echo Loading glew-2.2.0.zip to %cd%\glew.zip
rem curl https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip -o %cd%\glew.zip
rem echo Unpacking %cd%\glew.zip
rem tar -x -f %cd%\glew.zip
rem del glew.zip
rem cd glew-2.2.0/build/cmake
rem cmake -S . -B build -G "MinGW Makefiles"
rem cmake --build build --config Release
rem cd ../../..

rem rmdir temp /q /s