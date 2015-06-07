#include "stdafx.h"
<<<<<<< HEAD
=======

>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76
#include "Character.h"
#include <cmath>
#include <algorithm>
#include <limits>


<<<<<<< HEAD
GameObject::GameObject(){}
GameObject::GameObject(GLboolean isSolid, GLboolean destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos){
	
=======
GameObject::GameObject(GLboolean isSolid, GLboolean destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos){
>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76
	IsSolid = isSolid;
	Destroyed = destroyed;
	Height = height;
	Width = width;
	Xpos = xpos;
	Ypos = ypos;
<<<<<<< HEAD
	xVelocity = 0;
	yVelocity = 0;
	remove = false;
	movelength = Ypos;
=======

>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76
}
GLboolean GameObject::checkCollision(GameObject a, GameObject b){

	
	return (a.Xpos <= b.Xpos + b.Width &&
		b.Xpos <= a.Xpos + a.Width &&
		a.Ypos <= b.Ypos + b.Height &&
		b.Ypos <= a.Ypos + a.Height);
	   
}

<<<<<<< HEAD
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
	


=======
GLfloat GameObject::checkCollision2(GameObject a, GameObject b, GLfloat& normalx, GLfloat& normaly)
{
	//NEW COLLISION DECTECTION METHOD
	GLfloat xInvEntry, yInvEntry;
	GLfloat xInvExit, yInvExit;
		    // find the distance between the objects on the near and far sides for both x and y
		if (a.xVelocity > 0.0f)
		 {
		xInvEntry = b.Xpos - (a.Xpos + a.Width);
		xInvExit = (b.Xpos + b.Width) - a.Xpos;
		
			}
		else{
			
		    xInvEntry = (b.Xpos + b.Width) - a.Xpos;
			xInvExit = b.Xpos - (a.Xpos + a.Width);
			
				
		}
		if (a.yVelocity > 0.0f)
			 {
			yInvEntry = b.Ypos - (a.Ypos + a.Height);
			yInvExit = (b.Ypos + b.Height) - a.Ypos;
			}
		else{
			yInvEntry = (b.Ypos + b.Height) - a.Ypos;
			yInvExit = b.Ypos - (a.Ypos + a.Width);
			
				
		}
		
	   GLfloat xEntry, yEntry;
		GLfloat xExit, yExit;
		
				    // find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
			
			if (a.xVelocity == 0.0f)
			 {
			xEntry = -std::numeric_limits<float>::infinity();
			xExit = std::numeric_limits<float>::infinity();
			}
			else {
				xEntry = xInvEntry / a.xVelocity;
				xExit = xInvExit / a.xVelocity;
				
			}
			
				if (a.yVelocity == 0.0f)
				 {
				xEntry = -std::numeric_limits<float>::infinity();
				xExit = std::numeric_limits<float>::infinity();
				
					}
				else {
					yEntry = yInvEntry / a.yVelocity;
					yExit = yInvExit / a.yVelocity;
					
				}
						    // find the earliest/latest times of collision
				GLfloat entryTime = std::max(xEntry, yEntry);
				GLfloat exitTime = std::min(xExit, yExit);
						   // if there was no collision
					if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
					 {
					normalx = 0.0f;
					normaly = 0.0f;
					return 1.0f;
					}
				else // if there was a collision
					 {
					        // calculate normal of collided surface
						if (xEntry > yEntry)
						 {
						if (xInvEntry < 0.0f)
							 {
							normalx = 1.0f;
							normaly = 0.0f;
							}
						else
							 {
							normalx = -1.0f;
							normaly = 0.0f;
							}
						}
					else
						 {
						if (yInvEntry < 0.0f)
							{
							normalx = 0.0f;
							normaly = 1.0f;
							}
						else
							 {
							normalx = 0.0f;
							normaly = -1.0f;
							}
						}
					
						       // return the time of collision
						return entryTime;
					}
	

}
>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76
