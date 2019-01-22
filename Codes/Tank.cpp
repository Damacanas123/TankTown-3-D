#include "Tank.h"
#include <iostream>


void Tank::Draw()
{
	this->drawable->Draw(this->program);
}

bool Tank::CheckOutOfWorld(glm::vec3 point,float worldSize)
{
	return (point.x > Static::worldSize ||
		point.x < -Static::worldSize ||
		point.y > Static::worldSize ||
		point.y < -Static::worldSize);
	
}

void Tank::CheckBoundaryCollision()
{
	glm::vec3 pos = this->GetPos();
	glm::vec3 forwardRight = pos + this->boundingBoxForward + this->boundingBoxRight;
	glm::vec3 forwardLeft = pos + this->boundingBoxForward - this->boundingBoxRight;
	glm::vec3 backwardRight = pos - this->boundingBoxForward + this->boundingBoxRight;
	glm::vec3 backwardLeft = pos - this->boundingBoxForward - this->boundingBoxRight;
	if (this->CheckOutOfWorld(forwardRight,Static::worldSize)) {
		forwardThrottleSpeed = 0.0f;
		backwardThrottleSpeed = backwardThrottleSpeedHelper;
		bodyRotationRight = 0.0f;
		bodyRotationLeft = bodyRotationLeftHelper;
	}
	else if (this->CheckOutOfWorld(forwardLeft, Static::worldSize)) {
		forwardThrottleSpeed = 0.0f;
		backwardThrottleSpeed = backwardThrottleSpeedHelper;
		bodyRotationRight = bodyRotationRightHelper;
		bodyRotationLeft = 0.0f;
	}
	else if (this->CheckOutOfWorld(backwardRight, Static::worldSize)) {
		forwardThrottleSpeed = forwardThrottleSpeedHelper;
		backwardThrottleSpeed = 0.0f;
		bodyRotationRight = bodyRotationRightHelper;
		bodyRotationLeft = 0.0f;
	}
	else if (this->CheckOutOfWorld(backwardLeft, Static::worldSize)) {
		forwardThrottleSpeed = forwardThrottleSpeedHelper;
		backwardThrottleSpeed = 0.0f;
		bodyRotationRight = 0.0f;
		bodyRotationLeft = bodyRotationLeftHelper;
	}
	else {
		forwardThrottleSpeed = forwardThrottleSpeedHelper;
		backwardThrottleSpeed = backwardThrottleSpeedHelper;
		bodyRotationRight = bodyRotationRightHelper;
		bodyRotationLeft = bodyRotationLeftHelper;
	}
}



Tank::Tank()
{
}

Tank::Tank(VertexArrayObject* vao, int program,float forwardSpeed,float backwardSpeed,float bulletSpeed,float bodyRotationSpeed,float shootInterval) :
	drawable(new Drawable(vao, glm::vec3(0.0f, 15.0f, 0.0f))),
	program(program),
	forwardThrottleSpeed(forwardSpeed),
	backwardThrottleSpeed(backwardSpeed),
	forwardThrottleSpeedHelper(forwardSpeed),
	backwardThrottleSpeedHelper(backwardSpeed),
	bodyRotationSpeed(bodyRotationSpeed),
	barrelRotationSpeed(0.2f),
	bulletLifeTime(2.0f),
	forwardVector(glm::vec3(0.027f,-1.0f,0.0f)),
	backwardVector(-glm::vec3(0.027f,-1.0f,0.0f)),
	bulletSpeed(bulletSpeed),
	shootInterval(shootInterval),
	lastShoot(Util::GetCurrentTime()),
	boundingBoxForward(7.0f * glm::vec3(0.027f, -1.0f, 0.0f)),
	boundingBoxRight(1.6f * (glm::vec3(glm::rotate(-glm::pi<float>()/2, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(glm::vec3(0.027f, -1.0f, 0.0f),0.0f)))),
	bodyRotationLeft(bodyRotationSpeed),
	bodyRotationRight(-bodyRotationSpeed),
	bodyRotationLeftHelper(bodyRotationSpeed),
	bodyRotationRightHelper(-bodyRotationSpeed),
	bulletDamage(1),
	health(40)
{
	
}

glm::vec3 Tank::GetForwardVector()
{
	return this->forwardVector * this->forwardThrottleSpeed;
}

glm::vec3 Tank::GetBackwardVector()
{
	return this->backwardVector * this->backwardThrottleSpeed;
}

void Tank::MoveForward()
{
	this->drawable->Translate(this->GetForwardVector());
}

void Tank::MoveBackward()
{
	this->drawable->Translate(this->GetBackwardVector());
}





glm::mat4 Tank::Rotate(TankRotate direction)
{
	glm::mat4 rotation;
	if (direction == TankRotate::RIGHT) {
		this->drawable->rotate(this->bodyRotationRight, axis::z);
		rotation = glm::rotate(this->bodyRotationRight, glm::vec3(0.0f, 0.0f, 1.0f));
		
		
	}
	else if (direction == TankRotate::LEFT) {
		this->drawable->rotate(this->bodyRotationLeft, axis::z);
		rotation = glm::rotate(this->bodyRotationLeft, glm::vec3(0.0f, 0.0f, 1.0f));
		
	}
	else {
		throw std::invalid_argument("TankRotate enum type is invalid.");
	}
	this->forwardVector = glm::vec3(rotation * glm::vec4(this->forwardVector, 0));
	this->backwardVector = glm::vec3(rotation * glm::vec4(this->backwardVector, 0));
	this->boundingBoxForward = glm::vec3(rotation * glm::vec4(this->boundingBoxForward, 0));
	this->boundingBoxRight = glm::vec3(rotation * glm::vec4(this->boundingBoxRight, 0));
	return rotation;
}

void Tank::Shoot()
{
	if (Util::GetElapsedTime(this->lastShoot) > this->shootInterval) {
		Drawable* drawableBullet = new Drawable(Static::vaoBullet, glm::vec3(0.0f, 0.0f, 0.0f));
		glm::vec3 bulletAdjustmentVec = glm::rotate(this->drawable->GetRotation(axis::z), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(glm::vec3(0.35f, -6.0f, 1.5f), 0.0f);
		Bullet bullet(
			drawableBullet,
			this->program,
			this->bulletLifeTime,
			this->bulletDamage,
			this->drawable->GetTranslate() + bulletAdjustmentVec,
			this->forwardVector,
			this->drawable->GetRotation(axis::z),
			this->bulletSpeed);
		this->bulletListMutex.lock();
		this->bullets.push_back(bullet);
		this->bulletCreateTimes.push_back(Util::GetCurrentTime());
		this->bulletListMutex.unlock();
		this->lastShoot = Util::GetCurrentTime();
	}
	
}

void Tank::Update()
{
	
	this->Draw();
	this->CheckBoundaryCollision();
	this->bulletListMutex.lock();
	for (int i = 0; i < this->bullets.size(); i++) {
		bullets[i].Move();
		bullets[i].Draw();
		if (Util::GetElapsedTime(bulletCreateTimes[i]) > this->bulletLifeTime) {
			bullets.erase(bullets.begin() + i);
			bulletCreateTimes.erase(bulletCreateTimes.begin() + i);
		}
	}
	this->bulletListMutex.unlock();
}

void Tank::Update(Tank * player)
{

}




glm::vec3 Tank::GetPos() {
	return this->drawable->GetTranslate();
}

void Tank::SetPosition(glm::vec3 pos) {
	this->drawable->SetTranslate(pos);
}

void Tank::PrintPos() {
	glm::vec3 tankPos = this->GetPos();
	std::cout << tankPos.x << "," << tankPos.y << "," << tankPos.z << std::endl;
}




