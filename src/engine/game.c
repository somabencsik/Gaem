#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#define APPEND_SIZE 10

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void addGameObject(Game* game, GameObject* gameObject);
void removeGameObject(Game* game, GameObject* gameObject);
void updateGame(Game* game, float deltaTime);
void renderGame(Game* game);
void loop(Game* game);
void checkCollision(Game* game, float deltaTime);
void clean(Game* game);

void initializeGame(unsigned int windowWidth, unsigned int windowHeight, Game* this)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->addGameObject = addGameObject;
    this->removeGameObject = removeGameObject;
    this->updateGame = updateGame;
    this->renderGame = renderGame;
    this->loop = loop;
    this->checkCollision = checkCollision;
    this->clean = clean;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // TODO: Handle errors
    this->window = glfwCreateWindow(
        this->windowWidth, this->windowHeight, "LearnOpenGL", NULL, NULL
    );
    glfwMakeContextCurrent(this->window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, this->windowWidth, this->windowHeight);
    glfwSetFramebufferSizeCallback(this->window, framebufferSizeCallback);

    initializeShader(
        "./resources/shaders/rectangle.vs",
        "./resources/shaders/rectangle.fs",
        &this->gameObjectShader
    );

    this->gameObjects = (GameObject*)malloc(APPEND_SIZE * sizeof(GameObject));
    this->gameObjectsSize = 0;
    this->gameObjectsRealSize = APPEND_SIZE;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void addGameObject(Game* game, GameObject* gameObject)
{
    game->gameObjects[game->gameObjectsSize] = *gameObject;
    ++game->gameObjectsSize;

    if (game->gameObjectsSize == game->gameObjectsRealSize - 1)
    {
        game->gameObjects = (GameObject*)realloc(game->gameObjects, (game->gameObjectsRealSize + APPEND_SIZE) * sizeof(GameObject));
        game->gameObjectsRealSize = game->gameObjectsRealSize + APPEND_SIZE;
    }
}

void removeGameObject(Game* game, GameObject* gameObject)
{
    // TODO
}

void updateGame(Game* game, float deltaTime)
{
    for (unsigned int i = 0; i < game->gameObjectsSize; ++i)
    {
        game->gameObjects[i].updateGameObject(game->window, &game->gameObjects[i], deltaTime);
    }
    game->checkCollision(game, deltaTime);
}

void renderGame(Game* game)
{
    GameObject player = game->gameObjects[0];
    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    float left = player.x - 800.0f / 2.0f + (player.width / 2.0f);
    float right = player.x+ 800.0f / 2.0f + (player.width / 2.0f);
    float top = player.y - 600.0f / 2.0f + (player.width / 2.0f);
    float bottom = player.y + 600.0f / 2.0f + (player.width / 2.0f);
    glm_ortho(left, right, bottom, top, -1.0f, 1.0f, projection);

    for (unsigned int i = 0; i < game->gameObjectsSize; ++i)
    {
        game->gameObjects[i].shader->useShader(game->gameObjects[i].shader);
        game->gameObjects[i].shader->setMat4(game->gameObjects[i].shader, "projection", projection);
        game->gameObjects[i].renderGameObject(&game->gameObjects[i]);
    }
}

void loop(Game* game)
{
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while(!glfwWindowShouldClose(game->window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game->updateGame(game, deltaTime);
        game->renderGame(game);

        glfwSwapBuffers(game->window);
        glfwPollEvents();
    }

    game->clean(game);
    glfwTerminate();
}

void checkCollision(Game* game, float deltaTime)
{
    GameObject* current;
    GameObject* check;
    for (unsigned int i = 0; i < game->gameObjectsSize; ++i)
    {
        current = &game->gameObjects[i];
        for (unsigned int j = 0; j < game->gameObjectsSize; ++j)
        {
            if (i == j) continue;
            check = &game->gameObjects[j];

            if (
                (   // Top left
                    current->x > check->x
                    && current->x < check->x + check->width
                    && current->y > check->y
                    && current->y < check->y + check->height
                )
                ||
                (   // Top right
                    current->x + current->width > check->x
                    && current->x + current->width < check->x + check->width
                    && current->y > check->y
                    && current->y < check->y + check->height
                )
                ||
                (   // Bottom left
                    current->x > check->x
                    && current->x < check->x + check->width
                    && current->y + current->height > check->y
                    && current->y + current->height < check->y + check->height
                )
                ||
                (   // Bottom right
                    current->x + current->width > check->x
                    && current->x + current->width < check->x + check->width
                    && current->y + current->height > check->y
                    && current->y + current->height < check->y + check->height
                )
            )

            {
                game->gameObjects[i].onCollision(&game->gameObjects[i], &game->gameObjects[j], deltaTime);
            }
        }
    }
}

void clean(Game* game)
{
    for (unsigned int i = 0; i < game->gameObjectsSize; ++i)
    {
        game->gameObjects[i].cleanGameObject(&game->gameObjects[i]);
    }
    free(game->gameObjects);
}