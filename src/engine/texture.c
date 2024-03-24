#include "texture.h"

#include <glad/glad.h>
#include "stb_image.h"

Texture CreateTexture(const char* TexturePath)
{
    Texture texture;

    glGenTextures(1, &texture.ID);
    glBindTexture(GL_TEXTURE_2D, texture.ID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(
        TexturePath,
        &width,
        &height,
        &nrChannels,
        0
    );
    if (data)
    {
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RGB,
            width,
            height,
            0,
            GL_RGB,
            GL_UNSIGNED_BYTE,
            data
        );
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        printf("ERROR: Failed to load texture\n");
    }
    stbi_image_free(data);

    texture.use_texture = use_texture;

    return texture;
}

void use_texture(Texture* texture)
{
    glBindTexture(GL_TEXTURE_2D, texture->ID);
}