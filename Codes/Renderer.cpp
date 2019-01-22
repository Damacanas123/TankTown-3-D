#pragma once
#include "Renderer.h"
#include <iostream>
void GLClearError() {
	while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line) {
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL error]" << "(" << std::hex << error << "): " << function << " in " << file << " at line : " << std::dec << line << std::endl;
		return false;
	}
	return true;
}