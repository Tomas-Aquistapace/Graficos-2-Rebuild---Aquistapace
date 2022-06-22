#include "Game.h"

Game::Game()
{
	
}

Game ::~Game()
{
	
}

void Game::play()
{
	initBaseGame(1000, 500, "Puzzle Demo");
	engineLoop();
}

void Game::initGame(Renderer* renderer)
{
	timer = new Timer();
	timer->start();
	shapeA = new Shape(ShapeTypes::rectangle, renderer);

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

	//test
	Material greenRubber;
	greenRubber._diffuse = glm::vec3(0.4f, 0.5f, 0.4f);
	greenRubber._specular = glm::vec3(0.04f, 0.7f, 0.04f);
	greenRubber._shininess = 0.78125f * 128.0f;

	cubeA = new Shape(ShapeTypes::cube, greenRubber, renderer);
	cubeA->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));

	Material obsidian;
	obsidian._diffuse = glm::vec3(0.18275f, 0.17f, 0.22525f);
	obsidian._specular = glm::vec3(0.332741f, 0.328634f, 0.346435f);
	obsidian._shininess = 0.3f * 128.0f;

	cubeB = new Shape(ShapeTypes::cube, obsidian, renderer);
	cubeB->setPosition(glm::vec3(-1.0f, 1.0f, 0.0f));

	Material emerald;
	emerald._diffuse = glm::vec3(0.07568f, 0.61424f, 0.07568f);
	emerald._specular = glm::vec3(0.633f, 0.727811f, 0.633f);
	emerald._shininess = 0.6f * 128.0f;

	cubeC = new Shape(ShapeTypes::cube, emerald, renderer);
	cubeC->setPosition(glm::vec3(1.0f, 1.0f, 0.0f));
	
	_camera = new Camera(renderer);
	_camera->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));

	shapeA->setPosition(vec3(-1.0f, -1.0f, 0.5f));//shapeA->getPosition().x + shapeA->getScale().x * shapeA->width, 0.5f, 0.0f));
	shapeA->setRotation(vec3(0.0f, 0.0f, 0.0f));
}

void Game::mouse_callback(Window window, Camera camera) {
	glfwGetCursorPos(window.getWindow(), &mouseCurrentX, &mouseCurrentY);
	double xoffset = mouseCurrentX - mouseLastX;
	double yoffset = mouseLastY - mouseCurrentY; // reversed since y-coordinates range from bottom to top
	mouseLastX = mouseCurrentX;
	mouseLastY = mouseCurrentY;
	const double sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	mousePitch += xoffset;
	mouseYaw += yoffset;
	if (mousePitch > 89) {
		mousePitch = 89;
	}
	if (mousePitch < -89) {
		mousePitch = -89;
	}
	glm::vec3 direction;
	direction.x = cos(glm::radians(mouseYaw)) * cos(glm::radians(mousePitch));
	direction.y = sin(glm::radians(mousePitch));
	direction.z = sin(glm::radians(mouseYaw)) * cos(glm::radians(mousePitch));
	camera.setFront(glm::normalize(direction));
}

void Game::updateGame(CollisionManager collManager, Input* input)
{
	//input
	if (input->isKeyDown(GLFW_KEY_UP))
	{
		speedY = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_DOWN))
	{
		speedY = -1;
	}
	else
	{
		speedY = 0;
	}

	if (input->isKeyDown(GLFW_KEY_RIGHT))
	{
		speedX = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_LEFT))
	{
		speedX = -1;
	}
	else
	{
		speedX = 0;
	}

	if (input->isKeyDown(GLFW_KEY_L))
	{
		speedZ = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_O))
	{
		speedZ = -1;
	}
	else
	{
		speedZ = 0;
	}

	if (input->isKeyDown(GLFW_KEY_U))
	{
		growSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_J))
	{
		growSpeed = -1;
	}
	else
	{
		growSpeed = 0;
	}

	if (input->isKeyDown(GLFW_KEY_S))
	{
		rotXSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_W))
	{
		rotXSpeed = -1;
	}
	else
	{
		rotXSpeed = 0;
	}

	if (input->isKeyDown(GLFW_KEY_A))
	{
		rotYSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_D))
	{
		rotYSpeed = -1;
	}
	else
	{
		rotYSpeed = 0;
	}

	if (input->isKeyDown(GLFW_KEY_Q))
	{
		rotZSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_E))
	{
		rotZSpeed = -1;
	}
	else
	{
		rotZSpeed = 0;
	}
	if (input->isKeyDown(GLFW_KEY_KP_8))
	{
		camSpeedY = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_KP_5))
	{
		camSpeedY = -1;
	}
	else
	{
		camSpeedY = 0;
	}
	if (input->isKeyDown(GLFW_KEY_KP_6))
	{
		camSpeedX = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_KP_4))
	{
		camSpeedX = -1;
	}
	else
	{
		camSpeedX = 0;
	}
	if (input->isKeyDown(GLFW_KEY_KP_7))
	{
		camSpeedZ = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_KP_9))
	{
		camSpeedZ = -1;
	}
	else
	{
		camSpeedZ = 0;
	}
	//
	if (input->isKeyDown(GLFW_KEY_T))
	{
		camTargetY = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_G))
	{
		camTargetY = -1;
	}
	else
	{
		camTargetY = 0;
	}
	if (input->isKeyDown(GLFW_KEY_H))
	{
		camTargetX = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_F))
	{
		camTargetX = -1;
	}
	else
	{
		camTargetX = 0;
	}
	if (input->isKeyDown(GLFW_KEY_R)) //esta parte se puede remover
	{
		camTargetZ = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_Y))
	{
		camTargetZ = -1;
	}
	else
	{
		camTargetZ = 0;
	}

	if (input->isKeyPressed(GLFW_KEY_1, isPressed[1]))
	{
		_lightA->setActiveState(!_lightA->getActiveState());
	}
	if (input->isKeyPressed(GLFW_KEY_2, isPressed[2]))
	{
		_lightB->setActiveState(!_lightB->getActiveState());
	}
	if (input->isKeyPressed(GLFW_KEY_3, isPressed[3]))
	{
		_lightC->setActiveState(!_lightC->getActiveState());
	}

	vec3 cameraMovement = vec3(camSpeedX, camSpeedY, camSpeedZ) * 3.0f * timer->getDT();
	vec3 cameraRotation = vec3(camTargetX, camTargetY, camTargetZ) * camRotSpeed * timer->getDT();
	_camera->moveOnLocal(glm::vec3 (cameraMovement));
	_camera->rotate(glm::vec3(cameraRotation));	
	
	//vec3 playerMovement = vec3(speedX, speedY, speedZ) * timer->getDT();
	//
	//vec3 newPos = shapeA->getPosition() + playerMovement;
	//shapeA->setPosition(newPos);
	
	//vec3 newScale = shapeA->getScale() + vec3(growSpeed, growSpeed, growSpeed)*timer->getDT();
	//shapeA->setScale(newScale);
	//
	//vec3 newRot = shapeA->getRotation() + vec3(rotXSpeed, rotYSpeed, rotZSpeed)*timer->getDT();
	//shapeA->setRotation(newRot);

	timer->updateTimer();

	importer.models_Loaded[0]->Draw();
	importer.models_Loaded[1]->Draw();
	importer.models_Loaded[2]->Draw();

	_lightA->setPos(_camera->getPosition());
	_lightA->setDir(_camera->getFront());

	shapeA->setPosition(_lightB->getPos());
	shapeA->setRotation(vec3(0.0f, 0.0f, 45.0f));
	shapeA->draw();

	cubeA->draw();
	cubeB->draw();
	cubeC->draw();
}

void Game::destroyGame()
{
	if (timer) delete timer;
	if (shapeA) delete shapeA;
	if (cubeA) delete cubeA;
	if (cubeB) delete cubeB;
	if (cubeC) delete cubeC;
	//if (sprite1) delete sprite1;
	//if (sprite2) delete sprite2;
	//if (tileMap) delete tileMap;
	//if (animation) delete animation;
	if (_camera) delete _camera;
	if (_lightB) delete _lightB;
	if (_lightA) delete _lightA;
}
