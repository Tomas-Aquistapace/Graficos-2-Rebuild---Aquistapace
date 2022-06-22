#pragma once
#include "BaseGame.h"
class Game: BaseGame
{
private:
	Timer* _timer;

	Sprite* _sprite1;
	Camera* _camera;
	Lightning* _lightA;
	Lightning* _lightB;
	Lightning* _lightC;

public:
	Game();
	~Game();
	void play();
	void initGame(Renderer* renderer) override;
	void updateGame(CollisionManager collManager) override;
};