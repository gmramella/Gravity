/*
* Copyright (c) 2006-2007 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "Build/MyWorld.h"
#include "Build/View.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

/**
Callback de click de mouse da glfw
*/
static void click_callback(GLFWwindow* window, int button, int action, int mode);
/**
Callback de erro da glfw
*/
static void error_callback(int error, const char* description);
/**
Callback de teclado da glfw
*/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
/**
Callback de movimentação de mouse da glfw
*/
static void move_callback(GLFWwindow* window, double xpos, double ypos);
/**
Todo overhead de criação de janela com GLFW escondido em uma funcao
*/
static void initGlfw();

Globals globals;
MyWorld myWorld = MyWorld(globals);

float xMin = -320, xMax = 320, yMin = -320, yMax = 320; //ortho2D

GLFWwindow* window;
int moveUp = 0;
int moveRight = 0;

int main(int argc, char** argv)
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	srand((unsigned int)time(NULL));

	initGlfw();

	myWorld.InitBox2D();
	myWorld.CreateBodies();
	View view;

	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int w, h;
		glfwGetFramebufferSize(window, &w, &h);
		glViewport(0, 0, w, h);
		glClearColor(1, 1, 1, 0);
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (w >= h)
		{
			ratio = w / (float)h;
			glOrtho(xMin*ratio, xMax*ratio, yMin, yMax, -1, 1);
		}
		else
		{
			ratio = h / (float)w;
			glOrtho(xMin, xMax, yMin*ratio, yMax*ratio, -1, 1);
		}
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glfwGetWindowSize(window, &globals.width, &globals.height);

		myWorld.RunBox2D();
		myWorld.Delete();
		view.Render(myWorld.world);
		//view.PrintBodies(myWorld.world);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
	return 0;
}

static void click_callback(GLFWwindow* window, int button, int action, int mode)
{
	/*if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	std::cout << "Clicou esquerdo" << std::endl;
	if (button == GLFW_MOUSE_BUTTON_MIDDLE && action == GLFW_PRESS)
	std::cout << "Clicou meio" << std::endl;
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	std::cout << "Clicou direito" << std::endl;*/
}

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_SPACE && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		myWorld.boost = true;
		b2Vec2 nave = myWorld.bodies[2]->GetPosition();
		printf("%f %f %f %f\r\n", nave.x, nave.y, myWorld.xPos, myWorld.yPos);
	}
	else if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		myWorld.boost = false;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		moveUp += 1;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		moveUp -= 1;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		moveUp += -1;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		moveUp -= -1;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		moveRight += -1;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		moveRight -= -1;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		moveRight += 1;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		moveRight -= 1;
	}
	float32 len = sqrtf(moveUp * moveUp + moveRight * moveRight);
	if (len == 0) len = 1;
	myWorld.movement = b2Vec2(moveRight / len, moveUp / len);
}

static void move_callback(GLFWwindow* window, double xpos, double ypos)
{
	myWorld.xPos = xpos - globals.width/2;
	myWorld.yPos = ypos - globals.height/2;
	//std::cout << "Moveu mouse para (" << myWorld.xPos << ", " << myWorld.yPos << ")" << std::endl;
}

void initGlfw()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(960, 960, "HELLO GLFW!! BYE BYE GLUT!!!", NULL, NULL);
	glfwGetWindowSize(window, &globals.width, &globals.height);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, click_callback);
	glfwSetCursorPosCallback(window, move_callback);
}
