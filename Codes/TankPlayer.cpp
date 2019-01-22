#include "TankPlayer.h"

TankPlayer::TankPlayer(VertexArrayObject* vao, int program, float forwardSpeed, float backwardSpeed, float bulletSpeed, float bodyRotationSpeed, float shootInterval) :
	Tank(vao,program,forwardSpeed,backwardSpeed,bulletSpeed,bodyRotationSpeed,shootInterval),
	cameraDistance(glm::vec3(0.0F, 6.0F, 5.0F)),
	cameraPos(this->drawable->GetTranslate() + this->cameraDistance),
	cameraLookAtVec(glm::vec3(0.0F, -12.0F, -5.5F)),
	cameraUp(glm::vec3(0.0F, 0.0f, 1.0F))
{
	this->camera = new Camera(cameraPos, cameraLookAtVec, cameraUp);
	this->camera->UpdateTransform(program);
}

Camera * TankPlayer::GetCamera()
{
	return this->camera;
}

void TankPlayer::MoveForward()
{
	Tank::MoveForward();
	this->camera->Translate(this->GetForwardVector());
	//dont forget to set camera transform in uniform
	this->camera->UpdateTransform(this->program);
}

void TankPlayer::MoveBackward()
{
	Tank::MoveBackward();
	this->camera->Translate(this->GetBackwardVector());
	//dont forget to set camera transform in uniform
	this->camera->UpdateTransform(this->program);
}





glm::mat4 TankPlayer::Rotate(TankRotate direction)
{
	glm::mat4 rotation = Tank::Rotate(direction);
	this->cameraLookAtVec = glm::vec3(rotation * glm::vec4(this->cameraLookAtVec, 0.0f));
	this->cameraPos = glm::vec3(this->drawable->GetTranslate() - glm::vec3(this->cameraLookAtVec.x / 2.0f, this->cameraLookAtVec.y / 2.0f, -5.0f));
	//dont forget to set camera transform in uniform
	this->camera->SetTransform(this->cameraPos, this->cameraLookAtVec, this->cameraUp, this->program);
	return rotation;
}



void TankPlayer::SetPosition(glm::vec3 pos) {
	this->drawable->SetTranslate(pos);
	this->cameraPos = this->GetPos() + this->cameraDistance;
	this->camera->SetTransform(this->cameraPos, this->cameraLookAtVec, this->cameraUp, this->program);
}

void TankPlayer::Update(std::vector<Tank*> AITanks)
{
	this->Draw();
	this->CheckBoundaryCollision();
	this->bulletListMutex.lock();
	for (int i = 0; i < this->bullets.size(); i++) {
		bullets[i].Move();
		bullets[i].Draw();
		bool collided = false;
		for (int j = 0;  !collided &&  j < AITanks.size(); j++) {
			if (CheckCollision2D(AITanks[j],&bullets[i])) {
				AITanks[j]->health -= this->bulletDamage;
				bullets.erase(bullets.begin() + i);
				bulletCreateTimes.erase(bulletCreateTimes.begin() + i);
				collided = true;
			}
		}
		if (!collided && Util::GetElapsedTime(bulletCreateTimes[i]) > this->bulletLifeTime) {
			bullets.erase(bullets.begin() + i);
			bulletCreateTimes.erase(bulletCreateTimes.begin() + i);
		}
	}
	this->bulletListMutex.unlock();
}

