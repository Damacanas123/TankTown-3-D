#include "Drawable.h"
#include <iostream>

Drawable::Drawable(VertexArrayObject* vertexArrayObject,glm::vec3 backTranslation):vertexArrayObject(vertexArrayObject),toOriginTranslation(backTranslation)
{
	this->translation = glm::vec3(0.0f);
	this->xRotate = 0.0f;
	this->yRotate = 0.0f;
	this->zRotate = 0.0f;
	this->scaleVec = glm::vec3(1.0f);
}

void Drawable::Draw(unsigned int program)
{
	GLCall(glUniformMatrix4fv(glGetUniformLocation(program, "uTransform"), 1, GL_FALSE, &this->GetTransform()[0][0]));
	this->vertexArrayObject->Bind();
	this->vertexArrayObject->Draw();
	this->vertexArrayObject->UnBind();
}

void Drawable::rotate(glm::f32 radianAngle, axis eksen)
{
	if (eksen == axis::x) {
		xRotate = fmod((xRotate + radianAngle), twoPI);
	}
	else if (eksen == axis::y) {
		yRotate = fmod((yRotate + radianAngle), twoPI);
	}
	else if(eksen == axis::z){
		zRotate = fmod((zRotate + radianAngle), twoPI);
	}
	else {
		throw std::invalid_argument("Axis enum type is invalid.");
	}
}

void Drawable::Translate(glm::vec3 translateVec)
{
	this->translation += translateVec;
}

void Drawable::Scale(glm::vec3 scaleVec)
{
	this->scaleVec += scaleVec;
}

glm::vec3 Drawable::GetTranslate()
{
	return this->translation + this->toOriginTranslation;
}

float Drawable::GetRotation(axis eksen)
{
	if (eksen == axis::x) {
		return xRotate;
	}
	else if (eksen == axis::y) {
		return yRotate;
	}
	else if (eksen == axis::z) {
		return zRotate;
	}
	else {
		throw std::invalid_argument("Axis enum type is invalid.");
	}
}

glm::vec3 Drawable::GetScale()
{
	return this->scaleVec;
}

glm::mat4 Drawable::GetTransform()
{
	glm::mat4 transformation(1.0f);
	transformation = glm::scale(transformation, this->scaleVec);
	transformation = glm::translate(transformation, this->translation);
	transformation = glm::translate(transformation, this->toOriginTranslation);
	transformation = glm::rotate(transformation, xRotate, glm::vec3(1.0f, 0.0f, 0.0f));
	transformation = glm::rotate(transformation, yRotate, glm::vec3(0.0f, 1.0f, 0.0f));
	transformation = glm::rotate(transformation, zRotate, glm::vec3(0.0f, 0.0f, 1.0f));
	transformation = glm::translate(transformation,-this->toOriginTranslation);
	
	
	return transformation;
}

void Drawable::SetTranslate(glm::vec3 pos)
{
	this->translation = pos;
}

void Drawable::SetRotate(float rad, axis axis) {
	if (axis == axis::x) {
		this->xRotate = rad;
	}
	else if (axis == axis::y) {
		this->yRotate = rad;
	}
	else if (axis == axis::z) {
		this->zRotate = rad;
	}
	else {
		throw std::invalid_argument("Axis enum type is invalid.");
	}
}


