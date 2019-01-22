#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(Drawable * drawable, unsigned int program, float lifeTime, int damage,glm::vec3 initialPos,glm::vec3 forwardVec,float zRotation,float speed):
	drawable(drawable),
	program(program),
	lifeTime(lifeTime),
	damage(damage),
	initialPos(initialPos),
	forwardVec(forwardVec*speed),
	zRotation(zRotation),
	boundingBoxForward(0.5f * forwardVec/glm::length(forwardVec)),
	boundingBoxRight(0.5f * (glm::vec3(glm::rotate(-glm::pi<float>() / 2, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(forwardVec, 0.0f))) / glm::length(forwardVec))
{
	this->drawable->Translate(initialPos);
	this->drawable->rotate(zRotation, axis::z);
}

void Bullet::Draw()
{
	this->drawable->Draw(this->program);
}

void Bullet::Move()
{
	this->drawable->Translate(this->forwardVec);
}

glm::vec3 Bullet::GetPos()
{
	return this->drawable->GetTranslate();
}



