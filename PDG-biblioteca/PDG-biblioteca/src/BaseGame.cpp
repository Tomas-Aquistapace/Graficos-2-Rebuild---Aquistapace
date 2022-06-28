#include "BaseGame.h"
#include <iostream>

using namespace std;

BaseGame::BaseGame()
{
	_renderer = new Renderer();
	_window = new Window();
	_lightManager = new LightManager();

	_gameShouldClose = false;
}

BaseGame::~BaseGame()
{
	if (_window != NULL) 
	{
		delete _window;
	}
	if (_renderer != NULL) 
	{
		delete _renderer;
	}
	if (_lightManager != NULL)
	{
		delete _lightManager;
	}
}

void BaseGame::initBaseGame(int screenWidth, int screenHeight, const char* title)
{
	glfwInit();
	_window->createWindow(screenWidth, screenHeight, title);
	glfwMakeContextCurrent(_window->getWindow());
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	Input::SetWindow(_window->getWindow());

	_renderer->initShaderProgram();
}

const float radius = 10.0f;

int BaseGame::engineLoop(float r, float g, float b, float a)
{
	initGame(_renderer);

	while (!glfwWindowShouldClose(_window->getWindow()) && !_gameShouldClose)
	{
		//clear
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER);
		
		//game update
		updateGame(_collManager);

		//engine input
		Input::CheckClearInputList();

		//swap
		glfwSwapBuffers(_window->getWindow());
		glfwPollEvents();
	}
	_renderer->stopShader();
	
	glfwTerminate();
	
	//game destroy
	destroyGame();

	return 0;
}

void BaseGame::exitApplication()
{
	_gameShouldClose = true;
}

void BaseGame::activateFPSCamera(Camera* camera, float sensitivity)
{
	Input::ActivateFPSCamera(_window->getWindow(), camera, sensitivity);
}

void BaseGame::deactivateFPSCamera()
{
	Input::DeactivateFPSCamera(_window->getWindow());
}
