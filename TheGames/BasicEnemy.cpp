#include "stdafx.h"
#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(){};
BasicEnemy::BasicEnemy(GLboolean IsSolid, GLboolean Destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos)
           :GameObject(IsSolid, Destroyed, height, width, xpos, ypos){

	xVelocity = 0.0f;
	yVelocity = 0.0f;
	
};

void BasicEnemy::Draw(){
	glBindTexture(GL_TEXTURE_2D, texture);
	glPushMatrix();
	glEnable(GL_BLEND);// enable transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 0.0, 0.0, 0.0); //set square to transparent
	glBegin(GL_QUADS);
	glVertex2f(Xpos, Ypos);
	glVertex2f(Xpos + Width, Ypos);
	glVertex2f(Xpos + Width, Ypos + Height);
	glVertex2f(Xpos, Ypos + Height);
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

};

void BasicEnemy::remove(){

};
void BasicEnemy::PlayerCollision(GameObject player)
{

};

