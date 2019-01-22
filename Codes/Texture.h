#pragma once

#include <vector>

#include "GL/glew.h"
#include "Renderer.h"
class Texture
{
public:
	unsigned int gl_texture;
	unsigned long width, height;

	Texture();
	Texture(unsigned long width, unsigned long height, const std::vector<unsigned char>& pixels);
	~Texture();
};

