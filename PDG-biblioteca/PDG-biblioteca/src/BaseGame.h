#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "Input.h"
#include "Shape.h"
#include "Sprite.h"
#include "TileMap.h"
#include "modelImporter.h"
#include "Camera.h"
#include "Lightning.h"

class SABASAENGINE_API BaseGame
{
private:
	Renderer* _renderer;
	CollisionManager collManager;
	bool gameShouldClose;

protected:
	Window* _window;

public:
	modelImporter importer;
	BaseGame();
	~BaseGame();
	
	void initBaseGame(int screenWidth, int screenHeight, const char* title);
	int engineLoop(float r, float g, float b, float a);

	void CloseApp();
	void ActivateFPSCamera(Camera* camera, float sensitivity);
	void DeactivateFPSCamera();

	virtual void initGame(Renderer* renderer) = 0;
	virtual void updateGame(CollisionManager collManager) = 0;
	//virtual void destroyGame() = 0;
};