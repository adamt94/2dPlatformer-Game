#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glu.h>
#include <gl/GL.h>

#include "Game.h"



using namespace std;
const int WINDOW_WIDTH = 1000;// window width
const int WINDOW_HEIGHT = 600;//window height
Game game(WINDOW_WIDTH, WINDOW_HEIGHT);//game object 
static void error_callback(int error, const char* description)//ERROR MAN
{
	
	fputs(description, stderr);
}
//Proccessing keys
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			game.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
		{
			game.Keys[key] = GL_FALSE;
			game.KeysProcessed[key] = GL_FALSE;
		}
	}

}



int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())//intial
		exit(EXIT_FAILURE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GAME", NULL, NULL);//set up window
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);// focus on window
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);


	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    
	GLfloat  deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;
	//GAME LOOOP
	while (!glfwWindowShouldClose(window))
	{
		//Calculate delta time
		GLfloat  currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glfwPollEvents();
	    
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//Gives a 1 to 1 relationship between screen pixels and coordinates
		gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
		glMatrixMode(GL_MODELVIEW);
		
		//start stuff
		game.ProcessInput(deltaTime);
		game.Update(deltaTime);
		game.Render();
		//glColor3f(1.0, 1.0, 0.0);
		//glBegin(GL_QUADS); 
		//glVertex3f(-10.0f, -10.0f, 0.0f); // The bottom left corner  
		//glVertex3f(-10.0f, 10.0f, 0.0f); // The top left corner  
		//glVertex3f(10.0f, 10.0f, 0.0f); // The top right corner  
		//glVertex3f(10.0f, -10.0f, 0.0f);// Start drawing a quad primitive  
		//glEnd();
			glBegin(GL_QUADS);
	glVertex3f(-10.5f, -10.5f, 0.0); // The bottom left corner  
	glVertex3f(-10.5f, 10.5f, 0.0); // The top left corner  
	glVertex3f(10.5f, 10.5f, 0.0); // The top right corner  
	glVertex3f(10.5f, -10.5f, 0.0); // Start drawing a quad primitive  
	glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}