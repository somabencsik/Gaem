@echo off
SET type=%1

if %type% == engine GOTO ENGINE
if %type% == example GOTO EXAMPLE

:ENGINE
gcc -Wall -I./include/dependencies -I./include/engine ./src/dependencies/*.c ./src/*.c ./src/engine/*.c -L./libs/ -lglfw3 -lopengl32 -lkernel32 -luser32 -lgdi32 -lws2_32 -o main
.\main.exe
EXIT

:EXAMPLE
gcc -I./include/dependencies -I./include/engine -c ./src/dependencies/*.c ./src/engine/*.c -L./libs/ -lglfw3 -lopengl32 -lkernel32 -luser32 -lgdi32 -lws2_32
gcc -shared -o engine.dll *.o  -L./libs/ -lglfw3 -lopengl32 -lkernel32 -luser32 -lgdi32 -lws2_32
del *.o
gcc -I./include/dependencies -I./include/engine example/*.c -L./libs/ -L./ -lengine -o example/test1
.\example\test1.exe
EXIT