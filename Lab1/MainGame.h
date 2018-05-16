#pragma once
#include <SDL\SDL.h>
#include <GL/glew.h>
#include "Display.h" 
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "transform.h"
#include "Audio.h"
#include "Overlay.h"

enum class GameState{PLAY, EXIT};

class MainGame
{
public:
	MainGame();
	~MainGame();

	void run();

private:

	void startSystems();
	void processingInput();
	void gameLoop();
	void drawingGame();
	bool collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad);
	void playingAudio(unsigned int Source, glm::vec3 pos);
	void blobEffect();
	void settingADSLighting();
	void settingToonLighting();
	void settingRimShader();
	void settingRimToon();

	Display _gameDisplay;
	GameState _gameState;
	Mesh m1;
	Mesh m2;
	Mesh m3;
	Texture tex1;
	Texture tex2;
	Overlay overlay;
	Shader shadePass;
	Shader shadeBlur;
	Shader shadeToon;
	Shader shadeRim;
	Shader shadeRimToon;

	glm::mat4 modelView;

	Camera cam;
	Audio audioDevice;

	float counter;
	unsigned int whistle;
	unsigned int backGroundMusic;
};

