#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

Shader::Shader()
{
	_shader = 0;
}

Shader::~Shader()
{

}

unsigned int Shader::CompileShader(unsigned int type, const char* source)
{
	unsigned int id = glCreateShader(type);

	std::string sourceShaderCode;

	std::ifstream sourceShaderFile;

	sourceShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		sourceShaderFile.open(source);
		std::stringstream sourceShaderStream;

		sourceShaderStream << sourceShaderFile.rdbuf();

		sourceShaderFile.close();

		sourceShaderCode = sourceShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ - " << e.what() << std::endl;
	}

	const char* srcCode = sourceShaderCode.c_str();

	glShaderSource(id, 1, &srcCode, nullptr);
	glCompileShader(id);

	return id;
}

unsigned int Shader::CreateShader(const char* vertexShader, const char* fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDetachShader(program, vs);
	glDetachShader(program, fs);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::SetShader(const char* vertexShader, const char* fragmentShader)
{
	_shader = CreateShader(vertexShader, fragmentShader);
}

void Shader::ClearShader()
{
	if (_shader != 0)
	{
		glDeleteProgram(_shader);
		_shader = 0;
	}
}
	
unsigned int Shader::GetShader()
{
	return _shader;
}