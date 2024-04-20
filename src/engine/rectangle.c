#include "rectangle.h"

#include <stdio.h>
#include <stdlib.h>

void Render(Rectangle* Rect);
void Update(GLFWwindow* window, Rectangle* Rect, float deltaTime);
void OnCollision(Rectangle* Rect, Rectangle* Other);
void CleanUp(Rectangle* Rect);

void CreateRectangle(
    const char* TexturePath,
    float X,
    float Y,
    float Width,
    float Height,
    Rectangle* Rect
)
{
    Rect->Update = Update;
    Rect->Render = Render;
    Rect->OnCollision = OnCollision;
    Rect->CleanUp = CleanUp;

    CreateShader(
        "./resources/shaders/rectangle.vs",
        "./resources/shaders/rectangle.fs",
        &Rect->shader
    );
    CreateTexture(TexturePath, &Rect->texture);

    Rect->InitX = X;
    Rect->InitY = Y;
    Rect->Width = Width;
    Rect->Height = Height;
    Rect->XOffset = 0.0f;
    Rect->YOffset = 0.0f;
    Rect->X = X;
    Rect->Y = Y;

    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &Rect->VAO);
    glGenBuffers(1, &Rect->VBO);

    glBindBuffer(GL_ARRAY_BUFFER, Rect->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(Rect->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    glm_ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f, projection);

    Rect->shader.useShader(&Rect->shader);
    Rect->shader.setMat4(&Rect->shader, "projection", projection);
}

void Render(Rectangle* Rect)
{
    Rect->shader.useShader(&Rect->shader);

    mat4 model = GLM_MAT4_IDENTITY_INIT;

    glm_translate(model, (vec3){Rect->X, Rect->Y, 0.0f});
    glm_translate(model, (vec3){Rect->Width * 0.5f, Rect->Height * 0.5f, 0.0f});
    glm_rotate(model, glm_rad(0.0f), (vec3){0.0f, 0.0f, 1.0f});
    glm_translate(model, (vec3){Rect->Width * -0.5f, Rect->Height * -0.5f, 0.0f});
    glm_scale(model, (vec3){Rect->Width, Rect->Height, 1.0f});

    Rect->shader.setMat4(&Rect->shader, "model", model);

    Rect->texture.use_texture(&Rect->texture);
    glBindVertexArray(Rect->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Update(GLFWwindow* window, Rectangle* Rect, float deltaTime)
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