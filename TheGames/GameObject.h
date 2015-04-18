#ifndef GameObject_H
#define GameObject_H
#include <Windows.h>
#include "Image_Loading\nvImage.h"
#include <glew.h>
#include <iostream>
#include "stdafx.h"

#include <GLFW\glfw3.h>
using namespace std;




// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject 
{
public:
	// Object state


	GLboolean   IsSolid;
	GLboolean   Destroyed;
	GLint		Height;
	GLint		Width;
	GLint		ID;
	GLint		movelength;
	GLfloat     Xpos;
	GLfloat		Ypos;
	GLboolean	remove;
	GLfloat xVelocity,yVelocity;

	// Render state

	// Constructor(s)
	GameObject();
	GameObject(GLboolean isSolid, GLboolean destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos);
	GLboolean checkCollision(GameObject a, GameObject b);
	void Draw();
	GLuint loadPNG(char* name);
	
};

#endif