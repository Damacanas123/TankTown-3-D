#include "OuterSurface.h"

namespace OuterSurface {
	const glm::vec3 vertices[] = {
		//floor
		glm::vec3(-100.0f, -100.0f, 0.0f),
		 glm::vec3(100.0f, -100.0f, 0.0f),
		 glm::vec3(100.0f,  100.0f, 0.0f),
		 glm::vec3(100.0f,  100.0f, 0.0f),
		glm::vec3(-100.0f,  100.0f, 0.0f),
		glm::vec3(-100.0f, -100.0f, 0.0f),

		glm::vec3(-100.0f, -100.0f,  199.0f),
		glm::vec3(100.0f, -100.0f,  199.0f),
		glm::vec3(100.0f,  100.0f,  199.0f),
		glm::vec3(100.0f,  100.0f,  199.0f),
		glm::vec3(-100.0f,  100.0f,  199.0f),
		glm::vec3(-100.0f, -100.0f,  199.0f),

		glm::vec3(-100.0f,  100.0f,  199.0f),
		glm::vec3(-100.0f,  100.0f, -0.0f),
		glm::vec3(-100.0f, -100.0f, -0.0f),
		glm::vec3(-100.0f, -100.0f, -0.0f),
		glm::vec3(-100.0f, -100.0f,  199.0f),
		glm::vec3(-100.0f,  100.0f,  199.0f),

		glm::vec3(100.0f,  100.0f,  199.0f),
		glm::vec3(100.0f,  100.0f, -0.0f),
		glm::vec3(100.0f, -100.0f, -0.0f),
		glm::vec3(100.0f, -100.0f, -0.0f),
		glm::vec3(100.0f, -100.0f,  199.0f),
		glm::vec3(100.0f,  100.0f,  199.0f),

		glm::vec3(-100.0f, -100.0f, -0.0f),
		glm::vec3(100.0f, -100.0f, -0.0f),
		glm::vec3(100.0f, -100.0f,  199.0f),
		glm::vec3(100.0f, -100.0f,  199.0f),
		glm::vec3(-100.0f, -100.0f,  199.0f),
		glm::vec3(-100.0f, -100.0f, -0.0f),

		glm::vec3(-100.0f,  100.0f, -0.0f),
		glm::vec3(100.0f,  100.0f, -0.0f),
		glm::vec3(100.0f,  100.0f,  199.0f),
		glm::vec3(100.0f,  100.0f,  199.0f),
		glm::vec3(-100.0f,  100.0f,  199.0f),
		glm::vec3(-100.0f,  100.0f, -0.0f),
	};

	const glm::vec3 normals[] = {
		 glm::vec3(0.0f,  0.0f, 1.0f),
		 glm::vec3(0.0f,  0.0f, 1.0f),
		 glm::vec3(0.0f,  0.0f, 1.0f),
		 glm::vec3(0.0f,  0.0f, 1.0f),
		 glm::vec3(0.0f,  0.0f, 1.0f),
		 glm::vec3(0.0f,  0.0f, 1.0f),

		 glm::vec3(0.0f,  0.0f, -1.0f),
		 glm::vec3(0.0f,  0.0f, -1.0f),
		 glm::vec3(0.0f,  0.0f, -1.0f),
		glm::vec3(0.0f,  0.0f, -1.0f),
		glm::vec3(0.0f,  0.0f, -1.0f),
		glm::vec3(0.0f,  0.0f, -1.0f),

		glm::vec3(1.0f,  0.0f,  0.0f),
		glm::vec3(1.0f,  0.0f,  0.0f),
		glm::vec3(1.0f,  0.0f,  0.0f),
		glm::vec3(1.0f,  0.0f,  0.0f),
		glm::vec3(1.0f,  0.0f,  0.0f),
		glm::vec3(1.0f,  0.0f,  0.0f),

		glm::vec3(-1.0f,  0.0f,  0.0f),
		glm::vec3(-1.0f,  0.0f,  0.0f),
		glm::vec3(-1.0f,  0.0f,  0.0f),
		glm::vec3(-1.0f,  0.0f,  0.0f),
		glm::vec3(-1.0f,  0.0f,  0.0f),
		glm::vec3(-1.0f,  0.0f,  0.0f),

		glm::vec3(0.0f, 1.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f),
		glm::vec3(0.0f, 1.0f,  0.0f),

		glm::vec3(0.0f,  -1.0f,  0.0f),
		glm::vec3(0.0f,  -1.0f,  0.0f),
		glm::vec3(0.0f,  -1.0f,  0.0f),
		glm::vec3(0.0f,  -1.0f,  0.0f),
		glm::vec3(0.0f,  -1.0f,  0.0f),
		glm::vec3(0.0f,  -1.0f,  0.0f),
	};

	const glm::vec2 uv[] = {
		glm::vec2(0.0f,1.0f),
		glm::vec2(1.0f,1.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(0.0f,0.0f),
		glm::vec2(0.0f,1.0f),

		glm::vec2(0.0f,1.0f),
		glm::vec2(1.0f,1.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(0.0f,0.0f),
		glm::vec2(0.0f,1.0f),

		glm::vec2(0.0f,1.0f),
		glm::vec2(1.0f,1.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(0.0f,0.0f),
		glm::vec2(0.0f,1.0f),

		glm::vec2(0.0f,1.0f),
		glm::vec2(1.0f,1.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(0.0f,0.0f),
		glm::vec2(0.0f,1.0f),

		glm::vec2(0.0f,1.0f),
		glm::vec2(1.0f,1.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(0.0f,0.0f),
		glm::vec2(0.0f,1.0f),

		glm::vec2(0.0f,1.0f),
		glm::vec2(1.0f,1.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(1.0f,0.0f),
		glm::vec2(0.0f,0.0f),
		glm::vec2(0.0f,1.0f),
	};
	const GLuint element_count = 36;
	const GLuint size = 36 * sizeof(glm::vec3);
}