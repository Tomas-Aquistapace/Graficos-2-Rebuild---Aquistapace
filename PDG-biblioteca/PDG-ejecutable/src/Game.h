#pragma once
#include "BaseGame.h"

class Game: BaseGame
{
private:
	Timer* _timer;
	Camera* _camera;

	float camSpeedX = 0.0f;
	float camSpeedY = 0.0f;
	float camSpeedZ = 0.0f;

public:
	Game();
	~Game();

	void play();
	void initGame(Renderer* renderer) override;
	void updateGame(CollisionManager collManager) override;
	void destroyGame() override;
};