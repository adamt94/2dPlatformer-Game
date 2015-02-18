#ifndef GameObject_H
#define GameObject_H
#include <iostream>
#include "stdafx.h"
#include <GLFW/glfw3.h>
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
	GLfloat     Xpos;
	GLfloat		Ypos;

	// Render state

	// Constructor(s)
	GameObject(GLboolean isSolid, GLboolean destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos);
	void Collision();
	
};

#endif