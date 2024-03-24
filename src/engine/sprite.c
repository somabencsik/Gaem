#include "sprite.h"

#include <stdio.h>
#include <stdlib.h>

Sprite CreateSprite(
    const char* VertexPath,
    const char* FragmentPath,
    const char* TexturePath,
    float X,
    float Y,
    float Width,
    float Height
)
{
    Sprite sprite;

    sprite.shader = CreateShader(VertexPath, FragmentPath);
    sprite.texture = CreateTexture(TexturePath);

    sprite.X = X;
    sprite.X = Y;
    sprite.Width = Width;
    sprite.Height = Height;
    sprite.XOffset = 0.0f;
    sprite.YOffset = 0.0f;

    float DrawX = X / 400 - 1;
    float DrawY = (Y / 300 - 1) * -1;
    float DrawWidth = (Width + X) / 400 - 1;
    float DrawHeight = ((Height + Y) / 300 - 1) * -1;

    float vertices[] = {
        // positions          // colors           // texture coords
        DrawWidth,    DrawY,   0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        DrawWidth,    DrawHeight,   0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        DrawX,   DrawHeight,   0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        DrawX,   DrawY,   0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &sprite.VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(sprite.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    sprite.update = update;
    sprite.render = render;

    return sprite;
}

void render(Sprite* sprite)
{
    sprite->texture.use_texture(&sprite->texture);
    sprite->shader.use_shader(&sprite->shader);
    glBindVertexArray(sprite->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void update(Sprite* sprite, GLFWwindow* window)
{
    sprite->shader.setFloat(&sprite->shader, "xOffset", sprite->XOffset);
    sprite->shader.setFloat(&sprite->shader, "yOffset", sprite->YOffset);

    float DrawX = sprite->X / 400 - 1;
    float DrawY = (sprite->Y / 300 - 1) * -1;
    sprite->X = (DrawX + sprite->XOffset + 1.0f) * 400.0f;
    sprite->Y = (DrawX + sprite->XOffset + 1.0f) * 400.0f;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        sprite->XOffset = sprite->XOffset + 0.001;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        sprite->XOffset = sprite->XOffset - 0.001;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        sprite->YOffset = sprite->YOffset + 0.001;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        sprite->YOffset = sprite->YOffset - 0.001;
    }
}