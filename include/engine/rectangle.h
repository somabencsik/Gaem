#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "shader.h"
#include "texture.h"

#include "attribute.h"

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
    short int isCollide;
    Rectangle* collideRect;

    Attribute* attributes;
    unsigned int attrSize;
    unsigned int attrRealSize;

    void (*Render)(Rectangle*);
    void (*Update)(GLFWwindow*, Rectangle*, float);

    void (*OnCollision)(Rectangle*, Rectangle*, float);

    void (*addAttribute)(Rectangle*, Attribute);
    
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