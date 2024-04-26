#include "gameObject.h"

#include <stdlib.h>

#define APPEND_SIZE 4

void addAttribute(GameObject* this, Attribute* attribute);
void updateGameObject(GLFWwindow* window, GameObject* this, float deltaTime);
void renderGameObject(GameObject* this);
void onCollision(GameObject* this, GameObject* other, float deltaTime);
void cleanGameObject(GameObject* this);

void initializeGameObject(
    float x,
    float y,
    float width,
    float height,
    GameObject* this,
    Shader* shader,
    Texture* texture
)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    this->attributes = (Attribute*)malloc(APPEND_SIZE * sizeof(Attribute));
    this->attrSize = 0;
    this->attrRealSize = APPEND_SIZE;

    this->addAttribute = addAttribute;
    this->updateGameObject = updateGameObject;
    this->renderGameObject = renderGameObject;
    this->onCollision = onCollision;
    this->cleanGameObject = cleanGameObject;

    this->shader = shader;
    this->texture = texture;

    float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void addAttribute(GameObject* this, Attribute* attribute)
{
    this->attributes[this->attrSize] = *attribute;
    ++this->attrSize;
    if (this->attrSize == this->attrRealSize - 1)
    {
        this->attributes = (Attribute*)realloc(this->attributes, (this->attrRealSize + APPEND_SIZE) * sizeof(Attribute));
        this->attrRealSize = this->attrRealSize + APPEND_SIZE;
    }
}

void updateGameObject(GLFWwindow* window, GameObject* this, float deltaTime)
{

}

void renderGameObject(GameObject* this)
{
    this->shader->useShader(this->shader);

    mat4 model = GLM_MAT4_IDENTITY_INIT;
    glm_translate(model, (vec3){this->x, this->y, 0.0f});
    glm_translate(model, (vec3){this->width * 0.5f, this->height * 0.5f, 0.0f});
    glm_rotate(model, glm_rad(0.0f), (vec3){0.0f, 0.0f, 1.0f});
    glm_translate(model, (vec3){this->width * -0.5f, this->height * -0.5f, 0.0f});
    glm_scale(model, (vec3){this->width, this->height, 1.0f});

    this->shader->setMat4(this->shader, "model", model);

    this->texture->use_texture(this->texture);
    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void onCollision(GameObject* this, GameObject* other, float deltaTime)
{

}

void cleanGameObject(GameObject* this)
{
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    free(this->attributes);
}