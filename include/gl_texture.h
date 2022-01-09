#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include"gl_object.h"
#include"glm/vec3.hpp"

// TEXTURE UNIT

class gl_texture : public gl_object{
    public:
        gl_texture();
        ~gl_texture();
        void bind(GLenum GL_TEXTUREI);
        void loadData(const char *texture_path, bool textureIsAlpha);
        int getUnit() const;
        glm::vec3 ambient, diffuse, specular, color;
        float shininess;
    private:
        int width, height, channel;
        GLenum tex_unit;
        unsigned char *data;
};

#endif // GLTEXTURE_H