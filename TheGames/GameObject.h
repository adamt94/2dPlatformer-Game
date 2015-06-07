#ifndef GameObject_H
#define GameObject_H
<<<<<<< HEAD
#include <Windows.h>
#include "Image_Loading\nvImage.h"
#include <glew.h>
#include <iostream>
#include "stdafx.h"

#include <GLFW\glfw3.h>
=======

#include <iostream>
#include "stdafx.h"

#include <GLFW/glfw3.h>
>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76
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
<<<<<<< HEAD
	GLint		ID;
	GLint		movelength;
	GLfloat     Xpos;
	GLfloat		Ypos;
	GLboolean	remove;
=======
	GLfloat     Xpos;
	GLfloat		Ypos;
	
>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76
	GLfloat xVelocity,yVelocity;

	// Render state

	// Constructor(s)
<<<<<<< HEAD
	GameObject();
	GameObject(GLboolean isSolid, GLboolean destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos);
	GLboolean checkCollision(GameObject a, GameObject b);
	void Draw();
	GLuint loadPNG(char* name);
=======
	GameObject(GLboolean isSolid, GLboolean destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos);
	GLboolean checkCollision(GameObject a, GameObject b);
	GLfloat checkCollision2(GameObject a, GameObject b, GLfloat& normalyx, GLfloat& normaly);
	void Draw();
>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76
	
};

#endif