#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace glm;

Renderer::Renderer()
{
	_shader = new Shader();

	defaultMat = new Material(vec3(1.0f, 0.5f, 0.31f), vec3(1.0f, 0.5f, 0.31f), vec3(0.5f, 0.5f, 0.5f), 32.0f);
}

Renderer::~Renderer()
{
	if (_shader) delete _shader;

	if (defaultMat) delete defaultMat;
}

void Renderer::initShaderProgram() 
{
	_shader->SetShader("../PDG-biblioteca/src/Shader/vertex.shader", "../PDG-biblioteca/src/Shader/fragment.shader");
	glUseProgram(_shader->GetShader());
	setVP();
}

void Renderer::creatoVAO(unsigned int &vao)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void Renderer::createVBO(float* vertexDataArray, int arraySize, unsigned int &vbo)
{
	int vertexSize = sizeof(vertexDataArray) * arraySize;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexDataArray, GL_STATIC_DRAW);
}

void Renderer::createEBO(int* indexArray, int arraySize, unsigned int &_ebo) 
{
	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray) * arraySize, indexArray, GL_STATIC_DRAW);
}

void Renderer::setPosAttrib() 
{
	_posAttrib = glGetAttribLocation(_shader->GetShader(), "position");
	glVertexAttribPointer(_posAttrib, posElementsAmount, GL_FLOAT, GL_FALSE, attribElementsAmount * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttrib); //cambie esto de 0 a _posAttrib
}

void Renderer::setTextureAttrib()
{
	_textureAttrib = glGetAttribLocation(_shader->GetShader(), "texCoor");
	glVertexAttribPointer(_textureAttrib, texElementsAmount, GL_FLOAT, GL_FALSE, attribElementsAmount * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(_textureAttrib);//cambie esto de 1 a _textureAttrib
}

void Renderer::setNormalAttrib()
{
	_normalAttrib = glGetAttribLocation(_shader->GetShader(), "normal");
	glVertexAttribPointer(_normalAttrib, normalElementsAmount, GL_FLOAT, GL_FALSE, attribElementsAmount * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(_normalAttrib);//cambie esto de 1 a _textureAttrib
}

void Renderer::stopShader()
{
	if (_shader) _shader->ClearShader();
}

void Renderer::drawShape(glm::mat4x4 trs, unsigned int vbo, unsigned int vao, float* vertex, unsigned int size, unsigned int indexSize)
{
	setMaterial(defaultMat);
	bindSpriteBuffers(vbo,vao,vertex,size);
	setSpriteAttrib();
	updateProgram(trs);
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind
	//glBindTexture(GL_TEXTURE_2D, 0);
}
void Renderer::drawShape(glm::mat4x4 trs, unsigned int vbo, unsigned int vao, float* vertex, unsigned int size, unsigned int indexSize, Material* material)
{
	setMaterial(material);
	bindSpriteBuffers(vbo, vao, vertex, size);
	setSpriteAttrib();
	glUniform1i(glGetUniformLocation(_shader->GetShader(), "isModel"), 0);
	updateProgram(trs);
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind
}

unsigned int Renderer::getShaderProgram()
{
	return _shader->GetShader();
}

void Renderer::setTexture(unsigned int texture)
{	
	//cout << texture << endl;
	unsigned int uniformTex = glGetUniformLocation(_shader->GetShader(), "tex");
	glUseProgram(_shader->GetShader());
	glUniform1i(uniformTex, 0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
}

void Renderer::bindSpriteBuffers(unsigned int vbo, unsigned int vao, float* vertex, float size)
{
	unsigned int memorySize = sizeof(float) * size;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glBufferData(GL_ARRAY_BUFFER, memorySize, vertex, GL_STATIC_DRAW);
}

void Renderer::setSpriteAttrib()
{
	glUniform1i((glGetUniformLocation(_shader->GetShader(), "tex")), 0);// CHECKEAR ESTO
	setPosAttrib();
	setTextureAttrib();
	setNormalAttrib();
}

void Renderer::bindTexture(unsigned int texture) 
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
}

void Renderer::updateProgram(mat4 model) 
{
	unsigned int transformLocation = glGetUniformLocation(_shader->GetShader(), "Model");
	glUseProgram(_shader->GetShader());
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(model));
}

void Renderer::blendTexture()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::unblendTexture()
{
	glDisable(GL_BLEND);
}

void Renderer::setVP()
{
	unsigned int projectionLocation = glGetUniformLocation(_shader->GetShader(), "Projection");
	unsigned int viewLocation = glGetUniformLocation(_shader->GetShader(), "View");
	mat4 proj = mat4(1.0f);
	mat4 view = mat4(1.0f);
	view = lookAt(vec3(0.0, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	proj = /*glm::ortho(-4.0f,4.0f,-2.0f,2.0f,-100.0f,100.0f); */perspective(45.0f, 2.0f, 0.1f, 100.0f);//el aspect esta mal pero queda bien porque cambie las medidas de los cuadrados
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(proj));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));
}

void Renderer::updateView(vec3 position, vec3 target){
	unsigned int viewLocation = glGetUniformLocation(_shader->GetShader(), "View");
	mat4 view = lookAt(position, target, vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

	unsigned int viewPos = glGetUniformLocation(_shader->GetShader(), "viewPos");
	glUniform3fv(viewPos, 1, value_ptr(position));
}

void Renderer::updateView(vec3 position, vec3 front, vec3 _up)
{
	unsigned int viewLocation = glGetUniformLocation(_shader->GetShader(), "View");
	mat4 view;
	view = lookAt(position, position + front, _up);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

	unsigned int viewPos = glGetUniformLocation(_shader->GetShader(), "viewPos");
	glUniform3fv(viewPos, 1, value_ptr(position));
}

int Renderer::getAttribElementsAmount()
{
	return attribElementsAmount;
}

void Renderer::setMaterial(Material* material)
{
	unsigned int uniformMatAmb = glGetUniformLocation(_shader->GetShader(), "mat.ambient");
	unsigned int uniformMatDiff = glGetUniformLocation(_shader->GetShader(), "mat.diffuse");
	unsigned int uniformMatSpec = glGetUniformLocation(_shader->GetShader(), "mat.specular");
	unsigned int uniformMatShin = glGetUniformLocation(_shader->GetShader(), "mat.shininess");
	glUniform3fv(uniformMatAmb, 1, value_ptr(material->_ambient));
	glUniform3fv(uniformMatDiff, 1, value_ptr(material->_diffuse));
	glUniform3fv(uniformMatSpec, 1, value_ptr(material->_specular));
	glUniform1f(uniformMatShin, material->_shininess);
}

void Renderer::updateLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, unsigned int lightKind, bool activeState, int id, glm::vec3 color)
{
	string dirLightStr = "dirLight";
	string pointLightStr = "pointLight";
	string spotLightStr = "spotLight";
	string testLightStr = "light";

	string indexStr = "[" + to_string(id) + "]";
	pointLightStr += indexStr;
	dirLightStr += indexStr;
	spotLightStr += indexStr;

	switch (lightKind)
	{
	case 0:
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(testLightStr + ".position").c_str()), 1, value_ptr(position));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(testLightStr + ".ambient").c_str()), 1, value_ptr(ambient));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(testLightStr + ".diffuse").c_str()), 1, value_ptr(diffuse));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(testLightStr + ".specular").c_str()), 1, value_ptr(specular));
		glUniform1i(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(testLightStr + ".initialized").c_str()), activeState);
		glUniform1i(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(testLightStr + ".id").c_str()), id);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(testLightStr + ".color").c_str()), 1, value_ptr(color));
		break;
	case 1:
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(pointLightStr + ".position").c_str()), 1, value_ptr(position));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(pointLightStr + ".ambient").c_str()), 1, value_ptr(ambient));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(pointLightStr + ".diffuse").c_str()), 1, value_ptr(diffuse));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(pointLightStr + ".specular").c_str()), 1, value_ptr(specular));
		glUniform1f(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(pointLightStr + ".constant").c_str()), constant);// 1.0f
		glUniform1f(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(pointLightStr + ".linear").c_str()), linear);// 0.09f
		glUniform1f(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(pointLightStr + ".quadratic").c_str()), quadratic);// 0.032f
		glUniform1i(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(pointLightStr + ".initialized").c_str()), activeState);
		glUniform1i(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(pointLightStr + ".id").c_str()), id);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(pointLightStr + ".color").c_str()), 1, value_ptr(color));
		break;
	case 2:
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(dirLightStr + ".direction").c_str()), 1, value_ptr(direction));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(dirLightStr + ".ambient").c_str()), 1, value_ptr(ambient));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(dirLightStr + ".diffuse").c_str()), 1, value_ptr(diffuse));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(dirLightStr + ".specular").c_str()), 1, value_ptr(specular));
		glUniform1i(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(dirLightStr + ".initialized").c_str()), activeState);
		glUniform1i(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(dirLightStr + ".id").c_str()), id);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(dirLightStr + ".color").c_str()), 1, value_ptr(color));
		break;
	case 3:
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(spotLightStr + ".position").c_str()), 1, value_ptr(position));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(spotLightStr + ".direction").c_str()), 1, value_ptr(direction));//vec3(0.0f, 1.0f, 0.0f)
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(spotLightStr + ".ambient").c_str()), 1, value_ptr(ambient));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(spotLightStr + ".diffuse").c_str()), 1, value_ptr(diffuse));
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(spotLightStr + ".specular").c_str()), 1, value_ptr(specular));
		glUniform1f(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(spotLightStr + ".cutOff").c_str()), glm::cos(cutOff));// glm::radians(12.5f)
		glUniform1f(glGetUniformLocation(_shader->GetShader(), (GLchar*)(spotLightStr  + ".constant").c_str()), constant);// 1.0f
		glUniform1f(glGetUniformLocation(_shader->GetShader(), (GLchar*)(spotLightStr  + ".linear").c_str()), linear);// 0.09f
		glUniform1f(glGetUniformLocation(_shader->GetShader(), (GLchar*)(spotLightStr  + ".quadratic").c_str()), quadratic);// 0.032f
		glUniform1i(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(spotLightStr + ".initialized").c_str()), activeState);
		glUniform1i(glGetUniformLocation(_shader->GetShader(),  (GLchar*)(spotLightStr + ".id").c_str()), id);
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), (GLchar*)(spotLightStr + ".color").c_str()), 1, value_ptr(color));
		break;
	}
}

void Renderer::setMesh(string locationName, int texNumber, bool usesSpecularMaps) 
{
	glUseProgram(_shader->GetShader());
	glUniform1i(glGetUniformLocation(_shader->GetShader(),(GLchar*)locationName.c_str()), texNumber);
	setMaterial(defaultMat);
	glUniform1i(glGetUniformLocation(_shader->GetShader(), "mat.useSpecularMaps"), usesSpecularMaps);
	if (!usesSpecularMaps)
	{
		glUniform3fv(glGetUniformLocation(_shader->GetShader(), "mat.specular"), 1, value_ptr(glm::vec3(0.5f,0.5f,0.5f)));
	}
	glUniform1i(glGetUniformLocation(_shader->GetShader(), "isModel"), true);
}