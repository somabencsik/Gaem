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
void playerUpdate(GLFWwindow* window, GameObject* this, float deltaTime);
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
    this->object.updateGameObject = playerUpdate;
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

void playerUpdate(GLFWwindow* window, GameObject* this, float deltaTime)
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

    mat4 projection = GLM_MAT4_IDENTITY_INIT;
    float left = this->x - 800.0f / 2.0f + (this->width / 2.0f);
    float right = this->x+ 800.0f / 2.0f + (this->width / 2.0f);
    float top = this->y - 600.0f / 2.0f + (this->width / 2.0f);
    float bottom = this->y + 600.0f / 2.0f + (this->width / 2.0f);
    glm_ortho(left, right, bottom, top, -1.0f, 1.0f, projection);

    this->shader->useShader(this->shader);
    this->shader->setMat4(this->shader, "projection", projection);
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
    this->x = this->x - xDisplacement;
    unsigned short int xPrevCollision = isCollision(this, other);
    this->x = this->x + xDisplacement;
    unsigned short int xCollision = xCurrCollision && !xPrevCollision;
    while(xCollision)
    {
        xCurrCollision = isCollision(this, other);
        this->x = this->x - xDisplacement;
        xPrevCollision = isCollision(this, other);
        this->x = this->x + xDisplacement;
        xCollision = xCurrCollision && !xPrevCollision;
        this->x = this->x - (movement[0] * deltaTime);
    }

    unsigned short int yCurrCollision = isCollision(this, other);
    this->y = this->y - yDisplacement;
    unsigned short int yPrevCollision = isCollision(this, other);
    this->y = this->y + yDisplacement;
    unsigned short int yCollision = yCurrCollision && !yPrevCollision;
    
    while(yCollision)
    {
        yCurrCollision = isCollision(this, other);
        this->y = this->y - yDisplacement;
        yPrevCollision = isCollision(this, other);
        this->y = this->y + yDisplacement;
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
    
    GameObject wall;
    for (int i = 0; i < 800 / 50; ++i)
    {
        for (int j = 0; j < 600 / 50; ++j)
        {
            if (i != 0 && i != 15 && j != 0 && j != 11)
                continue;
            initializeGameObject(
                50.0f * i, 50.0f * j, 50.0f, 50.0f,
                &wall, &game.gameObjectShader, &playerTexture
            );
            game.addGameObject(&game, &wall);
        }
    }

    game.loop(&game);
    return 0;
}