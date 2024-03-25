#include <stdio.h>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "shader.h"
#include "texture.h"
#include "rectangle.h"

#define true 1
#define false 0

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

//////
////// EXAMPLE FOR PLAYER CODE
//////

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
    player.Rect.update = PlayerInput;
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


//////
////// END OF EXAMPLE
//////

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("ERROR: Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("ERROR: Failed to initialize GLAD\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Player player = CreatePlayer("./container.jpg", 50.0f, 50.0f, 50.0f, 50.0f);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        player.Rect.update(window, &player.Rect);
        player.Rect.render(&player.Rect);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &player.Rect.VAO);
    glDeleteBuffers(1, &player.Rect.VBO);
    glDeleteBuffers(1, &player.Rect.EBO);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}