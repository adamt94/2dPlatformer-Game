#include "stdafx.h"




#include "Character.h"
using namespace std;




Character::Character(GLboolean IsSolid, GLboolean Destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos)
	:GameObject(IsSolid, Destroyed, height, width, xpos, ypos)
{
	xVelocity = 0.0f; 
	yVelocity = 0.0f;
	jump = false;
	glClearColor(0.0, 0.0, 0.0, 0.0);

	
	
}
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
void Character::Up(){
	
	if (upintheair&&DoubleJumpReady&&yVelocity<10.0f)
	{
		Doublejump = true;
		yVelocity = 1000.0f;
		DoubleJumpReady = false;
	}

	if(jump)
	{
	   jump = false;
	 
		  
			  yVelocity = 800.2f;
			  upintheair = true;
	}
	

	
	
}
void Character::Down(){
	//increases speed until max
	if(yVelocity>(-maxSpeed))
	{
	 // yVelocity-=2.2f;
	}
	
	
}
void Character::Right(){
	playerleft = false;
	//increases speed until max
	if(xVelocity<maxSpeed)
	{
	  xVelocity+=2.2f;
	}
	
	
}
void Character::Left(){
	playerleft = true;
	//increases speed until max
	if(xVelocity>(-maxSpeed))
	{
	  xVelocity-=2.2f;
	}
	
}


