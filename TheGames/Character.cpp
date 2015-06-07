#include "stdafx.h"

<<<<<<< HEAD



#include "Character.h"
using namespace std;




Character::Character(GLboolean IsSolid, GLboolean Destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos)
	:GameObject(IsSolid, Destroyed, height, width, xpos, ypos)
{
	ID = 3;
	xVelocity = 0.0f; 
	yVelocity = 0.0f;
	jump = false;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	Score = 0;

=======
#include <iostream>

#include "LTexture.h"
#include "Character.h"

using namespace std;



LTexture t;
Character::Character(GLboolean IsSolid, GLboolean Destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos)
	:GameObject(IsSolid, Destroyed, height, width, xpos, ypos)
{
	Xpos = 70.0f;
	Ypos = 40.0f;
	xVelocity = 0.0f; 
	yVelocity = 0.0f;

	jump = false;
	t.loadTextureFromFile("characterstandingpos.png");
>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76

	
	
}
<<<<<<< HEAD

void Character::draw(){
	if (playerleft == false){ 
		glBindTexture(GL_TEXTURE_2D, myTexture);//walking right texture
	}
	else{
		glBindTexture(GL_TEXTURE_2D, leftpos); //walking left texture
	}
	if (Doublejump)
	{

		if (playerleft){
			glBindTexture(GL_TEXTURE_2D, jetpackTexutureleft);//jepack right texture
		}
		else{
			glBindTexture(GL_TEXTURE_2D, jetpackTexture);//jetpack left texture
		}
	}
	
	
	glPushMatrix();
	glEnable(GL_BLEND);// enable transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 0.0, 0.0,0.0); //set square to transparent
		glBegin(GL_QUADS);
			glVertex2f(Xpos,Ypos);
			glVertex2f(Xpos+Width,Ypos);
			glVertex2f(Xpos+Width,Ypos+Height);
			glVertex2f(Xpos,Ypos+Height);
		glEnd();
		
	glPopMatrix();

	//put texture ontop of square
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);//this becomes transparent
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);	glVertex2f(Xpos, Ypos);
	glTexCoord2f(1.0, 0.0); glVertex2f(Xpos + Width, Ypos);
	glTexCoord2f(1.0, 1.0); glVertex2f(Xpos + Width, Ypos + Height);
	glTexCoord2f(0.0, 1.0); glVertex2f(Xpos, Ypos + Height);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	
}
void Character::Up(GLfloat dt){
	int jumpheight = Ypos;
	if (upintheair&&DoubleJumpReady&&yVelocity<10.0f)
	{
		Doublejump = true;
		
			 
			yVelocity = 300.0f;
	
		DoubleJumpReady = false;
	}

	if(jump)
	{
	   jump = false;
	 
	  
	  
		  
		   yVelocity = 200.0f;
	   
			  upintheair = true;
	}
	

	
=======
void Character::draw(){
	//
	//glPushMatrix();
	//glColor3f(1.0, 0.0, 0.0);
	//	glBegin(GL_QUADS);
	//		glVertex3f(Xpos,Ypos,0.0);
	//		glVertex3f(Xpos+Width,Ypos,0.0);
	//		glVertex3f(Xpos+Width,Ypos+Height,0.0);
	//		glVertex3f(Xpos,Ypos+Height,0.0);
	//	glEnd();
	//glPopMatrix();
	t.render(Xpos,Ypos,Width,Height);
	
	
	
}
void Character::Up(){
	//jump again when reaches ground
	if(jump)
	{
	   jump = false;
	
	//increases speed until max jump height
	  while(yVelocity<maxJump)
	  {
		
	     yVelocity+=50.2f;
      }
	}
>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76
	
}
void Character::Down(){
	//increases speed until max
	if(yVelocity>(-maxSpeed))
	{
	 // yVelocity-=2.2f;
	}
	
	
}
void Character::Right(){
<<<<<<< HEAD
	playerleft = false;
	//increases speed until max
	if(xVelocity<maxSpeed)
	{
	  xVelocity+=4.2f;
	}
	
	
}
void Character::Left(){
	playerleft = true;
	//increases speed until max
	if(xVelocity>(-maxSpeed))
	{
	  xVelocity-=4.2f;
	}
	
}


=======
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
>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76
