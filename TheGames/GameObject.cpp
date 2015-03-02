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
GLboolean GameObject::checkCollision(GameObject a, GameObject b){
	//if ((-100 < Xtri + 4) && (100 > Xtri - 4) && (-8 - 50 < Ytri + 5.65) && (8 - 50 > Ytri - 4))
	if (a.Xpos < b.Xpos + b.Width &&
		a.Xpos + b.Width > b.Xpos &&
		a.Ypos < b.Ypos + b.Height &&
		a.Height + a.Ypos > b.Ypos) 
		// collision detected!
	
	{
		
		return true;
	}

}