#pragma once
#include "Renderer.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "Input.h"
#include "Shape.h"
#include "Sprite.h"
#include "TileMap.h"
#include "modelImporter.h"
#include "Camera.h"
#include "LightManager.h"

using namespace glm;

class ENGINE_API BaseGame
{
private:
	Renderer* _renderer;
	CollisionManager _collManager;
	bool _gameShouldClose;

protected:
	Window* _window;
	LightManager* _lightManager;
	modelImporter importer;

public:
	BaseGame();
	~BaseGame();
	
	void initBaseGame(int screenWidth, int screenHeight, const char* title);
	int engineLoop(float r, float g, float b, float a);

	virtual void initGame(Renderer* renderer) = 0;
	virtual void updateGame(CollisionManager collManager) = 0;
	virtual void destroyGame() = 0;

	void exitApplication();

	void activateFPSCamera(Camera* camera, float sensitivity);
	void deactivateFPSCamera();
};