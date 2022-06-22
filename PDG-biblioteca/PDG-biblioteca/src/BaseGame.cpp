#include "BaseGame.h"
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>

using namespace std;

BaseGame::BaseGame()
{
	_window = new Window();
	_renderer = new Renderer();
	gameShouldClose = false;
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
	//glfwSetInputMode(_window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	_renderer->initVertexShader();
	_renderer->initFragmentShader();
	_renderer->initShaderProgram();
}

int BaseGame::engineLoop(float r, float g, float b, float a)
{
	initGame(_renderer);

	while (!glfwWindowShouldClose(_window->getWindow()) && !gameShouldClose)
	{
		//clear
		glClearColor(r, g, b, a);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER);

		//game update
		updateGame(collManager);
		Input::CheckClearInputList();

		//swap
		glfwSwapBuffers(_window->getWindow());
		glfwPollEvents();
	}
	_renderer->deleteShaderProgram();
	_renderer->deleteFragmentShader();
	_renderer->deleteVertexShader();
	glfwTerminate();

	return 0;
}

void BaseGame::CloseApp()
{
	gameShouldClose = true;
}

void BaseGame::ActivateFPSCamera(Camera* camera, float sensitivity)
{
	Input::ActivateFPSCamera(_window->getWindow(), camera, sensitivity);
}

void BaseGame::DeactivateFPSCamera()
{
	Input::DeactivateFPSCamera(_window->getWindow());
}