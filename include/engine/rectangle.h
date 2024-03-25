#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "shader.h"
#include "texture.h"

typedef struct _rectangle Rectangle;
struct _rectangle
{
    Shader shader;
    Texture texture;

    unsigned int VAO, VBO, EBO;

    float X;
    float Y;
    float Width;
    float Height;
    float XOffset;
    float YOffset;

    void (*render)(Rectangle*);
    void (*update)(GLFWwindow*, Rectangle*);
};

Rectangle CreateRectangle(
    const char* TexturePath,
    float X,
    float Y,
    float Width,
    float Height
);

#endif // RECTANGLE_H