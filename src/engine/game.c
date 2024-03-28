#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#define APPEND_SIZE 10

void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height);
void AddObject(Game* game, Rectangle* Rect);
void RemoveObject(Game* game, Rectangle* Rect);
void UpdateGame(Game* game);
void RenderGame(Game* game);
void Loop(Game* game);
void Clean(Game* game);

Game CreateGame(unsigned int WindowWidth, unsigned int WindowHeight)
{
    Game game;

    game.WindowWidth = WindowWidth;
    game.WindowHeight = WindowHeight;
    game.AddObject = AddObject;
    game.RemoveObject = RemoveObject;
    game.UpdateGame = UpdateGame;
    game.RenderGame = RenderGame;
    game.Loop = Loop;
    game.Clean = Clean;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // TODO: Handle errors
    game.Window = glfwCreateWindow(
        game.WindowWidth, game.WindowHeight, "LearnOpenGL", NULL, NULL
    );
    glfwMakeContextCurrent(game.Window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, game.WindowWidth, game.WindowHeight);
    glfwSetFramebufferSizeCallback(game.Window, FramebufferSizeCallback);

    game.Objects = (Rectangle*)malloc(APPEND_SIZE * sizeof(Rectangle));
    game.ObjectsSize = 0;
    game.ObjectsRealSize = APPEND_SIZE;

    return game;
}

void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height)
{
    glViewport(0, 0, Width, Height);
}

void AddObject(Game* game, Rectangle* Rect)
{
    game->Objects[game->ObjectsSize] = *Rect;
    ++game->ObjectsSize;

    if (game->ObjectsSize == game->ObjectsRealSize - 1)
    {
        game->Objects = (Rectangle*)realloc(game->Objects, (game->ObjectsRealSize + APPEND_SIZE) * sizeof(Rectangle));
        game->ObjectsRealSize = game->ObjectsRealSize + APPEND_SIZE;
    }
}

void RemoveObject(Game* game, Rectangle* Rect)
{
    // TODO
}

void UpdateGame(Game* game)
{
    for (unsigned int i = 0; i < game->ObjectsSize; ++i)
    {
        game->Objects[i].Update(game->Window, &game->Objects[i]);
    }
}

void RenderGame(Game* game)
{
    for (unsigned int i = 0; i < game->ObjectsSize; ++i)
    {
        game->Objects[i].Render(&game->Objects[i]);
    }
}

void Loop(Game* game)
{
    while(!glfwWindowShouldClose(game->Window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game->UpdateGame(game);
        game->RenderGame(game);

        glfwSwapBuffers(game->Window);
        glfwPollEvents();
    }

    game->Clean(game);
    glfwTerminate();
}

void Clean(Game* game)
{
    for (unsigned int i = 0; i < game->ObjectsSize; ++i)
    {
        game->Objects[i].CleanUp(&game->Objects[i]);
    }
}