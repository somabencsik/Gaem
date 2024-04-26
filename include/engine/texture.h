#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct _texture Texture;
struct _texture
{
    unsigned int ID;

    void (*use_texture)(Texture *texture);
};

void initializeTexture(const char* TexturePath, Texture* texture);

#endif // TEXTURE_H