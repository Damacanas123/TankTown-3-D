#include "Camera.h"
#include <iostream>
Camera::Camera(glm::vec3 cameraPos, glm::vec3 lookAtVec, glm::vec3 up):
	cameraPos(cameraPos),
	lookAtVec(lookAtVec),
	up(up)
{

}

void Camera::Translate(glm::vec3 translationVec)
{
	this->cameraPos += translationVec;
}

void Camera::Rotate(float radianAngle, CameraRotate direction)
{
	glm::mat4 rotation;
	if (direction == CameraRotate::YAW) {
		rotation = glm::rotate(radianAngle, this->up);
		this->lookAtVec = glm::vec3(rotation * glm::vec4(this->lookAtVec, 0));
	}
	else if (direction == CameraRotate::PITCH) {
		rotation = glm::rotate(radianAngle, glm::cross(this->up, this->lookAtVec));
		this->lookAtVec = glm::vec3(rotation * glm::vec4(this->lookAtVec, 0));
		this->up = glm::vec3(rotation * glm::vec4(this->up, 0));
	}
	else if (direction == CameraRotate::ROLL) {
		rotation = glm::rotate(radianAngle, this->lookAtVec);
		this->up = glm::vec3(rotation * glm::vec4(this->up, 0));
	}
	else {
		throw std::invalid_argument("CameraRotate enum invalid arguement");
	}

}

void Camera::SetCamera(unsigned int program)
{
	GLCall(glUniformMatrix4fv(glGetUniformLocation(program, "uCamera"), 1, GL_FALSE, &this->cameraTransform[0][0]));
}

void Camera::UpdateTransform(unsigned int program)
{
	this->cameraTransform = glm::lookAt(this->cameraPos, this->cameraPos + this->lookAtVec, this->up);
	this->SetCamera(program);
}

void Camera::SetTransform(glm::vec3 cemaraPos, glm::vec3 lookAtVec, glm::vec3 up, unsigned int program)
{
	this->cameraPos = cemaraPos;
	this->lookAtVec = lookAtVec;
	this->up = up;
	this->UpdateTransform(program);
}
