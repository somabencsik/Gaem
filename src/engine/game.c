#include "game.h"

#include <stdio.h>
#include <stdlib.h>

#define APPEND_SIZE 10

void FramebufferSizeCallback(GLFWwindow* Window, int Width, int Height);
void AddObject(Game* game, Rectangle* Rect);
void RemoveObject(Game* game, Rectangle* Rect);
void UpdateGame(Game* game, float deltaTime);
void RenderGame(Game* game);
void Loop(Game* game);
void CheckCollision(Game* game, float deltaTime);
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
    game.CheckCollision = CheckCollision;
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

void UpdateGame(Game* game, float deltaTime)
{
    for (unsigned int i = 0; i < game->ObjectsSize; ++i)
    {
        game->Objects[i].Update(game->Window, &game->Objects[i], deltaTime);
    }
    game->CheckCollision(game, deltaTime);
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
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while(!glfwWindowShouldClose(game->Window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game->UpdateGame(game, deltaTime);
        game->RenderGame(game);

        glfwSwapBuffers(game->Window);
        glfwPollEvents();
    }

    game->Clean(game);
    glfwTerminate();
}

void CheckCollision(Game* game, float deltaTime)
{
    Rectangle Current;
    Rectangle Check;
    for (unsigned int i = 0; i < game->ObjectsSize; ++i)
    {
        Current = game->Objects[i];
        for (unsigned int j = 0; j < game->ObjectsSize; ++j)
        {
            if (i == j) continue;
            Check = game->Objects[j];

            if (
                (   // Top left
                    Current.X > Check.X
                    && Current.X < Check.X + Check.Width
                    && Current.Y > Check.Y
                    && Current.Y < Check.Y + Check.Height
                )
                ||
                (   // Top right
                    Current.X + Current.Width > Check.X
                    && Current.X + Current.Width < Check.X + Check.Width
                    && Current.Y > Check.Y
                    && Current.Y < Check.Y + Check.Height
                )
                ||
                (   // Bottom left
                    Current.X > Check.X
                    && Current.X < Check.X + Check.Width
                    && Current.Y + Current.Height > Check.Y
                    && Current.Y + Current.Height < Check.Y + Check.Height
                )
                ||
                (   // Bottom right
                    Current.X + Current.Width > Check.X
                    && Current.X + Current.Width < Check.X + Check.Width
                    && Current.Y + Current.Height > Check.Y
                    && Current.Y + Current.Height < Check.Y + Check.Height
                )
            )

            {
                game->Objects[i].OnCollision(&game->Objects[i], &game->Objects[j], deltaTime);
                game->Objects[i].collideRect = &game->Objects[j];
                game->Objects[i].isCollide = 1;
            }
            else
            {
                game->Objects[i].isCollide = 0;
                game->Objects[i].collideRect = NULL;
            }
        }
    }
}

void Clean(Game* game)
{
    for (unsigned int i = 0; i < game->ObjectsSize; ++i)
    {
        game->Objects[i].CleanUp(&game->Objects[i]);
    }
    free(game->Objects);
}