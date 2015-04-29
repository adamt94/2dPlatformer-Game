#include "stdafx.h"
#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(){};
BasicEnemy::BasicEnemy(GLboolean IsSolid, GLboolean Destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos)
           :GameObject(IsSolid, Destroyed, height, width, xpos, ypos){
	ID = 4;//enemy ID
	xVelocity = 0.0f;
	yVelocity = 0.0f;
	dead = false;
	
};

void BasicEnemy::Draw(){
	for (BasicEnemy a : this->enemies)
	{
		if (!a.dead)
		{

			glBindTexture(GL_TEXTURE_2D, texture);
			glPushMatrix();
			glEnable(GL_BLEND);// enable transparency
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(1.0, 0.0, 0.0, 0.0); //set square to transparent
			glBegin(GL_QUADS);
			glVertex2f(a.Xpos, a.Ypos);
			glVertex2f(a.Xpos + a.Width, a.Ypos);
			glVertex2f(a.Xpos + a.Width, a.Ypos + a.Height);
			glVertex2f(a.Xpos, a.Ypos + a.Height);
			glEnd();

			glPopMatrix();

			//put texture ontop of square
			glEnable(GL_TEXTURE_2D);
			glColor3f(1, 1, 1);//this becomes transparent
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);	glVertex2f(a.Xpos, a.Ypos);
			glTexCoord2f(1.0, 0.0); glVertex2f(a.Xpos + a.Width, a.Ypos);
			glTexCoord2f(1.0, 1.0); glVertex2f(a.Xpos + a.Width, a.Ypos + a.Height);
			glTexCoord2f(0.0, 1.0); glVertex2f(a.Xpos, a.Ypos + a.Height);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
		}
	}

};

void BasicEnemy::remove(){
	dead = true;
};

void BasicEnemy::Right(){
	if (xVelocity<(emaxSpeed))
	{
		xVelocity += 2.2f;
	}
}
void BasicEnemy::Left(){
	if (xVelocity>(-emaxSpeed))
	{
		xVelocity -= 2.2f;

	}
}
void BasicEnemy::addEnemy(GLfloat xpos, GLfloat ypos){

		 BasicEnemy enem(true, true, 32.0f, 32.0f, xpos, ypos);
	
		 this->enemies.push_back(enem);
	
}
void BasicEnemy::PlayerCollision(GameObject player,BasicEnemy enemy)
{
	


};


