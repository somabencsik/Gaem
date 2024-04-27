gcc -Wall -I./include/dependencies -I./include/engine ./src/dependencies/*.c ./src/*.c ./src/engine/*.c -lglfw -lGL -lX11 -lpthread -lXrandr -ldl -lm -o main
./main