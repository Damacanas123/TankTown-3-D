#pragma once

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

#include "Texture.h"

class TextureManager
{
public:
	static Texture* loadPNG(const char* filename);
	static std::unordered_map<const char*, const Texture> textures;
	~TextureManager();

private:
	TextureManager();
};

