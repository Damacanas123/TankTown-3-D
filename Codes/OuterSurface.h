#pragma once

#include <GL\glew.h>
#include <assert.h>

#include "config.h"
#include <glm/glm.hpp>

namespace OuterSurface {
	extern const glm::vec3 vertices[];
	extern const glm::vec3 normals[];
	extern const glm::vec2 uv[];
	extern const GLuint element_count;
	extern const GLuint size;
}