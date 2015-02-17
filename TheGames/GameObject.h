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

	GLfloat     Rotation;
	GLboolean   IsSolid;
	GLboolean   Destroyed;
	// Render state

	// Constructor(s)s
	GameObject();

};

#endif