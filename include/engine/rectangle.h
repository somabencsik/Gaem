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
    float InitX;
    float InitY;
    float Width;
    float Height;
    float XOffset;
    float YOffset;
    float DrawX;
    float DrawY;

    void (*Render)(Rectangle*);
    void (*Update)(GLFWwindow*, Rectangle*, float);

    void (*OnCollision)(Rectangle*, Rectangle*);
    
    void (*CleanUp)(Rectangle*);
};

void CreateRectangle(
    const char* TexturePath,
    float X,
    float Y,
    float Width,
    float Height,
    Rectangle* Rect
);

#endif // RECTANGLE_H