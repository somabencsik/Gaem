#ifndef SPRITE_H
#define SPRITE_H

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "shader.h"
#include "texture.h"

typedef struct _sprite Sprite;
struct _sprite
{
    Shader shader;
    Texture texture;

    unsigned int VAO;

    float X;
    float Y;
    float Width;
    float Height;
    float XOffset;
    float YOffset;

    void (*render)(Sprite*);
    void (*update)(Sprite*, GLFWwindow*);
};

Sprite CreateSprite(
    const char* VertexPath,
    const char* FragmentPath,
    const char* TexturePath,
    float X,
    float Y,
    float Width,
    float Height
);

#endif // SPRITE_H