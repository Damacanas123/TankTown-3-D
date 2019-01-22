#pragma once

#include "Static.h"
#include "glm/gtx/transform.hpp"
class Bullet {
public:
	float lifeTime;
	int damage;
	Drawable* drawable;
	unsigned int program;
	glm::vec3 initialPos;
	glm::vec3 forwardVec;
	float zRotation;

	glm::vec3 boundingBoxForward;
	glm::vec3 boundingBoxRight;
public:
	Bullet();
	Bullet(Drawable* drawable,unsigned int program,float lifeTime,int damage, glm::vec3 initialPos, glm::vec3 forwardVec,float zRotation,float speed);
	void Draw();
	void Move();

	glm::vec3 GetPos();


};