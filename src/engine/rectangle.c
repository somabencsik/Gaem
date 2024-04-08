#include "rectangle.h"

#include <stdio.h>
#include <stdlib.h>

void Render(Rectangle* Rect);
void Update(GLFWwindow* window, Rectangle* Rect);
void OnCollision(Rectangle* Rect, Rectangle* Other);
void CleanUp(Rectangle* Rect);

Rectangle CreateRectangle(
    const char* TexturePath,
    float X,
    float Y,
    float Width,
    float Height
)
{
    Rectangle Rect;

    Rect.Update = Update;
    Rect.Render = Render;
    Rect.OnCollision = OnCollision;
    Rect.CleanUp = CleanUp;

    Rect.shader = CreateShader(
        "./resources/shaders/rectangle.vs",
        "./resources/shaders/rectangle.fs"
    );
    Rect.texture = CreateTexture(TexturePath);

    Rect.InitX = X;
    Rect.InitY = Y;
    Rect.Width = Width;
    Rect.Height = Height;
    Rect.XOffset = 0.0f;
    Rect.YOffset = 0.0f;

    float DrawX = X / 400 - 1;
    float DrawY = (Y / 300 - 1) * -1;
    float DrawWidth = (Width + X) / 400 - 1;
    float DrawHeight = ((Height + Y) / 300 - 1) * -1;

    float vertices[] = {
        // positions                     // texture coords
        DrawWidth,  DrawY,      0.0f,    1.0f, 1.0f, // top right
        DrawWidth,  DrawHeight, 0.0f,    1.0f, 0.0f, // bottom right
        DrawX,      DrawHeight, 0.0f,    0.0f, 0.0f, // bottom left
        DrawX,      DrawY,      0.0f,    0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    glGenVertexArrays(1, &Rect.VAO);
    glGenBuffers(1, &Rect.VBO);
    glGenBuffers(1, &Rect.EBO);

    glBindVertexArray(Rect.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, Rect.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Rect.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return Rect;
}

void Render(Rectangle* Rect)
{
    Rect->texture.use_texture(&Rect->texture);
    Rect->shader.use_shader(&Rect->shader);
    glBindVertexArray(Rect->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Update(GLFWwindow* window, Rectangle* Rect)
{
    
}

void OnCollision(Rectangle* Rect, Rectangle* Other)
{

}

void CleanUp(Rectangle* Rect)
{
    glDeleteVertexArrays(1, &Rect->VAO);
    glDeleteBuffers(1, &Rect->VBO);
    glDeleteBuffers(1, &Rect->EBO);
}