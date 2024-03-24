@echo off
gcc -I./include/dependencies -I./include/engine ./src/dependencies/*.c ./src/*.c ./src/engine/*.c -L./libs/ -lglfw3 -lopengl32 -lkernel32 -luser32 -lgdi32 -lws2_32 -o main
.\main.exe