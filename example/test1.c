#include "game.h"

#include <stdio.h>

typedef struct _player Player;
struct _player
{
    Rectangle Rect;
    vec2 movement;
    float speed;
};

unsigned short int isCollision(Rectangle* rect, Rectangle* other);
void PlayerInput(GLFWwindow* window, Rectangle* Rect, float deltaTime);
void playerCollision(Rectangle* rect, Rectangle* other, float deltaTime);

void CreatePlayer(
    const char* TexturePath,
    float X,
    float Y,
    float Width,
    float Height,
    Player* player)
{
    CreateRectangle(TexturePath, X, Y, Width, Height, &player->Rect);
    player->Rect.Update = PlayerInput;
    player->Rect.OnCollision = playerCollision;

    player->movement[0] = 0.0f;
    player->movement[1] = 0.0f;
    player->Rect.addAttribute(&player->Rect, (Attribute){player->movement, "vec2", "movement"});

    player->speed = 200.0f;
    player->Rect.addAttribute(&player->Rect, (Attribute){(void*)&player->speed, "float", "speed"});
}

void PlayerInput(GLFWwindow* window, Rectangle* Rect, float deltaTime)
{
    float speed = *(float*)getAttrValue("speed", Rect->attributes, Rect->attrSize);
    float* movement = getAttrValue("movement", Rect->attributes, Rect->attrSize);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        movement[0] = 1;
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        movement[0] = -1;
    else
        movement[0] = 0;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        movement[1] = -1;
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        movement[1] = 1;
    else
        movement[1] = 0;

    float xDisplacement = ((speed * deltaTime) * movement[0]);
    float yDisplacement = ((speed * deltaTime) * movement[1]);

    Rect->X = Rect->X + xDisplacement;
    Rect->Y = Rect->Y + yDisplacement;

    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    float left = Rect->X - 800.0f / 2.0f + (Rect->Width / 2);
    float right = Rect->X + 800.0f / 2.0f + (Rect->Width / 2);
    float bottom = Rect->Y - 600.0f / 2.0f + (Rect->Width / 2);
    float top = Rect->Y + 600.0f / 2.0f + (Rect->Width / 2);
    glm_ortho(left, right, bottom, top, -1.0f, 1.0f, projection);
    //printf("left: %f, right: %f, bottom: %f, top: %f\n\n", left, right, bottom, top);
    Rect->shader.useShader(&Rect->shader);
    Rect->shader.setMat4(&Rect->shader, "projection", projection);
}

unsigned short int isCollision(Rectangle* rect, Rectangle* other)
{
    return (
      rect->X + rect->Width / 2  > other->X - other->Width / 2 &&
      rect->X - rect->Width / 2  < other->X + other->Width / 2 &&
      rect->Y + rect->Height / 2 > other->Y - other->Height / 2 &&
      rect->Y - rect->Height / 2 < other->Y + other->Height / 2
    );
}

void playerCollision(Rectangle* rect, Rectangle* other, float deltaTime)
{
    float speed = *(float*)getAttrValue("speed", rect->attributes, rect->attrSize);
    float* movement = getAttrValue("movement", rect->attributes, rect->attrSize);

    float xDisplacement = ((speed * deltaTime) * movement[0]);
    float yDisplacement = ((speed * deltaTime) * movement[1]);

    unsigned short int xCurrCollision = isCollision(rect, other);
    rect->X = rect->X - (xDisplacement * 2);
    unsigned short int xPrevCollision = isCollision(rect, other);
    rect->X = rect->X + (xDisplacement * 2);
    unsigned short int xCollision = xCurrCollision && !xPrevCollision;
    while(xCollision)
    {
        xCurrCollision = isCollision(rect, other);
        rect->X = rect->X - (xDisplacement * 2);
        xPrevCollision = isCollision(rect, other);
        rect->X = rect->X + (xDisplacement * 2);
        xCollision = xCurrCollision && !xPrevCollision;
        rect->X = rect->X - (movement[0] * deltaTime);
    }

    unsigned short int yCurrCollision = isCollision(rect, other);
    rect->Y = rect->Y - (yDisplacement * 2);
    unsigned short int yPrevCollision = isCollision(rect, other);
    rect->Y = rect->Y + (yDisplacement * 2);
    unsigned short int yCollision = yCurrCollision && !yPrevCollision;
    
    while(yCollision)
    {
        yCurrCollision = isCollision(rect, other);
        rect->Y = rect->Y - (yDisplacement * 2);
        yPrevCollision = isCollision(rect, other);
        rect->Y = rect->Y + (yDisplacement * 2);
        yCollision = yCurrCollision && !yPrevCollision;
        rect->Y = rect->Y - (movement[1] * deltaTime);
    }
}

int main()
{
    Game game = CreateGame(800, 600);
    
    Player player;
    CreatePlayer("./container.jpg", 50.0f, 50.0f, 50.0f, 50.0f, &player);
    game.AddObject(&game, &player.Rect);
    
    for (int i = 0; i < 800 / 50; ++i)
    {
        for (int j = 0; j < 600 / 50; ++j)
        {
            if (i != 0 && i != 15 && j != 0 && j != 11)
                continue;
            Rectangle rect;
            CreateRectangle("./container.jpg", 50.0f * i, 50.0f * j, 50.0f, 50.0f, &rect);
            game.AddObject(&game, &rect);
        }
    }

    game.Loop(&game);
    return 0;
}