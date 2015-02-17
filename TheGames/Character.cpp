#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <gl/glu.h>
#include <gl/GL.h>
#include "Character.h"
using namespace std;

GLfloat Height, Width, Xpos, Ypos, xVelocity, yVelocity;
const GLfloat friction = 0.57;
const GLfloat maxSpeed = 350.0f;
Character::Character(GLfloat height, GLfloat width, GLfloat xpos, GLfloat ypos, GLfloat xVel, GLfloat yVel)
{
	Height = height;
	Width = width;
	Xpos = xpos;
	Ypos = ypos;
	xVelocity = xVel;
	yVelocity = yVel;
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
void Character::movement(){
	//slow down if player has let got of movement key
	
	
}