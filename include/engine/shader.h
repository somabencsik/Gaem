#ifndef SHADER_H
#define SHADER_H

#include "cglm/cglm.h"

typedef struct _shader Shader;
struct _shader
{
    unsigned int ID;

    void (*useShader)(Shader*);
    void (*setBool)(Shader*, const char*, int);
    void (*setInt)(Shader*, const char*, int);
    void (*setFloat)(Shader*, const char*, float);
    void (*setMat4)(Shader*, const char*, mat4);
};

void CreateShader(const char* VertexPath, const char* FragmentPath, Shader* shader);

#endif // SHADER_H