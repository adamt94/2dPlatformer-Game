#include "stdafx.h"

#include <iostream>
#include "Game.h"
#include "Character.h"
using namespace std;
Character Player(100.0f,-100.0f,500,300,0.0f,200.0f);

Game::Game(GLuint width, GLuint height)
: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

void Game::Init(){}


void Game::ProcessInput(GLfloat dt){

	if (this->State == GAME_ACTIVE){
		if (this->Keys[GLFW_KEY_W])//up
		{
			
			Player.Ypos += Player.yVelocity*dt;
			
		}
		if (this->Keys[GLFW_KEY_S])//down
		{
			Player.Ypos += -Player.yVelocity*dt;
		}
		if (this->Keys[GLFW_KEY_D])//right
		{
			
			Player.Xpos += Player.xVelocity*dt;
		
		}
		if (this->Keys[GLFW_KEY_A])//left
		{
			
			Player.Xpos += Player.xVelocity*dt;
		}
		
		
	}
}
void Game::Update(GLfloat dt){
	
	

}
void Game::Render(){
	if (this->State == GAME_ACTIVE || this->State == GAME_MENU || this->State == GAME_WIN){
		glClear(GL_COLOR_BUFFER_BIT);

		glLoadIdentity();
		//draw the objects to screen
		Player.draw();
		Player.movement();
		glFlush();
		
	}
}

void Game::ResetLevel(){
	//reset level when player loses
}
void Game::DoCollision(){
	//check when theres are collision between objects
}