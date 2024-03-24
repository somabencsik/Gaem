#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct _texture Texture;
struct _texture
{
    unsigned int ID;

    void (*use_texture)(Texture *texture);
};

Texture CreateTexture(const char* TexturePath);
void use_texture(Texture* texture);

#endif // TEXTURE_H