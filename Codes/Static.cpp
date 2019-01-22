#include "Static.h"

namespace Static{
	std::vector<Drawable*> drawables;
	Drawable* drawableTankPlayer;
	Drawable* drawableTankAI;
	Drawable* drawableOuterSurface;
	std::vector<VertexArrayObject*> VAOS;
	VertexArrayObject* vaoTank;
	VertexArrayObject* vaoBullet;
	VertexArrayObject* vaoOuterSurface;
	Texture* textureTank;
	Texture* textureBullet;
	Texture* textureAsphalt;

	float worldSize = 100.0f;
	void LoadVertexArrayObjects() {
		vaoTank = MeshManager::loadOBJ("tank_top.obj");
		vaoTank->SetTexture(textureTank);
		VAOS.push_back(vaoTank);

		vaoBullet = new VertexArrayObject(rectangular_prism::element_count);
		vaoBullet->AddPositionBuffer(&rectangular_prism::vertices[0]);
		vaoBullet->AddNormalBuffer(&rectangular_prism::normals[0]);
		VAOS.push_back(vaoBullet);

		vaoOuterSurface = new VertexArrayObject(OuterSurface::element_count);
		vaoOuterSurface->AddPositionBuffer(&OuterSurface::vertices[0]);
		vaoOuterSurface->AddNormalBuffer(&OuterSurface::normals[0]);
		vaoOuterSurface->AddTextureBuffer(&OuterSurface::uv[0]);
		vaoOuterSurface->SetTexture(textureAsphalt);
		VAOS.push_back(vaoOuterSurface);
		
	}
	void LoadDrawables() {
		drawableOuterSurface = new Drawable(Static::vaoOuterSurface, glm::vec3(0.0f, 0.0f, 0.0f));
		drawables.push_back(drawableTankPlayer);
		drawables.push_back(drawableTankAI);
		drawables.push_back(drawableOuterSurface);
	}

	void LoadTextures() {
		textureTank = TextureManager::loadPNG("tankTexture.png");
		textureAsphalt = TextureManager::loadPNG("painting.png");
	}
	void DeleteDrawables() {
		for (int i = 0; i < drawables.size(); i++) {
			delete drawables[i];
		}
	}
	void DeleteVAOS() {
		for (int i = 0; i < VAOS.size(); i++) {
			delete VAOS[i];
		}
	}
}
