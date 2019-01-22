#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "config.h"
#include "Texture.h"

class VertexArrayObject {
private:
	unsigned int vao;
	unsigned int positionArray, normalArray, textureArray;
	unsigned int vertexCount;
	Texture* texture;
public:
	VertexArrayObject();
	VertexArrayObject(unsigned int vertexCount);
	~VertexArrayObject();
	void AddPositionBuffer(const glm::vec3* positions);
	void AddNormalBuffer(const glm::vec3* normals);
	void AddTextureBuffer(const glm::vec2* uv);
	void Bind();
	void UnBind();
	void Draw();
	void SetTexture(Texture* texture);

};