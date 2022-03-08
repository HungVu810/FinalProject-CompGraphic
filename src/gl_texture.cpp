#include "../include/gl_texture.h"
// header to extract texture data
#define STB_IMAGE_IMPLEMENTATION
#include <../include/stb_image.h>
#include <cassert>
#include <iostream>

// static init
unsigned gl_texture::ambient = 0;
unsigned gl_texture::diffuse = 0;
unsigned gl_texture::specular = 0;
unsigned gl_texture::emission = 0;

// associate sampler2D uniform variable with a texture unit via glUniform1i or glUniform1iv
// unsigned ai_textureType is the unsinged equivalance of the aiTextureType enum class elements
gl_texture::gl_texture(const char *texture_path, aiTextureType type) : gl_object(){
    // Define STBI_FAILURE_USERMSG to get user-friendly debug string
    data = stbi_load(texture_path, &width, &height, &channel, 0);
	assert(data);
	assignSamplerName(type);
    glGenTextures(1, &name);
}

gl_texture::~gl_texture(){
	// problem with free an not malloc'ed data
	stbi_image_free(data);
    glDeleteTextures(1, &name);
}

// the provided tex_unit must be unique (not used by another gl_texture when binding) from 0 to GL_MAX_COMBINED_TEXURE_IMAGE_UNITS. The tex_unit support all texture binding points. There can only 1 texure per tex_unit because 2 different sampler can't be assigned with the same tex_unit contains 2 different bounded binding points
void gl_texture::bind(GLenum GL_TEXTUREI){
    // the same as glActiveTexture(tex_unit) and glBindTexture(name)
    assert(GL_TEXTUREI >= 0 && GL_TEXTUREI < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS);
    tex_unit = GL_TEXTUREI;
    glActiveTexture(GL_TEXTUREI);
    glBindTexture(GL_TEXTURE_2D, name);
}

void gl_texture::loadData(){
	// make sure to check to alpha value, png format need GL_RGBA (alpha channel) instead of GL_RGB
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 width,
                 height,
                 0,
                 channel == 3 ? GL_RGB : GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // default rules for texture wrapping and texture filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

int gl_texture::getUnit() const{
    return tex_unit - GL_TEXTURE0;
}

std::string gl_texture::getSamplerName() const{
	return sampler_name;
}

void gl_texture::assignSamplerName(aiTextureType type){
	switch(type){
		case aiTextureType_AMBIENT: sampler_name = std::string{"ambient" + std::to_string(ambient++)}; break;
		case aiTextureType_DIFFUSE: sampler_name = std::string{"diffuse" + std::to_string(diffuse++)}; break;
		case aiTextureType_SPECULAR: sampler_name = std::string{"specular" + std::to_string(specular++)}; break;
		case aiTextureType_EMISSIVE: sampler_name = std::string{"emission" + std::to_string(emission++)}; break;
		default: {
			std::cerr << "unknown aiTextureType" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
}
