#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <intrin.h>

#include <GL\glew.h>
#include "transform.h"
#include "Camera.h"

class Shader
{
public:
	Shader();

	void Binding(); //Set gpu to use our shaders
	void Update(const Transform& transform, const Camera& camera);
	void Start(const std::string& vertFile, const std::string& fragFile);
	GLuint gettingProgram() { return program; }

	std::string Shader::LoadingShader(const std::string& fileName);
	void Shader::CheckingShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint Shader::CreatingShader(const std::string& text, unsigned int type);


	// uniform functions
	// ------------------------------------------------------------------------
	void settingBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void settingInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(program, name.c_str()), value);
		
		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void settingFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(program, name.c_str()), value);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void settingVec2(const std::string &name, const glm::vec2 &value) const
	{
		glUniform2fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void settingVec2(const std::string &name, float x, float y) const
	{
		glUniform2f(glGetUniformLocation(program, name.c_str()), x, y);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void settingVec3(const std::string &name, const glm::vec3 &value) const
	{
		glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void settingVec3(const std::string &name, float x, float y, float z) const
	{
		glUniform3f(glGetUniformLocation(program, name.c_str()), x, y, z);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void settingVec4(const std::string &name, const glm::vec4 &value) const
	{
		glUniform4fv(glGetUniformLocation(program, name.c_str()), 1, &value[0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	void settingVec4(const std::string &name, float x, float y, float z, float w)
	{
		glUniform4f(glGetUniformLocation(program, name.c_str()), x, y, z, w);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void settingMat2(const std::string &name, const glm::mat2 &mat) const
	{
		glUniformMatrix2fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void settingMat3(const std::string &name, const glm::mat3 &mat) const
	{
		glUniformMatrix3fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}
	// ------------------------------------------------------------------------
	void settingMat4(const std::string &name, const glm::mat4 &mat) const
	{
		glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);

		if ((glGetUniformLocation(program, name.c_str()) == -1))
		{
			std::cerr << "Unable to load shader: " << name.c_str() << std::endl;
			__debugbreak();
		}
	}


	~Shader();


protected:
private:
	static const unsigned int NUM_SHADERS = 2; // number of shaders

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint program; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};
