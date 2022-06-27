#pragma once
#include "BaseGame.h"

class Game: BaseGame
{
private:
	Timer* _timer;

	Camera* _camera;
	Lightning* _lightA;
	Lightning* _lightB;
	Lightning* _lightC;

	float camSpeedX = 0.0f;
	float camSpeedY = 0.0f;
	float camSpeedZ = 0.0f;

	float camTargetX = 0.0f;
	float camTargetY = 0.0f;
	float camTargetZ = 0.0f;
	float camRotSpeed = 50.0f;

	bool isPressed[9];

public:
	Game();
	~Game();

	void play();
	void initGame(Renderer* renderer) override;
	void updateGame(CollisionManager collManager) override;
	void destroyGame() override;
};