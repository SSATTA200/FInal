#pragma once
#include <string>
#include "Texture.h"
#include "Display.h"
#include "Mesh.h"
#include <gl\glew.h>
#include <glm\glm.hpp>
#include <vector>


class Overlay
{
public:
	Overlay();
	~Overlay();
	void drawingOL(GLuint program);
	void start(const std::string& fileName);

private:
	Texture tex;
};

