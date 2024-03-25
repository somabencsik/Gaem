#include "shader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>

char* ReadShader(const char* ShaderPath);
void CheckShaderError(unsigned int shader, const char* type);
void use_shader(Shader* shader);
void setBool(Shader* shader, const char* name, int value);
void setInt(Shader* shader, const char* name, int value);
void setFloat(Shader* shader, const char* name, float value);
void setMat4(Shader* shader, const char* name, float matrix[4][4]);

Shader CreateShader(const char* VertexPath, const char* FragmentPath)
{
    Shader shader;
    shader.use_shader = use_shader;
    shader.setBool = setBool;
    shader.setInt = setInt;
    shader.setFloat = setFloat;
    shader.setMat4 = setMat4;

    const char* VertexCode = ReadShader(VertexPath);
    const char* FragmentCode = ReadShader(FragmentPath);

    unsigned int VertexShader, FragmentShader;
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &VertexCode, NULL);
    glCompileShader(VertexShader);
    CheckShaderError(VertexShader, "Vertex");

    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &FragmentCode, NULL);
    glCompileShader(FragmentShader);
    CheckShaderError(FragmentShader, "Fragment");

    shader.ID = glCreateProgram();
    glAttachShader(shader.ID, VertexShader);
    glAttachShader(shader.ID, FragmentShader);
    glLinkProgram(shader.ID);
    CheckShaderError(shader.ID, "Program");

    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);

    return shader;
}

char* ReadShader(const char* ShaderPath)
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

void CheckShaderError(unsigned int shader, const char* type)
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

void use_shader(Shader* shader) 
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

void setMat4(Shader* shader, const char* name, float matrix[4][4])
{

}