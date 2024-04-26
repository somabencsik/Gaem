#include "game.h"

#include <stdio.h>

typedef struct _player Player;
struct _player
{
    GameObject object;
    vec2 movement;
    float speed;
};

unsigned short int isCollision(GameObject* this, GameObject* other);
void playerInput(GLFWwindow* window, GameObject* this, float deltaTime);
void playerCollision(GameObject* this, GameObject* other, float deltaTime);

void initializePlayer(
    float x,
    float y,
    float width,
    float height,
    Texture* texture,
    Shader* shader,
    Player* this
)
{
    initializeGameObject(x, y, width, height, &this->object, shader, texture);
    this->object.updateGameObject = playerInput;
    this->object.onCollision = playerCollision;

    this->movement[0] = 0.0f;
    this->movement[1] = 0.0f;
    Attribute movementAttr;
    initializeAttribute(this->movement, "vec2", "movement", &movementAttr);
    this->object.addAttribute(&this->object, &movementAttr);

    this->speed = 200.0f;
    Attribute speedAttr = {(void*)&this->speed, "float", "speed"};
    this->object.addAttribute(&this->object, &speedAttr);
}

void playerInput(GLFWwindow* window, GameObject* this, float deltaTime)
{
    float speed = *(float*)getAttrValue("speed", this->attributes, this->attrSize);
    float* movement = getAttrValue("movement", this->attributes, this->attrSize);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        movement[0] = 1;
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        movement[0] = -1;
    }
    else
    {
        movement[0] = 0;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        movement[1] = -1;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        movement[1] = 1;
    }
    else
    {
        movement[1] = 0;
    }

    float xDisplacement = ((speed * deltaTime) * movement[0]);
    float yDisplacement = ((speed * deltaTime) * movement[1]);

    this->x = this->x + xDisplacement;
    this->y = this->y + yDisplacement;
}

unsigned short int isCollision(GameObject* this, GameObject* other)
{
    return (
      this->x + this->width / 2  > other->x - other->width / 2 &&
      this->x - this->width / 2  < other->x + other->width / 2 &&
      this->y + this->height / 2 > other->y - other->height / 2 &&
      this->y - this->height / 2 < other->y + other->height / 2
    );
}

void playerCollision(GameObject* this, GameObject* other, float deltaTime)
{
    float speed = *(float*)getAttrValue("speed", this->attributes, this->attrSize);
    float* movement = getAttrValue("movement", this->attributes, this->attrSize);

    float xDisplacement = ((speed * deltaTime) * movement[0]);
    float yDisplacement = ((speed * deltaTime) * movement[1]);

    unsigned short int xCurrCollision = isCollision(this, other);
    this->x = this->x - (xDisplacement * 2);
    unsigned short int xPrevCollision = isCollision(this, other);
    this->x = this->x + (xDisplacement * 2);
    unsigned short int xCollision = xCurrCollision && !xPrevCollision;
    while(xCollision)
    {
        xCurrCollision = isCollision(this, other);
        this->x = this->x - (xDisplacement * 2);
        xPrevCollision = isCollision(this, other);
        this->x = this->x + (xDisplacement * 2);
        xCollision = xCurrCollision && !xPrevCollision;
        this->x = this->x - (movement[0] * deltaTime);
    }

    unsigned short int yCurrCollision = isCollision(this, other);
    this->y = this->y - (yDisplacement * 2);
    unsigned short int yPrevCollision = isCollision(this, other);
    this->y = this->y + (yDisplacement * 2);
    unsigned short int yCollision = yCurrCollision && !yPrevCollision;
    
    while(yCollision)
    {
        yCurrCollision = isCollision(this, other);
        this->y = this->y - (yDisplacement * 2);
        yPrevCollision = isCollision(this, other);
        this->y = this->y + (yDisplacement * 2);
        yCollision = yCurrCollision && !yPrevCollision;
        this->y = this->y - (movement[1] * deltaTime);
    }
}

int main()
{
    Game game;
    initializeGame(800, 600, &game);

    Texture playerTexture;
    initializeTexture("./container.jpg", &playerTexture);
    
    Player player;
    initializePlayer(
        100.0f, 100.0f, 50.0f, 50.0f,
        &playerTexture, &game.gameObjectShader, &player
    ); 
    game.addGameObject(&game, &player.object);
    
    for (int i = 0; i < 800 / 50; ++i)
    {
        for (int j = 0; j < 600 / 50; ++j)
        {
            if (i != 0 && i != 15 && j != 0 && j != 11)
                continue;
            GameObject wall;
            initializeGameObject(50.0f * i, 50.0f * j, 50.0f, 50.0f, &wall, &game.gameObjectShader, &playerTexture);
            game.addGameObject(&game, &wall);
        }
    }

    game.loop(&game);
    return 0;
}