#include "stdafx.h"
#include <iostream>


#include "Character.h"
using namespace std;




Character::Character(GLboolean IsSolid, GLboolean Destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos)
	:GameObject(IsSolid, Destroyed, height, width, xpos, ypos)
{
	
	xVelocity = 0.0f; 
	yVelocity = 0.0f;
	
}
void Character::draw(){
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(Xpos, Ypos, 0.0);
	glBegin(GL_QUADS);
	glVertex3f(-10.5f, -10.5f, 0.0); // The bottom left corner  
	glVertex3f(-10.5f, 10.5f, 0.0); // The top left corner  
	glVertex3f(10.5f, 10.5f, 0.0); // The top right corner  
	glVertex3f(10.5f, -10.5f, 0.0); // Start drawing a quad primitive  
	glEnd();
	glPopMatrix();
	
}
void Character::Up(){
	//increases speed until max
	if(yVelocity<maxSpeed)
	{
	  yVelocity+=5.0f;
	}
	
}
void Character::Down(){
	//increases speed until max
	if(yVelocity>(-maxSpeed))
	{
	  yVelocity-=5.0f;
	}
	
	
}
void Character::Right(){
	//increases speed until max
	if(xVelocity<maxSpeed)
	{
	  xVelocity+=5.0f;
	}
	
}
void Character::Left(){
	//increases speed until max
	if(xVelocity>(-maxSpeed))
	{
	  xVelocity-=5.0f;
	}
	
}
