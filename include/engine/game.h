#ifndef GAME_H
#define GAME_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "rectangle.h"

typedef struct _game Game;
struct _game
{
    unsigned int WindowWidth;
    unsigned int WindowHeight;
    GLFWwindow* Window;

    Rectangle* Objects;
    unsigned int ObjectsSize;
    unsigned int ObjectsRealSize;

    void (*AddObject)(Game*, Rectangle*);
    void (*RemoveObject)(Game*, Rectangle*);

    void (*UpdateGame)(Game*, float);
    void (*RenderGame)(Game*);
    void (*Loop)(Game*); // Better name for Loop

    void (*CheckCollision)(Game*);

    void (*Clean)(Game*);
};

Game CreateGame(unsigned int WindowWidth, unsigned int WindowHeight);

#endif // GAME_H