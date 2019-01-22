#pragma once
#include "Tank.h"

class TankPlayer : public Tank {
private:
	Camera* camera;

	//distance of camera from tank as a vector
	glm::vec3 cameraDistance;
	glm::vec3 cameraPos;
	glm::vec3 cameraLookAtVec;
	glm::vec3 cameraUp;
public:
	TankPlayer(VertexArrayObject* vao, int program, float forwardSpeed, float backwardSpeed, float bulletSpeed, float bodyRotationSpeed, float shootInterval);

	Camera* GetCamera();


	//overridden functions
	void MoveForward();
	void MoveBackward();
	glm::mat4 Rotate(TankRotate direction);
	void SetPosition(glm::vec3 pos);
	void Update(std::vector<Tank*> AITanks);
};