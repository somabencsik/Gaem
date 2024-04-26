#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "texture.h"

#include "attribute.h"

typedef struct _game_object GameObject;
struct _game_object
{
    Shader* shader;
    Texture* texture;

    float x, y, width, height;
    unsigned int VAO, VBO;

    Attribute* attributes;
    unsigned int attrSize, attrRealSize;
    void (*addAttribute)(GameObject*, Attribute*);

    void (*updateGameObject)(GLFWwindow*, GameObject*, float);
    void (*renderGameObject)(GameObject*);

    void (*onCollision)(GameObject*, GameObject*, float);

    void (*cleanGameObject)(GameObject*);

};

void initializeGameObject(
    float x,
    float y,
    float width,
    float height,
    GameObject* this,
    Shader* shader,
    Texture* texture
);

#endif // GAME_OBJECT_H