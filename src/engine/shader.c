#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>

char* readShader(const char* ShaderPath);
void checkShaderError(unsigned int shader, const char* type);
void useShader(Shader* shader);
void setBool(Shader* shader, const char* name, int value);
void setInt(Shader* shader, const char* name, int value);
void setFloat(Shader* shader, const char* name, float value);
void setMat4(Shader* shader, const char* name, mat4 matrix);

void initializeShader(const char* vertexPath, const char* fragmentPath, Shader* shader)
{
    shader->useShader = useShader;
    shader->setBool = setBool;
    shader->setInt = setInt;
    shader->setFloat = setFloat;
    shader->setMat4 = setMat4;

    const char* VertexCode = readShader(vertexPath);
    const char* FragmentCode = readShader(fragmentPath);

    unsigned int vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &VertexCode, NULL);
    glCompileShader(vertexShader);
    checkShaderError(vertexShader, "Vertex");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &FragmentCode, NULL);
    glCompileShader(fragmentShader);
    checkShaderError(fragmentShader, "Fragment");

    shader->ID = glCreateProgram();
    glAttachShader(shader->ID, vertexShader);
    glAttachShader(shader->ID, fragmentShader);
    glLinkProgram(shader->ID);
    checkShaderError(shader->ID, "Program");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

char* readShader(const char* ShaderPath)
{
    FILE *ShaderFile;
    ShaderFile = fopen(ShaderPath, "r");

    char* ShaderCode = (char*)calloc(1, sizeof(char));
    size_t n = 1;

    char str[500];
    while (fgets(str, 500, ShaderFile))
    {
        n += strlen(str);
        char* tmp = (char*)realloc(ShaderCode, n);

        if (tmp == NULL) break;

        ShaderCode = tmp;

        strcat(ShaderCode, str);
    }
    fclose(ShaderFile);

    return ShaderCode;
}

void checkShaderError(unsigned int shader, const char* type)
{
    int success;
    char infoLog[1024];

    if (strcmp(type, "Program"))
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            printf("SHADER ERROR: %s:\n%s\n", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            printf("SHADER ERROR: %s:\n%s\n", type, infoLog);
        }
    }
}

void useShader(Shader* shader) 
{ 
    glUseProgram(shader->ID); 
}

void setBool(Shader* shader, const char* name, int value)
{         
    glUniform1i(glGetUniformLocation(shader->ID, name), (int)value); 
}

void setInt(Shader* shader, const char* name, int value)
{ 
    glUniform1i(glGetUniformLocation(shader->ID, name), value); 
}

void setFloat(Shader* shader, const char* name, float value)
{
    glUniform1f(glGetUniformLocation(shader->ID, name), value); 
}

void setMat4(Shader* shader, const char* name, mat4 matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, name), 1, GL_FALSE, matrix[0]);
}