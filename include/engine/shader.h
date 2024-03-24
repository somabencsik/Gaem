#ifndef SHADER_H
#define SHADER_H

typedef struct _shader Shader;
struct _shader
{
    unsigned int ID;

    void (*use_shader)(Shader*);
    void (*setBool)(Shader*, const char*, int);
    void (*setInt)(Shader*, const char*, int);
    void (*setFloat)(Shader*, const char*, float);
    void (*setMat4)(Shader*, const char*, float[4][4]);
};

Shader CreateShader(const char* VertexPath, const char* FragmentPath);
void use_shader(Shader* shader);
void setBool(Shader* shader, const char* name, int value);
void setInt(Shader* shader, const char* name, int value);
void setFloat(Shader* shader, const char* name, float value);
void setMat4(Shader* shader, const char* name, float matrix[4][4]);

#endif // SHADER_H