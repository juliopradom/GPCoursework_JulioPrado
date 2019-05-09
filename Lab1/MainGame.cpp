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
	Shader* shaderReflection();
	ShaderGeo* shaderExplosion();
	

	ShaderGeo* shaderSystem();
}

MainGame::~MainGame() 
{
}

void MainGame::run()
{
	initSystems(); 
	gameLoop();
}

void MainGame::initSystems()
{
	_gameDisplay.initDisplay(); 
	//whistle = audioDevice.loadSound("..\\res\\bang.wav");
	//backGroundMusic = audioDevice.loadSound("..\\res\\background.wav");
	texture.init("..\\res\\bricks.jpg"); //load texture
	texture1.init("..\\res\\sun.png"); //load texture


	shaderSkybox.init("..\\res\\shaderSkybox.vert", "..\\res\\shaderSkybox.frag");
	shaderReflection.init("..\\res\\shaderReflection.vert", "..\\res\\shaderReflection.frag");
	shaderExplosion.init("..\\res\\shaderGeoText.vert", "..\\res\\shaderGeoText.frag", "..\\res\\shaderGeoText.geom");


	shaderSystem.init("..\\res\\shaderSystem.vert", "..\\res\\shaderSystem.frag", "..\\res\\shaderSystem.geom");

	

	overlay.init("..\\res\\bricks.jpg");

	mesh1.loadModel("..\\res\\Fiat.obj");
	mesh2.loadModel("..\\res\\monkey3.obj");
	mesh3.loadModel("..\\res\\greekbuilding.obj");
	
	myCamera.initCamera(glm::vec3(0.0, 0.0, -10.0), 70.0f, (float)_gameDisplay.getWidth()/_gameDisplay.getHeight(), 0.01f, 1000.0f);

	counter = 1.0f;

	vector<std::string> faces
	{
		"..\\res\\skybox\\right.jpg",
		"..\\res\\skybox\\left.jpg",
		"..\\res\\skybox\\top.jpg",
		"..\\res\\skybox\\bottom.jpg",
		"..\\res\\skybox\\front.jpg",
		"..\\res\\skybox\\back.jpg"
	};
    cubemapTexture = skybox.loadCubemap(faces); //Load the cubemap using "faces" into cubemapTextures

	

	float skyboxVertices[] = {
		// positions          
		-12.0f,  12.0f, -12.0f,
		-12.0f, -12.0f, -12.0f,
		12.0f, 12.0f, 12.0f,
		12.0f, -12.0f, -12.0f,
		12.0f,  12.0f, -12.0f,
		-12.0f,  12.0f, -12.0f,

		-12.0f, -12.0f,  12.0f,
		-12.0f, -12.0f, -12.0f,
		-12.0f,  12.0f, -12.0f,
		-12.0f,  12.0f, -12.0f,
		-12.0f,  12.0f,  12.0f,
		-12.0f, -12.0f,  12.0f,

		12.0f, -12.0f, -12.0f,
		12.0f, -12.0f,  12.0f,
		12.0f,  12.0f,  12.0f,
		12.0f,  12.0f,  12.0f,
		12.0f,  12.0f, -12.0f,
		12.0f, -12.0f, -12.0f,

		-12.0f, -12.0f,  12.0f,
		-12.0f,  12.0f,  12.0f,
		12.0f,  12.0f,  12.0f,
		12.0f,  12.0f,  12.0f,
		12.0f, -12.0f,  12.0f,
		-12.0f, -12.0f,  12.0f,

		-12.0f,  12.0f, -12.0f,
		12.0f,  12.0f, -12.0f,
		12.0f,  12.0f,  12.0f,
		12.0f,  12.0f,  12.0f,
		-12.0f,  12.0f,  12.0f,
		-12.0f,  12.0f, -12.0f,

		-12.0f, -12.0f, -12.0f,
		-12.0f, -12.0f,  12.0f,
		12.0f, -12.0f, -12.0f,
		12.0f, -12.0f, -12.0f,
		-12.0f, -12.0f,  12.0f,
		12.0f, -12.0f,  12.0f
	};



	//use openGL functionality to generate & bind data into buffers
	
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	
}

void MainGame::gameLoop()
{
	while (_gameState != GameState::EXIT)
	{
		processInput();
		drawGame();
		playAudio(backGroundMusic, glm::vec3(0.0f,0.0f,0.0f));
	}
}

void MainGame::processInput()
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

void MainGame::Skybox()
{
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	shaderSkybox.Bind();
	shaderSkybox.setInt("skybox", 0);
	//view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
	shaderSkybox.setMat4("view", myCamera.GetView());
	shaderSkybox.setMat4("projection", myCamera.GetProjection());
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}


void MainGame::Reflection()
{

	shaderReflection.setMat4("model", transform.GetModel());
	shaderReflection.setMat4("view", myCamera.GetView());
	shaderReflection.setMat4("projection", myCamera.GetProjection());
	shaderReflection.setVec3("cameraPos", myCamera.getPos());
	shaderReflection.setInt("skybox", 0);




}


void MainGame::playAudio(unsigned int Source, glm::vec3 pos)
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

void MainGame::setADSLighting()
{
	modelView = transform.GetModel() * myCamera.GetView();
	
	shaderPass.setMat4("ModelViewMatrix", modelView);
	shaderPass.setMat4("ProjectionMatrix", myCamera.GetProjection()); 
	
	glm::mat4 normalMatrix = transpose(inverse(modelView));
	
	shaderPass.setMat4("NormalMatrix", normalMatrix);

	shaderPass.setVec4("Position", glm::vec4(10.0,10.0,10.0,1.0));
	shaderPass.setVec3("Intensity", glm::vec3(0.0, 0.0, 0.0));

	shaderPass.setVec3("ka", glm::vec3(0.5, 0.5, 0.5));
	shaderPass.setVec3("kd", glm::vec3(0.5, 0.5, 0.5));
	shaderPass.setVec3("ks", glm::vec3(0.5, 0.5, 0.5));

	shaderPass.setFloat("Shininess", 0.5);
}

void MainGame::setToonLighting()
{
	shaderToon.setVec3("lightDir", glm::vec3(0.5, 0.5, 0.5));
}

void MainGame::setRimShader()
{
	shaderRim.setMat4("u_vm", myCamera.GetView());
	shaderRim.setMat4("u_pm", myCamera.GetProjection());
}


void MainGame::blobEffect()
{
	GLuint blockIndex = glGetUniformBlockIndex(shaderBlur.getProgram(), "BlobSettings");

	GLint blockSize;
	glGetActiveUniformBlockiv(shaderBlur.getProgram(), blockIndex,
		GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize); //get information about blobsettings and save it in blockSize

	GLubyte * blockBuffer = (GLubyte *)malloc(blockSize); //allocates the requested memory and returns a pointer to it.

														  // Query for the offsets of each block variable
	const GLchar *names[] = { "InnerColor", "OuterColor",
		"RadiusInner", "RadiusOuter" };

	GLuint indices[4];
	glGetUniformIndices(shaderBlur.getProgram(), 4, names, indices); // glGetUniformIndices retrieves the indices of a number of uniforms within program

	GLint offset[4];
	glGetActiveUniformsiv(shaderBlur.getProgram(), 4, indices, GL_UNIFORM_OFFSET, offset); //Returns information about several active uniform variables for the specified program object

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


void MainGame::setShaderGeo()
{

	shaderExplosion.setFloat("time", 1.0f + (counter*1.0f));

}





void MainGame::setSystem(glm::vec3 variable, float lapsus)
{

	
		shaderSystem.setMat4("model", glm::mat4(transform.GetModel()));
		shaderSystem.setMat4("view", myCamera.GetView());
		shaderSystem.setMat4("projection", myCamera.GetProjection());

		shaderSystem.setVec4("point", glm::vec4(variable, 1));

		glm::mat4 translation;


		translation[0] = glm::vec4(sqrtf(2.0f) / 2.0f, -sqrtf(2.0f) / 2.0f, 0, 0.0f);
		translation[1] = glm::vec4(sqrtf(2.0f) / 2.0f, sqrtf(2.0f) / 2.0f, 0, 0.0f);
		translation[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		translation[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);


		shaderSystem.setMat4("translation", glm::mat4(translation));

		// Clock-wise
		
		glm::mat4 translation_offset;

		translation_offset[0] = glm::vec4(cos(lapsus), -sin(lapsus), 0, 0.0f);
		translation_offset[1] = glm::vec4(sin(lapsus), cos(lapsus), 0, 0.0f);
		translation_offset[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		translation_offset[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		glm::vec4 pos = glm::vec4(variable, 1) + translation_offset * (glm::vec4(3, 0, 0, 0) - glm::vec4(variable, 1));
		pos[3] = 0;

		shaderSystem.setVec4("direction", pos);

		// Anti clock-wise


		glm::mat4 translation_offset_invert;

		translation_offset_invert[0] = glm::vec4(cos(-lapsus), -sin(-lapsus), 0, 0.0f);
		translation_offset_invert[1] = glm::vec4(sin(-lapsus), cos(-lapsus), 0, 0.0f);
		translation_offset_invert[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		translation_offset_invert[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		pos = glm::vec4(variable, 1) + translation_offset_invert * (glm::vec4(3, 0, 0, 0) - glm::vec4(variable, 1));
		pos[3] = 0;

		shaderSystem.setVec4("direction_invert", pos);

}




void MainGame::drawGame()
{

	
	_gameDisplay.clearDisplay(0.0f, 0.0f, 0.0f, 1.0f);


	Skybox();


	transform.SetPos(glm::vec3(-sinf(counter)*10, 0.5, 7.0));
	transform.SetRot(glm::vec3(-counter, counter , counter * 5));
	transform.SetScale(glm::vec3(0.05, 0.05, 0.05));

	
	setShaderGeo();

	shaderExplosion.Bind();
	shaderExplosion.Update(transform, myCamera);
	texture.Bind(0);
	mesh3.draw();
	mesh3.updateSphereData(*transform.GetPos(), 0.62f);



	transform.SetPos(glm::vec3(sinf(counter)*10, 0.5, 0.0));
	transform.SetRot(glm::vec3(0.0, counter , 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	setShaderGeo();

	
	shaderReflection.Bind();
	Reflection();
	shaderReflection.Update(transform, myCamera);
	texture.Bind(0);
	mesh1.draw();
	
	

	transform.SetPos(glm::vec3(-sinf(counter), -1.0, -sinf(counter)*10 +10));
	transform.SetRot(glm::vec3(0.0, counter , 0.0));
	transform.SetScale(glm::vec3(0.6, 0.6, 0.6));
	setShaderGeo();

	
	shaderSystem.Bind();
	
	shaderSystem.Update(transform, myCamera);
	setSystem(glm::vec3(-sinf(counter), -1.0, -sinf(counter) * 10 + 10), counter);
	texture1.Bind(0);
	mesh2.draw();



	counter = counter + 0.01f;

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	_gameDisplay.swapBuffer();
} 