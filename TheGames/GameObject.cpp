#include "stdafx.h"
#include "Character.h"
#include <cmath>
#include <algorithm>
#include <limits>


GameObject::GameObject(){}
GameObject::GameObject(GLboolean isSolid, GLboolean destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos){
	IsSolid = isSolid;
	Destroyed = destroyed;
	Height = height;
	Width = width;
	Xpos = xpos;
	Ypos = ypos;

}
GLboolean GameObject::checkCollision(GameObject a, GameObject b){

	
	return (a.Xpos <= b.Xpos + b.Width &&
		b.Xpos <= a.Xpos + a.Width &&
		a.Ypos <= b.Ypos + b.Height &&
		b.Ypos <= a.Ypos + a.Height);
	   
}

GLuint GameObject::loadPNG(char* name)
{
	nv::Image img;

	GLuint myTextureID;

	// Return true on success
	if (img.loadImageFromFile(name))
	{
		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}

	else
		MessageBox(NULL, L"Failed to load texture", L"End of the world", MB_OK | MB_ICONINFORMATION);

	return myTextureID;

}
	


