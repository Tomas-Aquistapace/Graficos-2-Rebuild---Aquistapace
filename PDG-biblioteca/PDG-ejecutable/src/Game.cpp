#include "Game.h"

Game::Game()
{
	_timer = NULL;
	_sprite1 = NULL;
	_camera = NULL;
	_lightA = NULL;
	_lightB = NULL;
	_lightC = NULL;
}

Game ::~Game()
{
	if (_timer != NULL)
	{
		delete _timer;
		_timer = NULL;
	}
	if (_sprite1 != NULL)
	{
		delete _sprite1;
		_sprite1 = NULL;
	}
	if (_camera != NULL)
	{
		delete _camera;
		_camera = NULL;
	}
	if (_lightA != NULL)
	{
		delete _lightA;
		_lightA = NULL;
	}
	if (_lightB != NULL)
	{
		delete _lightB;
		_lightB = NULL;
	}
	if (_lightC != NULL)
	{
		delete _lightC;
		_lightC = NULL;
	}
}

void Game::play()
{
	initBaseGame(1000, 500, "Aquistapace Project");
	engineLoop(1, 0, 1, 1);
}

void Game::initGame(Renderer* renderer)
{
	// --------------------------
	// Timer:

	_timer = new Timer();
	_timer->start();

	// --------------------------
	// Lights:

	_lightA = new Lightning(renderer);
	_lightA->initializeSpot(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f), glm::radians(5.0f), 0.09f, 0.032f);
	_lightA->setActiveState(false);

	_lightB = new Lightning(renderer);
	_lightB->initializePoint(glm::vec3(0.0f, 5.0f, 5.0f), glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f), 0.09f, 0.032f);
	_lightB->setActiveState(false);

	_lightC = new Lightning(renderer);
	_lightC->initializeDirectional(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(0.5f));
	_lightC->setActiveState(false);

	// --------------------------
	// Models:

	importer.loadModel("res/Models/Cat/Cat_v1_l3.obj", false, renderer);
	importer.loadModel("res/Models/Gun_dae/Gun.dae", false, renderer);
	importer.loadModel("res/Models/backpack/backpack.obj", true, renderer);

	importer.models_Loaded[0]->setPosition(vec3(0.0f, -2.0f, -5.0f));
	importer.models_Loaded[0]->setRotation(vec3(270.0f, 0.0f, 0.0f));
	importer.models_Loaded[0]->setScale(vec3(0.05f, 0.05f, 0.05f));
	importer.models_Loaded[1]->setPosition(vec3(-1, 0, 0));
	importer.models_Loaded[1]->setRotation(vec3(270.0f, 0.0f, 45.0f));
	importer.models_Loaded[2]->setPosition(vec3(1, 0, 0));
	importer.models_Loaded[2]->setRotation(vec3(0, 0, -90));
	importer.models_Loaded[2]->setScale(vec3(0.25f, 0.25f, 0.25f));
	
	// --------------------------
	// Camera:

	_camera = new Camera(renderer);
	_camera->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	
	ActivateFPSCamera(_camera, 0.05f);

	// --------------------------
	// Sprites:
	
	//_sprite1 = new Sprite(renderer, "res/floor.png", true);
	//_sprite1->setPosition(vec3(0, 0, 0));
	//_sprite1->setScale(vec3(10, 0, 10));
}

void Game::updateGame(CollisionManager collManager)
{
	// --------------------------
	// Input:

	if (Input::GetKeyDown(Keycode::ESCAPE))
	{
		CloseApp();
	}

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

	// -------------------------
	// Camera:

	//vec3 cameraMovement = vec3(camSpeedX, camSpeedY, camSpeedZ) * 3.0f * _timer->getDT();
	//vec3 cameraRotation = vec3(camTargetX, camTargetY, camTargetZ) * camRotSpeed * _timer->getDT();
	//_camera->moveOnLocal(glm::vec3 (cameraMovement));
	//_camera->rotate(glm::vec3(cameraRotation));	

	// -------------------------
	// Draw:

	importer.models_Loaded[0]->Draw();
	importer.models_Loaded[1]->Draw();
	importer.models_Loaded[2]->Draw();

	_lightA->setPos(_camera->getPosition());
	_lightA->setDir(_camera->getFront());

	//_sprite1->draw();

	_timer->updateTimer();
}