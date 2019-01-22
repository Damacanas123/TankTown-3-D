#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "VertexArrayObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"
#include "Renderer.h"
enum axis{
	x,y,z
};
const static float twoPI = 2 * glm::pi<float>();
class Drawable {
private:
	VertexArrayObject* vertexArrayObject;
	//this vector is the needed vector to translate the model to origin if the model is not loaded around the origin. 
	glm::vec3 toOriginTranslation;
	glm::vec3 translation;
	glm::vec3 scaleVec;
	float xRotate;
	float yRotate;
	float zRotate;
public:
	Drawable(VertexArrayObject* vertexArrayObject,glm::vec3 backTranslation);
	void Draw(unsigned int program);
	void rotate(glm::f32 randianAngle, axis eksen);
	void Translate(glm::vec3 translateVec);
	void Scale(glm::vec3 scaleVec);
	glm::vec3 GetTranslate();
	float GetRotation(axis eksen);
	glm::vec3 GetScale();
	glm::mat4 GetTransform();
	void SetTranslate(glm::vec3 pos);
	void SetRotate(float rad, axis axis);

};