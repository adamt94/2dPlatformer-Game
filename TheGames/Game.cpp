#include "stdafx.h"
#include <glew.h>
#include <iostream>
#include <cmath>
#include "Game.h"
#include "BasicEnemy.h"
#include "Character.h"
#include "GameLevel.h"
#include <GLFW\glfw3.h>
using namespace std;
Character Player = Character(true,true,32.0f,32.0f,70,40);
GameLevel level = GameLevel();
BasicEnemy Enemy = BasicEnemy(true,true,32.0f,32.0f,140,40);
const GLfloat resistance = 02.0f;
const GLfloat gravity = -1.15f;
Game::Game(GLuint width, GLuint height)
: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

void Game::Init(){
	
	level.Load("lvltest.txt",1000 , 600);

	Player.myTexture = Player.loadPNG("characterstandingpos.png");
	level.myTexture = level.loadPNG("platform.png");
	Background = level.loadPNG("gamebackground.png");
	Player.leftpos = Player.loadPNG("characterstandingpos(left).png");
	Player.jetpackTexture = Player.loadPNG("characterstandingpos(jetpack).png");
	Player.jetpackTexutureleft = Player.loadPNG("characterstandingpos(jetpackleft).png");
	Enemy.texture = Enemy.loadPNG("enemy.png");
   
}


void Game::ProcessInput(GLfloat dt){

	if (this->State == GAME_ACTIVE){
		if (this->Keys[GLFW_KEY_W])//up
		{
	
			
				Player.Up();
			
	
			
		}
		if (this->Keys[GLFW_KEY_S])//down
		{
			Player.Down();
		}
		if (this->Keys[GLFW_KEY_D])//right
		{
			
			
			Player.Right();
		
		}
		if (this->Keys[GLFW_KEY_A])//left
		{
			
			Player.Left();
		}
		if (this->Keys[GLFW_KEY_R])//resetlevel
		{
			ResetLevel();
		}
		
		
	}
}
void Game::Update(GLfloat dt){
	if(Player.yVelocity>-500.0f)//max acceleration downwards
	{
	   Player.yVelocity  +=gravity;//apply gravity
	}
	if (Enemy.yVelocity>-500.0f)//max acceleration downwards
	{
		Enemy.yVelocity += gravity;//apply gravity
	}
	
	//adds resistance to slow character down
	if(Player.xVelocity>1){
		Player.xVelocity -= resistance;
	}
	else if(Player.xVelocity<-1){
		
		Player.xVelocity += resistance;
	}
	else{
		Player.xVelocity = 0;
	}
	if(Player.yVelocity>1){
		Player.yVelocity -= resistance;
	}
	if(Player.yVelocity<-1){
		//Player.yVelocity += resistance;
	}
	
	//update player position
	Player.Xpos += Player.xVelocity*dt;
	Player.Ypos += (Player.yVelocity*dt);
	//update enemys positions
	Enemy.Xpos += Enemy.xVelocity*dt;
	Enemy.Ypos += (Enemy.yVelocity*dt);
	
	

}
void Game::Render(){
	if (this->State == GAME_ACTIVE || this->State == GAME_MENU || this->State == GAME_WIN){
		glClear(GL_COLOR_BUFFER_BIT);
		drawBackground();
		glLoadIdentity();
		//camera follows player
		if (-(Player.Xpos) + 500 < 0 )
		{


			glTranslatef(-(Player.Xpos) + 500, 0.0, 0.0);
		}
		if (-(Player.Ypos) + 250 < 0)
		{

			glTranslatef(0.0, -(Player.Ypos)+250, 0.0);
		}
		 
		 //check collisions
		 DoCollision();
		  level.Draw();
		//draw the objects to screen
		Player.draw();
		Enemy.Draw();
	
	//	glLoadIdentity();
		
		
	     
		
		glFlush();
		
	}
}

void Game::ResetLevel(){
	 Player = Character(true, true, 32.0f, 32.0f, 500, 300);
	 level = GameLevel();
	 Init();
	//reset level when player loses
}
void Game::DoCollision(){
	GLboolean checkJump;
	for (GameObject &tile : level.Bricks){

		if (Player.checkCollision(Player, tile) == true)//if there was a collison
		{
				


			/*	GLfloat left = tile.Xpos - (Player.Xpos + Player.Width);
				GLfloat right = (tile.Xpos + tile.Width) - Player.Xpos;
				GLfloat top = tile.Ypos - (Player.Ypos+ Player.Height);
				GLfloat bottom = (tile.Ypos + tile.Width) - Player.Ypos;
				GLfloat mtdX;//minmun translation distance
				GLfloat mtdY;
			
					Player.jump = false;
				//calulcate the mtd of the axis
				if(abs(left)<right)
				{
					
					mtdX = left;
				
				}
				else {
					
					mtdX = right;
				}
				//calculate the mtd of the y axis
				if(abs(top)< bottom)
				{
			
					mtdY = top;
				}
				else{
					
					Player.jump = true;// when on the bottom enable jump
					Player.upintheair = false; //upon landing, reset to false
					Player.DoubleJumpReady = true; //upon landing, reset to true
					mtdY = bottom;
					Player.Doublejump = false;//end of double jump so can change texture
				}
				//assign  the largest mtd to 0 so player is moved the mtd on collision
				if(abs(mtdX) < abs(mtdY))
				{
					
					mtdY =0;
				}
				else{
				 
					mtdX = 0;
				}*/
				//move the players position out of collision
			    vector<GLfloat> mtd = CalculateMinTrasnlation(tile);
				
				Player.Ypos += mtd[1];
				Player.Xpos += mtd[0];
				if (mtd[0] != 0)
				{
					Player.xVelocity = -Player.xVelocity; //* creates a bounce when thers a collision in x axis
					}
				else if (mtd[1] != 0)
				{
					Player.yVelocity = -Player.yVelocity/4;//* creates a bounce when thers a collision in y axis
				}


				
		}

		 





	}
}

void Game::drawBackground(){
	glBindTexture(GL_TEXTURE_2D, Background);
	glPushMatrix();
	glEnable(GL_BLEND);// enable transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 0.0, 0.0, 0.0); //set square to transparent
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0 + 2000,0);
	glVertex2f(0 + 2000, 0 + 1200);
	glVertex2f(0, 0 + 1200);
	glEnd();

	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);//this becomes transparent
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);	glVertex2f(0, 0);
	glTexCoord2f(2.0, 0.0); glVertex2f(0 + 2000, 0);
	glTexCoord2f(2.0, 2.0); glVertex2f(0 + 2000, 0 + 1200);
	glTexCoord2f(0.0, 2.0); glVertex2f(0, 0 + 1200);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}

vector<GLfloat> Game::CalculateMinTrasnlation(GameObject tile){
	vector<GLfloat> mtd(2);
	GLfloat left = tile.Xpos - (Player.Xpos + Player.Width);
	GLfloat right = (tile.Xpos + tile.Width) - Player.Xpos;
	GLfloat top = tile.Ypos - (Player.Ypos + Player.Height);
	GLfloat bottom = (tile.Ypos + tile.Width) - Player.Ypos;
	GLfloat mtdX;//minmun translation distance
	GLfloat mtdY;

	Player.jump = false;
	//calulcate the mtd of the axis
	if (abs(left)<right)
	{

		mtdX = left;

	}
	else {

		mtdX = right;
	}
	//calculate the mtd of the y axis
	if (abs(top)< bottom)
	{

		mtdY = top;
	}
	else{

		Player.jump = true;// when on the bottom enable jump
		Player.upintheair = false; //upon landing, reset to false
		Player.DoubleJumpReady = true; //upon landing, reset to true
		mtdY = bottom;
		Player.Doublejump = false;//end of double jump so can change texture
	}
	//assign  the largest mtd to 0 so player is moved the mtd on collision
	if (abs(mtdX) < abs(mtdY))
	{

		mtdY = 0;
	}
	else{

		mtdX = 0;
	}
	mtd[0] = mtdX;
	mtd[1] = mtdY;
	return mtd;
}