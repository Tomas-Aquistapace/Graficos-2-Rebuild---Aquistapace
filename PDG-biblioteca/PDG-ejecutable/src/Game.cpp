#include "Game.h"

Game::Game()
{
	_timer = NULL;
	_camera = NULL;
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

	_lightManager->addDirectional(renderer, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(0.5f));
	_lightManager->getDirectionalLight(0)->setActiveState(false);

	_lightManager->addPoints(renderer, vec3(0.0f, 5.0f, 5.0f), vec3(0.1f, 0.1f, 0.1f), vec3(0.5f, 0.5f, 0.5f), vec3(1.0f), 0.09f, 0.032f);
	_lightManager->getPointLight(0)->setActiveState(false);

	_lightManager->addSpots(renderer, vec3(0), vec3(0), vec3(0.1f, 0.1f, 0.1f), vec3(0.5f, 0.5f, 0.5f), vec3(1.0f), radians(12.5f), 0.3f, 0.1f);
	_lightManager->getSpotLight(0)->setActiveState(false);

	importer.loadModel("res/Models/Knuckles/Knuckles.fbx", false, renderer);
	importer.loadModel("res/Models/manMesh/FinalBaseMesh.obj", false, renderer);
	importer.loadModel("res/Models/backpack/backpack.obj", true, renderer);

	importer.models_Loaded[0]->setPosition(vec3(0.0f, 0.0f, -8.0f));
	importer.models_Loaded[0]->setRotation(vec3(270.0f, 0.0f, 0.0f));
	importer.models_Loaded[1]->setPosition(vec3(0.0f, -10.0f, 5.0f));
	importer.models_Loaded[1]->setRotation(vec3(270.0f, 0.0f, 0.0f));
	importer.models_Loaded[1]->setScale(vec3(2.0f, 2.0f, 2.0f));
	importer.models_Loaded[2]->setPosition(vec3(5.0f, 0.0f, -5.0f));

	_camera = new Camera(renderer);
	_camera->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

	activateFPSCamera(_camera, 0.05f);
}

//	Separar el modelImp para que no funcione como un manager 
//	Cambiar el color de las luces
//	Permitir que se cambien las trans con las teclas

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
		_lightManager->getDirectionalLight(0)->setActiveState(!_lightManager->getDirectionalLight(0)->getActiveState());
	}
	if (Input::GetKeyDown(Keycode::ALPHA2))
	{
		_lightManager->getPointLight(0)->setActiveState(!_lightManager->getPointLight(0)->getActiveState());
	}
	if (Input::GetKeyDown(Keycode::ALPHA3))
	{
		_lightManager->getSpotLight(0)->setActiveState(!_lightManager->getSpotLight(0)->getActiveState());
	}

	// Camera Movement:
	vec3 cameraMovement = vec3(camSpeedX, camSpeedY, camSpeedZ) * 3.0f * _timer->getDT();
	_camera->moveOnLocal(cameraMovement);

	_lightManager->getSpotLight(0)->setPos(_camera->getPosition());
	_lightManager->getSpotLight(0)->setDir(_camera->getFront());
	
	importer.models_Loaded[1]->setRotationY(importer.models_Loaded[1]->getRotation().y + 0.025f);
	importer.models_Loaded[2]->setRotationZ(importer.models_Loaded[2]->getRotation().z + 0.15f);
	
	// Draw:
	importer.models_Loaded[0]->Draw();
	importer.models_Loaded[1]->Draw();
	importer.models_Loaded[2]->Draw();

	_lightManager->drawLights();

	// Timer:
	_timer->updateTimer();
}

void Game::destroyGame()
{
	if (_timer) delete _timer;
	if (_camera) delete _camera;
}