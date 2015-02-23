#include "stdafx.h"
#include "Character.h"

GameObject::GameObject(GLboolean isSolid, GLboolean destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos){
	IsSolid = isSolid;
	Destroyed = destroyed;
	Height = height;
	Width = width;
	Xpos = xpos;
	Ypos = ypos;

}
