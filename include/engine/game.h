#ifndef GAME_H
#define GAME_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "gameObject.h"

typedef struct _game Game;
struct _game
{
    unsigned int windowWidth, windowHeight;
    GLFWwindow* window;

    GameObject* gameObjects;
    unsigned int gameObjectsSize;
    unsigned int gameObjectsRealSize;

    Shader gameObjectShader;

    void (*addGameObject)(Game*, GameObject*);
    void (*removeGameObject)(Game*, GameObject*);

    void (*updateGame)(Game*, float);
    void (*renderGame)(Game*);
    void (*loop)(Game*); // Better name for Loop

    void (*checkCollision)(Game*, float);

    void (*clean)(Game*);
};

void initializeGame(unsigned int windowWidth, unsigned int windowHeight, Game* this);

#endif // GAME_H