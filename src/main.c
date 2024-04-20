#include "game.h"

#include <stdio.h>

typedef struct _player Player;
struct _player
{
    Rectangle Rect;
};

void PlayerInput(GLFWwindow* window, Rectangle* Rect, float deltaTime);
void PlayerCollision(Rectangle* Rect, Rectangle* Other);

Player CreatePlayer(
    const char* TexturePath,
    float X,
    float Y,
    float Width,
    float Height)
{
    Player player;
    CreateRectangle(TexturePath, X, Y, Width, Height, &player.Rect);
    player.Rect.Update = PlayerInput;
    player.Rect.OnCollision = PlayerCollision;
    return player;
}

void PlayerInput(GLFWwindow* window, Rectangle* Rect, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Rect->X = Rect->X + (200 * deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        Rect->X = Rect->X - (200 * deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        Rect->Y = Rect->Y - (200 * deltaTime);
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        Rect->Y = Rect->Y + (200 * deltaTime);
    }
}

void PlayerCollision(Rectangle* Rect, Rectangle* Other)
{
    // TODO: Make the leftover
    if (// Top left
        Rect->X > Other->X
        && Rect->X < Other->X + Other->Width
        && Rect->Y > Other->Y
        && Rect->Y < Other->Y + Other->Height
    )
    {
        
    }
    else if (// Top right
        Rect->X + Rect->Width > Other->X
        && Rect->X + Rect->Width < Other->X + Other->Width
        && Rect->Y > Other->Y
        && Rect->Y < Other->Y + Other->Height
    )
    {

    }
    else if (// Bottom left
        Rect->X > Other->X
        && Rect->X < Other->X + Other->Width
        && Rect->Y + Rect->Height > Other->Y
        && Rect->Y + Rect->Height < Other->Y + Other->Height
    )
    {

    }
    else if(// Bottom right
        Rect->X + Rect->Width > Other->X
        && Rect->X + Rect->Width < Other->X + Other->Width
        && Rect->Y + Rect->Height > Other->Y
        && Rect->Y + Rect->Height < Other->Y + Other->Height
    )
    {

    }
}

int main()
{
    Game game = CreateGame(800, 600);
    
    Player player = CreatePlayer("./container.jpg", 50.0f, 50.0f, 50.0f, 50.0f);
    game.AddObject(&game, &player.Rect);

    Rectangle rect;
    CreateRectangle("./container.jpg", 200.0f, 200.0f, 50.0f, 50.0f, &rect);
    game.AddObject(&game, &rect);
    
    //for (int i = 0; i < 800 / 50; ++i)
    //{
    //    for (int j = 0; j < 600 / 50; ++j)
    //    {
    //        if (i != 0 && i != 15 && j != 0 && j != 11)
    //            continue;
    //        rect = CreateRectangle("./container.jpg", 50.0f * i, 50.0f * j, 50.0f, 50.0f);
    //        game.AddObject(&game, &rect);
    //    }
    //}

    //printf("X: %f, Y: %f\nX: %f, Y: %f\n\n", Rect.X, Rect.Y, rect.X, rect.Y);
    
    //game.UpdateGame(&game);
    
    //printf("X: %f, Y: %f\nX: %f, Y: %f\n\n", Rect.X, Rect.Y, rect.X, rect.Y);


    game.Loop(&game);
    return 0;
}