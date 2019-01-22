#pragma once
#include "Drawable.h"
#include "VertexArrayObject.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "rectangular_prism.h"
#include "OuterSurface.h"
namespace Static{
	extern Drawable* drawableTankPlayer;
	extern Drawable* drawableTankAI;
	extern Drawable* drawableOuterSurface;
	extern std::vector<VertexArrayObject*> VAOS;
	extern VertexArrayObject* vaoTank;
	extern VertexArrayObject* vaoBullet;
	extern VertexArrayObject* vaoOuterSurface;
	extern Texture* textureTank;

	extern float worldSize;

	void LoadVertexArrayObjects();
	void LoadTextures();
	void LoadDrawables();
	void DeleteDrawables();
	void DeleteVAOS();

}
