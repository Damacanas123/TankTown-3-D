#pragma once
#include "Tank.h"
#include <random>
class Tank;
class TankAI : public Tank {
private:
	std::chrono::system_clock::time_point lastRandomGenerated;
	float directionUpdateInterval = 2.0f;
	int forwardBackwardDirection;
	int rotationDirection;
public:
	TankAI(VertexArrayObject* vao, int program, float forwardSpeed, float backwardSpeed, float bulletSpeed, float bodyRotationSpeed, float shootInterval);
	void Update(Tank* player);
};