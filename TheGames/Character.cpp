#include "stdafx.h"
#include <iostream>


#include "Character.h"
using namespace std;




Character::Character(GLboolean IsSolid, GLboolean Destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos)
	:GameObject(IsSolid, Destroyed, height, width, xpos, ypos)
{
	Xpos = 0.0f;
	Ypos = 0.0f;
	xVelocity = 0.0f; 
	yVelocity = 0.0f;
	
}
void Character::draw(){
	
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(Xpos, Ypos, 0.0);
		glBegin(GL_QUADS);
			glVertex3f(Xpos,Ypos,0);
			glVertex3f(Xpos+Width,Ypos,0);
			glVertex3f(Xpos+Width,Ypos+Height,0);
			glVertex3f(Xpos,Ypos+Height,0);
		glEnd();
	glPopMatrix();
	
	
	
}
void Character::Up(){
	//increases speed until max
	if(yVelocity<maxSpeed)
	{
	  yVelocity+=2.2f;
	}
	
}
void Character::Down(){
	//increases speed until max
	if(yVelocity>(-maxSpeed))
	{
	  yVelocity-=2.2f;
	}
	
	
}
void Character::Right(){
	//increases speed until max
	if(xVelocity<maxSpeed)
	{
	  xVelocity+=2.2f;
	}
	
}
void Character::Left(){
	//increases speed until max
	if(xVelocity>(-maxSpeed))
	{
	  xVelocity-=2.2f;
	}
	
}
