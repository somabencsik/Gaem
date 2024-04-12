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

void CreateShader(const char* VertexPath, const char* FragmentPath, Shader* shader);

#endif // SHADER_H