#include "stdafx.h"

#include <iostream>
#include <cmath>

#include "Game.h"
#include "Character.h"
#include "GameLevel.h"

using namespace std;
Character Player = Character(true,true,32.0f,32.0f,500,300);
GameLevel level = GameLevel();

const GLfloat resistance = 02.0f;
const GLfloat gravity = -0.15f;
Game::Game(GLuint width, GLuint height)
: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

void Game::Init(){
	
	level.Load("lvltest.txt",1000 , 600);
	
	
   
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
		
		
	}
}
void Game::Update(GLfloat dt){
	if(Player.yVelocity>-200.0f)//max acceleration downwards
	{
	   Player.yVelocity  +=gravity;//apply gravity
	}
	
	
	//adds resistance to slow character down
	if(Player.xVelocity>1){
		Player.xVelocity -= resistance;
	}
	if(Player.xVelocity<-1){
		
		Player.xVelocity += resistance;
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
	
	

}
void Game::Render(){
	if (this->State == GAME_ACTIVE || this->State == GAME_MENU || this->State == GAME_WIN){
		glClear(GL_COLOR_BUFFER_BIT);
	
		glLoadIdentity();
				//camera follows player
		 glTranslatef(-(Player.Xpos)+500,-Player.Ypos+250,0.0);
		 //check collisions
		 DoCollision();
		  level.Draw();
		//draw the objects to screen
		Player.draw();
	
	//	glLoadIdentity();
		
		
	     
		
		glFlush();
		
	}
}

void Game::ResetLevel(){
	//reset level when player loses
}
void Game::DoCollision(){
	GLboolean checkJump;
	for (GameObject &tile : level.Bricks){

		if (Player.checkCollision(Player, tile) == true)
		{
				


				GLfloat left = tile.Xpos - (Player.Xpos + Player.Width);
				GLfloat right = (tile.Xpos + tile.Width) - Player.Xpos;
				GLfloat top = tile.Ypos - (Player.Ypos+ Player.Height);
				GLfloat bottom = (tile.Ypos + tile.Width) - Player.Ypos;
				GLfloat mtdX;
				GLfloat mtdY;
			
			    Player.jump = false;// when collision player can jump
				if(abs(left)<right)
				{
				//	Player.xVelocity = 0;
					mtdX = left;
				
				}
				else {
					//Player.xVelocity = 0;
					mtdX = right;
				}
				if(abs(top)< bottom)
				{
			
					mtdY = top;
				}
				else{
					
					Player.jump = true;// when collision player can jump
					mtdY = bottom;
				}

				if(abs(mtdX) < abs(mtdY))
				{
					
					mtdY =0;
				}
				else{
				 
					mtdX = 0;
				}
				
				Player.Ypos += mtdY;
				Player.Xpos += mtdX;


				
		}

		 




		














		//do something when checkcollision(); is true
	}
}