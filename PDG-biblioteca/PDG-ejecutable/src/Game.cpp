#include "Game.h"

Game::Game()
{
	
}

Game ::~Game()
{
	
}

void Game::play()
{
	initBaseGame(1000, 500, "Aquistapace Engine");
	engineLoop(0.5f, 0.5f, 0.5f, 1.0f);
}

void Game::initGame(Renderer* renderer)
{
	_timer = new Timer();
	_timer->start();

	_lightA = new Lightning(renderer);
	_lightA->initializeSpot(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f), glm::radians(5.0f), 0.09f, 0.032f);
	_lightA->setActiveState(false);

	_lightB = new Lightning(renderer);
	_lightB->initializePoint(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f), 0.09f, 0.032f);
	_lightB->setActiveState(false);

	_lightC = new Lightning(renderer);
	_lightC->initializeDirectional(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(0.5f));
	_lightC->setActiveState(false);

	importer.loadModel("res/Models/Knuckles/Knuckles.fbx", false, renderer);
	importer.loadModel("res/Models/Gun_dae/Gun.dae", false, renderer);
	importer.loadModel("res/Models/backpack/backpack.obj", true, renderer);

	importer.models_Loaded[0]->setPosition(vec3(0.0f, 0.0f, -8.0f));
	importer.models_Loaded[0]->setRotation(vec3(270.0f, 0.0f, 0.0f));
	importer.models_Loaded[1]->setPosition(vec3(-5.0f, 0.0f, -5.0f));
	importer.models_Loaded[1]->setRotation(vec3(270.0f, 0.0f, 180.0f));
	importer.models_Loaded[1]->setScale(vec3(5.0f, 5.0f, 5.0f));
	importer.models_Loaded[2]->setPosition(vec3(5.0f, 0.0f, -5.0f));
	
	_camera = new Camera(renderer);
	_camera->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

	activateFPSCamera(_camera, 0.05f);
}

void Game::updateGame(CollisionManager collManager)
{
	// Input:
	if (Input::GetKeyDown(Keycode::ESCAPE))
	{
		exitApplication();
	}

	// Move Camera:
	if (Input::GetKey(Keycode::W))
	{
		camSpeedY = 1;
	}
	else if (Input::GetKey(Keycode::S))
	{
		camSpeedY = -1;
	}
	else
	{
		camSpeedY = 0;
	}
	if (Input::GetKey(Keycode::A))
	{
		camSpeedX = 1;
	}
	else if (Input::GetKey(Keycode::D))
	{
		camSpeedX = -1;
	}
	else
	{
		camSpeedX = 0;
	}

	// Turn Off/On the Lights:
	if (Input::GetKeyDown(Keycode::ALPHA1))
	{
		_lightA->setActiveState(!_lightA->getActiveState());
	}
	if (Input::GetKeyDown(Keycode::ALPHA2))
	{
		_lightB->setActiveState(!_lightB->getActiveState());
	}
	if (Input::GetKeyDown(Keycode::ALPHA3))
	{
		_lightC->setActiveState(!_lightC->getActiveState());
	}

	// Camera Movement:
	vec3 cameraMovement = vec3(camSpeedX, camSpeedY, camSpeedZ) * 3.0f * _timer->getDT();
	_camera->moveOnLocal(cameraMovement);

	_lightA->setPos(_camera->getPosition());
	_lightA->setDir(_camera->getFront());
	
	// Draw:
	importer.models_Loaded[0]->Draw();
	importer.models_Loaded[1]->Draw();
	importer.models_Loaded[2]->Draw();

	_lightA->draw();
	_lightB->draw();
	_lightC->draw();

	// Timer:
	_timer->updateTimer();
}

void Game::destroyGame()
{
	if (_timer) delete _timer;
	if (_camera) delete _camera;
	if (_lightA) delete _lightA;
	if (_lightB) delete _lightB;
	if (_lightC) delete _lightC;
}