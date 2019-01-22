
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "MeshManager.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <GL\freeglut.h>
#include "Renderer.h"
#include <vector>
#include "Drawable.h"
#include "Camera.h"
#include "rectangular_prism.h"
#include "Tank.h"
#include "TankPlayer.h"
#include "TankAI.h"
#include "TextureManager.h"
#include "Static.h"



void configureGl() {
	//	Set background color to black and opaque
	GLCall(glClearColor(0.4F, 0.1F, 0.1F, 1.0F));

	//	Enable depth test for each pixel
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));
}
GLuint program;

GLuint setup_program() {
	// Vertex Shader
	const GLchar *vertexSource = R"glsl(
			#version 330

			in vec3 aPosition;
			in vec3 aNormal;
			in vec2 aTexCoord;

			uniform mat4 uTransform;
			uniform mat4 uCamera;
			uniform mat4 uPerspective;

			out vec3 WorldPosition;
			out vec3 Normal;
			out vec2 TexCoord;

			void main()
			{
				WorldPosition = (uTransform * vec4(aPosition, 1.0)).xyz;
				Normal = normalize(mat3(transpose(inverse(uTransform))) * aNormal);
				TexCoord = aTexCoord;

				vec4 opengl_pos = uPerspective * uCamera * uTransform * vec4(aPosition, 1.0);

				gl_Position = opengl_pos;
			}
		)glsl";

	// Fragment Shader
	const GLchar *fragmentSource = R"glsl(
			#version 330

			in vec3 WorldPosition;
			in vec3 Normal;
			in vec2 TexCoord;

			uniform sampler2D Texture;

			layout (location = 0) out vec4 outColor;

			void main()
			{
				vec3 light_pos = vec3(0.0, 0.0, 80.0);

				vec3 light_direction = normalize(light_pos - WorldPosition.xyz);
				float light_density = dot(light_direction, Normal);

				vec4 color = texture(Texture, TexCoord*10);

				outColor = color * (light_density + 0.2);
			}
		)glsl";

	// Create and compile the vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLCall(glShaderSource(vertexShader, 1, &vertexSource, NULL));
	GLCall(glCompileShader(vertexShader));

	// Create and compile the fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLCall(glShaderSource(fragmentShader, 1, &fragmentSource, NULL));
	GLCall(glCompileShader(fragmentShader));

	// Link the vertex and fragment shader into a shader program
	GLuint program = glCreateProgram();
	GLCall(glAttachShader(program, vertexShader));
	GLCall(glAttachShader(program, fragmentShader));

	GLCall(glBindAttribLocation(program, ATTR_LOCATION::POSITION, "aPosition"));
	GLCall(glBindAttribLocation(program, ATTR_LOCATION::NORMAL, "aNormal"));

	GLCall(glLinkProgram(program));

	return program;
}



TankPlayer* tankPlayer;
TankAI* tankAI;
TankAI* tankAI2;
TankAI* tankAI3;
TankAI* tankAI4;
Drawable* staticCube;
std::vector<Tank* > AITanks;
bool keyState[sizeof(char)] = { 0 };


void KeyStateUpdate() {

	//tank move forward - backward
	if (keyState['w']) {
		tankPlayer->MoveForward();
	}
	else if (keyState['s']) {
		//std::cout << keyState['s'] << std::endl;
		tankPlayer->MoveBackward();
	}
	//tank rotate
	if (keyState['d']) {
		tankPlayer->Rotate(TankRotate::RIGHT);
	}
	else if (keyState['a']) {
		tankPlayer->Rotate(TankRotate::LEFT);
	}
	//camera rotate
	if (keyState['t']) {
		tankPlayer->GetCamera()->Rotate(-0.1, CameraRotate::PITCH);
		tankPlayer->GetCamera()->UpdateTransform(program);
	}
	else if (keyState['y']) {
		tankPlayer->GetCamera()->Rotate(0.1, CameraRotate::ROLL);
		tankPlayer->GetCamera()->UpdateTransform(program);
	}
}

void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		tankPlayer->Shoot();
		tankAI->Shoot();
	}
		
	else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		keyState['w'] = true;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		keyState['w'] = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		keyState['s'] = true;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		keyState['s'] = false;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		keyState['d'] = true;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		keyState['d'] = false;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		keyState['a'] = true;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		keyState['a'] = false;
	}
	else if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		keyState['t'] = true;
	}
	else if (key == GLFW_KEY_T && action == GLFW_RELEASE) {
		keyState['t'] = false;
	}
	else if (key == GLFW_KEY_Y && action == GLFW_PRESS) {
		keyState['y'] = true;
	}
	else if (key == GLFW_KEY_Y && action == GLFW_RELEASE) {
		keyState['y'] = false;
	}
}
void setup() {
	//initialize key states to false;
	for (int i = 0; i < sizeof(char); i++) {
		keyState[i] = 0;
	}
	keyState['s'] = 0;

	//setupDebuging();

	configureGl();

	//	Create program
	program = setup_program();
	GLCall(glUseProgram(program));

	//load texture
	Static::LoadTextures();
	//load models
	Static::LoadVertexArrayObjects();
	Static::LoadDrawables();
	tankPlayer = new TankPlayer(Static::vaoTank, program, 0.4f, 0.2f, 1.0f, 0.03f, 1.0f);
	tankPlayer->SetPosition(glm::vec3(50.0f, -20.0f, 0.0f));
	tankAI = new TankAI(Static::vaoTank, program, 0.4f, 0.2f, 1.0f, 0.03f, 1.0f);
	tankAI->SetPosition(glm::vec3(20.0f, -80.0f, 0.0f));
	AITanks.push_back(tankAI);
	tankAI2 = new TankAI(Static::vaoTank, program, 0.4f, 0.2f, 1.0f, 0.03f, 1.0f);
	tankAI2->SetPosition(glm::vec3(80.0f, 30.0f, 0.0f));
	AITanks.push_back(tankAI2);
	tankAI3 = new TankAI(Static::vaoTank, program, 0.4f, 0.2f, 1.0f, 0.03f, 1.0f);
	tankAI3->SetPosition(glm::vec3(40.0f, 15.0f, 0.0f));
	AITanks.push_back(tankAI3);
	tankAI4 = new TankAI(Static::vaoTank, program, 0.4f, 0.2f, 1.0f, 0.03f, 1.0f);
	tankAI4->SetPosition(glm::vec3(-60.0f, -40.0f, 0.0f));
	AITanks.push_back(tankAI4);
	TankAI* tankAI5 = new TankAI(Static::vaoTank, program, 0.4f, 0.2f, 1.0f, 0.03f, 1.0f);
	tankAI5->SetPosition(glm::vec3(-60.0f, -40.0f, 0.0f));
	AITanks.push_back(tankAI5);
	TankAI* tankAI6 = new TankAI(Static::vaoTank, program, 0.4f, 0.2f, 1.0f, 0.03f, 1.0f);
	tankAI6->SetPosition(glm::vec3(-60.0f, -40.0f, 0.0f));
	AITanks.push_back(tankAI6);
	TankAI* tankAI7 = new TankAI(Static::vaoTank, program, 0.4f, 0.2f, 1.0f, 0.03f, 1.0f);
	tankAI7->SetPosition(glm::vec3(-60.0f, -40.0f, 0.0f));
	AITanks.push_back(tankAI7);
	//a static cube to understand tank's move
	VertexArrayObject* vertexArrayObjectBullet = new VertexArrayObject(rectangular_prism::element_count);
	vertexArrayObjectBullet->AddPositionBuffer(&rectangular_prism::vertices[0]);
	vertexArrayObjectBullet->AddNormalBuffer(&rectangular_prism::normals[0]);
	staticCube = new Drawable(vertexArrayObjectBullet, glm::vec3(0.0f, 0.0f, 0.0f));

	

	glm::mat4 perspective = glm::perspective(glm::radians(60.0F), config::SCREEN_RATIO, 0.1F, 800.0F);
	GLCall(glUniformMatrix4fv(glGetUniformLocation(program, "uPerspective"), 1, GL_FALSE, &perspective[0][0]));
}
int main() {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

	// Open a window and create its OpenGL context
	GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
	window = glfwCreateWindow(1920, 1080, "Tutorial 01", NULL, NULL);
	if (window == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); // Initialize GLEW
	glfwSwapInterval(1);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Couldn't initialize glew");
	}
	
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetKeyCallback(window, KeyCallBack);
	setup();
	while (!glfwWindowShouldClose(window))
	{
		
		
		KeyStateUpdate();
		/* Render here */
		
		//	Clear the color buffer and depth buffer
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		if (tankPlayer->health < 0) {
			glm::vec3 pos = tankPlayer->GetPos();
			delete tankPlayer->drawable;
			tankPlayer->drawable = new Drawable(Static::vaoBullet,glm::vec3(0.0f,0.0f,0.0f));
			tankPlayer->SetPosition(pos);
		}
		tankPlayer->Update(AITanks);
		for (int i = 0; i < AITanks.size(); i++) {
			AITanks[i]->Update(tankPlayer);
			if (AITanks[i]->health < 0) {
				AITanks.erase(AITanks.begin() + i);
			}
		}
		staticCube->Draw(program);
		Static::drawableOuterSurface->Draw(program);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	Static::DeleteDrawables();
	Static::DeleteVAOS();
	glfwTerminate();
}