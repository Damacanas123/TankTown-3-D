#include "VertexArrayObject.h"
#include "Renderer.h"
VertexArrayObject::VertexArrayObject()
{
}
VertexArrayObject::VertexArrayObject(unsigned int vertexCount):vertexCount(vertexCount)
{
	GLCall(glGenVertexArrays(1, &this->vao));
	Bind();
}

VertexArrayObject::~VertexArrayObject()
{
	this->UnBind();
	GLCall(glDeleteVertexArrays(1, &this->vao));
}

void VertexArrayObject::AddPositionBuffer(const glm::vec3 * positions)
{
	GLCall(glGenBuffers(1, &this->positionArray));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER,this->positionArray));
	GLCall(glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(glm::vec3),positions,GL_STATIC_DRAW));
	GLCall(glEnableVertexAttribArray(ATTR_LOCATION::POSITION));
	GLCall(glVertexAttribPointer(ATTR_LOCATION::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0));
}

void VertexArrayObject::AddNormalBuffer(const glm::vec3 * normals)
{
	GLCall(glGenBuffers(1, &this->normalArray));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->normalArray));
	GLCall(glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(glm::vec3), normals, GL_STATIC_DRAW));
	GLCall(glEnableVertexAttribArray(ATTR_LOCATION::NORMAL));
	GLCall(glVertexAttribPointer(ATTR_LOCATION::NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0));
}

void VertexArrayObject::AddTextureBuffer(const glm::vec2 * uv)
{
	GLCall(glGenBuffers(1, &this->textureArray));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->textureArray));
	GLCall(glBufferData(GL_ARRAY_BUFFER, this->vertexCount * sizeof(glm::vec2), uv, GL_STATIC_DRAW));
	GLCall(glEnableVertexAttribArray(ATTR_LOCATION::UV));
	GLCall(glVertexAttribPointer(ATTR_LOCATION::UV, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), 0));
}

void VertexArrayObject::Bind()
{
	GLCall(glBindVertexArray(this->vao));
}

void VertexArrayObject::UnBind()
{
	GLCall(glBindVertexArray(0));
}

void VertexArrayObject::Draw()
{
	if (this->texture != nullptr) {
		GLCall(glBindTexture(GL_TEXTURE_2D, texture->gl_texture));
	}
	
	GLCall(glDrawArrays(GL_TRIANGLES, 0, this->vertexCount));
}

void VertexArrayObject::SetTexture(Texture* texture)
{
	this->texture = texture;
}
