#include "MainGame.h"
#include "Camera.h"
#include <iostream>
#include <string>


Transform transform;

MainGame::MainGame()
{
	_gameState = GameState::PLAY;
	Display* _gameDisplay = new Display(); //new display
    Mesh* mesh1();
	Mesh* mesh2();
	Mesh* mesh3();
	Audio* audioDevice();
	Texture* texture(); //load texture
	Texture* texture1(); //load texture
	Overlay* overlay(); //load texture
	Shader* shaderPass();
	Shader* shaderBlur();
	Shader* shaderToon();
	Shader* shaderRim();
	Shader* shaderRimToon();
}

MainGame::~MainGame() 
{
}

void MainGame::run()
{
	startSystems(); 
	gameLoop();
}

void MainGame::startSystems()
{
	_gameDisplay.initDisplay(); 
	whistle = audioDevice.loadSound("..\\res\\bang.wav");
	backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");
	tex1.init("..\\res\\bricks.jpg"); //load texture
	tex2.init("..\\res\\water.jpg"); //load texture

	shadePass.Start("..\\res\\shaderRim.vert","..\\res\\shaderRim.frag");
	shadeBlur.Start("..\\res\\shaderBlur.vert", "..\\res\\shaderBlur.frag");
	shadeToon.Start("..\\res\\shaderToon.vert", "..\\res\\shaderToon.frag");
	shadeRim.Start("..\\res\\shaderRim.vert", "..\\res\\shaderRim.frag");
	shadeRimToon.Start("..\\res\\shaderRimToon.vert", "..\\res\\shaderRimToon.frag");
	
	overlay.start("..\\res\\bricks.jpg");

	m1.loadModel("..\\res\\pixelspaceship.obj");
	m2.loadModel("..\\res\\skull.obj");
	m3.loadModel("..\\res\\monkey3.obj");
	
	cam.initCamera(glm::vec3(0, 0, -10.0), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processingInput();
		drawingGame();
		collision(m1.getSpherePos(), m1.getSphereRadius(), m2.getSpherePos(), m2.getSphereRadius());
		playingAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
	}
}

void MainGame::processingInput()
{
	SDL_Event evnt;

	while(SDL_PollEvent(&evnt)) //get and process events
	{
		switch (evnt.type)
		{
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
		}
	}
	
}


bool MainGame::collision(glm::vec3 m1Pos, float m1Rad, glm::vec3 m2Pos, float m2Rad)
{
	float distance = glm::sqrt((m2Pos.x - m1Pos.x)*(m2Pos.x - m1Pos.x) + (m2Pos.y - m1Pos.y)*(m2Pos.y - m1Pos.y) + (m2Pos.z - m1Pos.z)*(m2Pos.z - m1Pos.z));

	if (distance < (m1Rad + m2Rad))
	{
		audioDevice.setlistener(cam.getPos(), m1Pos); //add bool to mesh
		//playAudio(whistle, m1Pos);
		return true;
	}
	else
	{
		return false;
	}
}

void MainGame::playingAudio(unsigned int Source, glm::vec3 pos)
{
	
	ALint state; 
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		//audioDevice.playSound(Source, pos);
	}
}

void MainGame::settingADSLighting()
{
	modelView = transform.GetModel() * cam.GetView();
	
	shadePass.settingMat4("ModelViewMatrix", modelView);
	shadePass.settingMat4("ProjectionMatrix", cam.GetProjection()); 
	
	glm::mat4 normalMatrix = transpose(inverse(modelView));
	
	shadePass.settingMat4("NormalMatrix", normalMatrix);

	shadePass.settingVec4("Position", glm::vec4(10.0,10.0,10.0,1.0));
	shadePass.settingVec3("Intensity", glm::vec3(0.0, 0.0, 0.0));

	shadePass.settingVec3("ka", glm::vec3(0.5, 0.5, 0.5));
	shadePass.settingVec3("kd", glm::vec3(0.5, 0.5, 0.5));
	shadePass.settingVec3("ks", glm::vec3(0.5, 0.5, 0.5));

	shadePass.settingFloat("Shininess", 0.5);
}

void MainGame::settingToonLighting()
{
	shadeToon.settingVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
}

void MainGame::settingRimShader()
{
	shadeRim.settingMat4("u_vm", cam.GetView());
	shadeRim.settingMat4("u_pm", cam.GetProjection());
}

void MainGame::settingRimToon()
{
	shadeRimToon.settingVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
	shadeRimToon.settingMat4("u_vm", cam.GetView());
	shadeRimToon.settingMat4("u_pm", cam.GetProjection());
}

void MainGame::blobEffect()
{
	GLuint blockIndex = glGetUniformBlockIndex(shadeBlur.gettingProgram(), "BlobSettings");

	GLint blockSize;
	glGetActiveUniformBlockiv(shadeBlur.gettingProgram(), blockIndex,
		GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize); //get information about blobsettings and save it in blockSize

	GLubyte * blockBuffer = (GLubyte *)malloc(blockSize); //allocates the requested memory and returns a pointer to it.

														  // Query for the offsets of each block variable
	const GLchar *names[] = { "InnerColor", "OuterColor",
		"RadiusInner", "RadiusOuter" };

	GLuint indices[4];
	glGetUniformIndices(shadeBlur.gettingProgram(), 4, names, indices); // glGetUniformIndices retrieves the indices of a number of uniforms within program

	GLint offset[4];
	glGetActiveUniformsiv(shadeBlur.gettingProgram(), 4, indices, GL_UNIFORM_OFFSET, offset); //Returns information about several active uniform variables for the specified program object

	GLfloat outerColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	GLfloat innerColor[] = { 1.0f, 1.0f, 0.75f, 1.0f };

	GLfloat innerRadius = 0.0f, outerRadius = 3.0f;

	memcpy(blockBuffer + offset[0], innerColor,
		4 * sizeof(GLfloat)); //destination, source, no of bytes. 
	memcpy(blockBuffer + offset[1], outerColor,
		4 * sizeof(GLfloat));
	memcpy(blockBuffer + offset[2], &innerRadius,
		sizeof(GLfloat));
	memcpy(blockBuffer + offset[3], &outerRadius,
		sizeof(GLfloat));

	GLuint uboHandle;

	glGenBuffers(1, &uboHandle);

	glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
	glBufferData(GL_UNIFORM_BUFFER, blockSize, blockBuffer,
		GL_DYNAMIC_DRAW); //creates and initializes a buffer object's data store - targer, size, data, usage

	glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, uboHandle); // bind a buffer object to an indexed buffer target - trager, index, buffer
}

void MainGame::drawingGame()
{
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);

	transform.SetPos(glm::vec3(sinf(counter), -1, 0.0));
	transform.SetRot(glm::vec3(0.0, 5, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	
	shadeRim.Binding();
	settingRimShader();
	shadeRim.Update(transform, cam);
	tex1.Bind(0);
	m1.draw();
	m1.updateSphereData(*transform.GetPos(), 0.62f);
	
	////////////////////////////////////////////////////////////////////////////////////
	transform.SetPos(glm::vec3(1, -1.0, 200));
	transform.SetRot(glm::vec3(-180.0, counter * 7, 180));
	transform.SetScale(glm::vec3(0.3, 0.3, 0.3));
	
	shadeRimToon.Binding();	
	settingRimToon();
	shadeRimToon.Update(transform, cam);
	m2.draw();
	m2.updateSphereData(*transform.GetPos(), 0.62f);

	/////////////////////////////////////////////////////////////////////////////////////
	transform.SetPos(glm::vec3(-sinf(counter), -sinf(counter), -sinf(counter)));
	transform.SetRot(glm::vec3(0.0, counter * 5, 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));

	shadeToon.Binding();
	settingToonLighting();
	shadeToon.Update(transform, cam);
	m3.draw();
	m3.updateSphereData(*transform.GetPos(), 0.62f);

	counter = counter + 0.01f;

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 