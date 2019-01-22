#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>
#include "Renderer.h"

enum CameraRotate {
	YAW, PITCH,ROLL
};
class Camera {
private:
	glm::mat4 cameraTransform;
	glm::vec3 cameraPos;
	glm::vec3 lookAtVec;
	glm::vec3 up;
public:
	
	
	Camera(glm::vec3 cameraPos,glm::vec3 lookAtVec,glm::vec3 up);
	//this function takes in the direction you want to move the camera. It handles multiplying with minus 1.
	void Translate(glm::vec3 translationVec);
	void Rotate(float radianAngle, CameraRotate direction);
	void SetCamera(unsigned int program);
	void UpdateTransform(unsigned int program);
	void SetTransform(glm::vec3 cemaraPos,glm::vec3 lookAtVec,glm::vec3 up,unsigned int program);

};