#include "game.h"

#include <stdio.h>

typedef struct _player Player;
struct _player
{
    Rectangle Rect;
};

void PlayerInput(GLFWwindow* window, Rectangle* Rect);

Player CreatePlayer(
    const char* TexturePath,
    float X,
    float Y,
    float Width,
    float Height)
{
    Player player;
    player.Rect = CreateRectangle(TexturePath, X, Y, Width, Height);
    player.Rect.Update = PlayerInput;
    return player;
}

void PlayerInput(GLFWwindow* window, Rectangle* Rect)
{
    Rect->shader.setFloat(&Rect->shader, "xOffset", Rect->XOffset);
    Rect->shader.setFloat(&Rect->shader, "yOffset", Rect->YOffset);

    float DrawX = Rect->X / 400 - 1;
    float DrawY = (Rect->Y / 300 - 1) * -1;
    Rect->X = (DrawX + Rect->XOffset + 1.0f) * 400.0f;
    Rect->Y = (DrawX + Rect->XOffset + 1.0f) * 400.0f;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Rect->XOffset = Rect->XOffset + 0.01;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Rect->XOffset = Rect->XOffset - 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Rect->YOffset = Rect->YOffset + 0.01;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Rect->YOffset = Rect->YOffset - 0.01;
    }
}

int main()
{
    Game game = CreateGame(800, 600);

    /*
    for (int i = 0; i < 800 / 50; ++i)
    {
        for (int j = 0; j < 600 / 50; ++j)
        {
            if (i != 0 && i != 15 && j != 0 && j != 11)
                continue;
            Rectangle rect = CreateRectangle("./container.jpg", 50.0f * i, 50.0f * j, 50.0f, 50.0f);
            game.AddObject(&game, &rect);
        }
    }*/

    Player player = CreatePlayer("./container.jpg", 50.0f, 50.0f, 50.0f, 50.0f);
    game.AddObject(&game, &player.Rect);

    game.Loop(&game);
    return 0;
}