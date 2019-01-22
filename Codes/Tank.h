#pragma once

#include "VertexArrayObject.h"
#include "glm/gtx/transform.hpp"
#include "Camera.h"
#include "TextureManager.h"
#include "Renderer.h"
#include "Bullet.h"
#include <thread>
#include <mutex>          
#include <chrono>
#include "Util.h"
#include "Static.h"
#include <thread>
class Bullet;
enum TankRotate {
	LEFT, RIGHT
};
class Tank {
public:
	Drawable* drawable;

	

	//helper data
	std::chrono::system_clock::time_point lastShoot;
	int program;
	float forwardThrottleSpeedHelper;
	float backwardThrottleSpeedHelper;
	float bodyRotationRightHelper;
	float bodyRotationLeftHelper;
	
	glm::vec3 boundingBoxForward;//the vectors that represent the very end of the tank
	glm::vec3 boundingBoxRight;

	//movement
	float forwardThrottleSpeed;
	float backwardThrottleSpeed;
	float bodyRotationSpeed;
	float barrelRotationSpeed;

	float bodyRotationRight;
	float bodyRotationLeft;
	

	//stats
	int bulletDamage;
	int health;
	float bulletLifeTime;
	float bulletSpeed;
	float shootInterval;

	glm::vec3 forwardVector;
	glm::vec3 backwardVector;


	std::mutex bulletListMutex;
	std::vector<Bullet> bullets;
	std::vector<std::chrono::system_clock::time_point> bulletCreateTimes;

	void Draw();
	//checks if a point is out of the world
	bool CheckOutOfWorld(glm::vec3 point,float worldSize);
	void CheckBoundaryCollision();

public:
	Tank();
	Tank(VertexArrayObject* vao, int program, float forwardSpeed, float backwardSpeed,float bulletSpeed,float bodyRotationSpeed,float shootInterval);

	glm::vec3 GetForwardVector();
	glm::vec3 GetBackwardVector();
	virtual void MoveForward();
	virtual void MoveBackward();


	//this returns local(initialized inside this function) rotation matrix in order for it to be used in TankPlayer child class for camera rotation
	virtual glm::mat4 Rotate(TankRotate direction);
	virtual void Shoot();
	virtual void Update();
	virtual void Update(Tank* player);
	
	glm::vec3 GetPos();

	
	

	virtual void SetPosition(glm::vec3 pos);

	//for debug purposes
	void PrintPos();

	friend class Bullet;

};

static bool CheckCollision2D(Tank* tank, Bullet* bullet) {
	glm::vec3 bulletForwardRight = bullet->GetPos() + bullet->boundingBoxForward + bullet->boundingBoxRight;
	glm::vec3 bulletForwardLeft = bullet->GetPos() + bullet->boundingBoxForward - bullet->boundingBoxRight;
	glm::vec3 bulletBackwardRight = bullet->GetPos() - bullet->boundingBoxForward + bullet->boundingBoxRight;
	glm::vec3 bulletBackwardLeft = bullet->GetPos() - bullet->boundingBoxForward - bullet->boundingBoxRight;


	glm::vec3 tankPos = tank->GetPos();
	glm::vec3 forwardRight = tankPos + tank->boundingBoxForward + tank->boundingBoxRight;
	glm::vec3 forwardLeft = tankPos + tank->boundingBoxForward - tank->boundingBoxRight;
	glm::vec3 backwardRight = tankPos - tank->boundingBoxForward + tank->boundingBoxRight;
	glm::vec3 backwardLeft = tankPos - tank->boundingBoxForward - tank->boundingBoxRight;

	glm::vec3 axis = tankPos - bullet->GetPos();
	float f1[4];
	float f2[4];
	f1[0] = glm::dot(bulletForwardRight, axis);
	f1[1] = glm::dot(bulletForwardLeft, axis);
	f1[2] = glm::dot(bulletBackwardRight, axis);
	f1[3] = glm::dot(bulletBackwardLeft, axis);
	f2[0] = glm::dot(forwardRight, axis);
	f2[1] = glm::dot(forwardLeft, axis);
	f2[2] = glm::dot(backwardRight, axis);
	f2[3] = glm::dot(backwardLeft, axis);

	float minLeft = 20000.0f;
	float maxLeft = -20000.0f;


	float minRight = 20000.0f;
	float maxRight = -20000.0f;

	for (int i = 0; i < 4; i++) {
		if (f1[i] < minLeft) {
			minLeft = f1[i];
		}
		if (f1[i] > maxLeft) {
			maxLeft = f1[i];
		}
		if (f2[i] < minRight) {
			minRight = f2[i];
		}
		if (f2[i] > maxRight) {
			maxRight = f2[i];
		}
	}
	if ((minLeft > minRight && minLeft < maxRight) ||
		(maxLeft > minRight && maxLeft < maxRight)) {
		return true;
	}
	return false;
}