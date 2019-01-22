#include "TankAI.h"

TankAI::TankAI(VertexArrayObject * vao, int program, float forwardSpeed, float backwardSpeed, float bulletSpeed, float bodyRotationSpeed, float shootInterval):
	Tank(vao,program,forwardSpeed,backwardSpeed,bulletSpeed,bodyRotationSpeed,shootInterval)
{
	this->lastRandomGenerated = Util::GetCurrentTime();
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1,3);
	auto binaryRandGenerator = std::bind(distribution, generator);
	this->forwardBackwardDirection = binaryRandGenerator();
	this->rotationDirection = binaryRandGenerator();
}

void TankAI::Update(Tank* player)
{
	this->Draw();
	this->CheckBoundaryCollision();
	if (Util::GetElapsedTime(lastRandomGenerated) > this->directionUpdateInterval) {
		this->lastRandomGenerated = Util::GetCurrentTime();
		std::default_random_engine generator;
		generator.seed((int)std::chrono::time_point_cast<std::chrono::milliseconds>(Util::GetCurrentTime()).time_since_epoch().count());
		std::uniform_int_distribution<int> distribution(1,3);
		auto binaryRandGenerator = std::bind(distribution, generator);
		this->forwardBackwardDirection = binaryRandGenerator();
		this->rotationDirection = binaryRandGenerator();
	}
	
	if (this->forwardBackwardDirection == 1) {
		this->MoveBackward();
	}
	else {
		this->MoveForward();
	}
	if (rotationDirection == 1) {
		this->Rotate(TankRotate::LEFT);
	}
	else if(rotationDirection == 2){
		this->Rotate(TankRotate::RIGHT);
	}

	//shooting logic
	glm::vec3 playerPos = player->GetPos();
	glm::vec3 selfPos = this->GetPos();
	glm::vec3 axis = playerPos - selfPos;
	axis = axis / glm::length(axis);
	glm::vec3 normalizedForwardVec = this->forwardVector / glm::length(this->forwardVector);
	if (dot(axis, normalizedForwardVec) > 0.99) {
		this->Shoot();
	}
	this->bulletListMutex.lock();
	for (int i = 0; i < this->bullets.size(); i++) {
		bullets[i].Move();
		bullets[i].Draw();
		bool collided = false;
		if (CheckCollision2D(player, &bullets[i])) {
			player->health -= this->bulletDamage;
			bullets.erase(bullets.begin() + i);
			bulletCreateTimes.erase(bulletCreateTimes.begin() + i);
			collided = true;
			continue;
		}
		
		if (!collided && Util::GetElapsedTime(bulletCreateTimes[i]) > this->bulletLifeTime) {
			bullets.erase(bullets.begin() + i);
			bulletCreateTimes.erase(bulletCreateTimes.begin() + i);
		}
	}
	this->bulletListMutex.unlock();
}
