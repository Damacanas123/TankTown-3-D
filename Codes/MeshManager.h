#define _CRT_SECURE_NO_WARNINGS

#pragma once

#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "VertexArrayObject.h"
#include "glm/glm.hpp"

struct ModelData {};

class MeshManager {
public:
	static VertexArrayObject* loadOBJ(const char* file_name);
	~MeshManager();

private:
	MeshManager();
	static void decodeOBJ(
		const char * path,
		std::vector<glm::vec3>& out_vertices,
		std::vector<glm::vec3>& out_normals,
		std::vector<glm::vec2>& out_uvs);
};
