#include "stdafx.h"
#include <glew.h>
#include <iostream>
#include <cmath>
#include "Game.h"

#include "Character.h"
#include "BasicEnemy.h"
#include "FreeType.h"
#include "GameLevel.h"
#include <GLFW\glfw3.h>
using namespace std;
Character Player = Character(true, true, 32.0f, 32.0f, 140, 40);
GameLevel level = GameLevel();
BasicEnemy Enemy = BasicEnemy();
//BasicEnemy Enemy = BasicEnemy(true,true,32.0f,32.0f,240,40);

const GLfloat resistance = 01.8f;
const GLfloat gravity = -490.5f;
GLboolean movingtile = false;//For keeping player on moving platform
int levelcount = 0;
using namespace freetype;
font_data our_font;
Game::Game(GLuint width, GLuint height)
: State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{
	
}

void Game::Init(){

	our_font.init("kenvector_future.ttf", 22);
	if (levelcount == 0)
	{

		level.Load("lvltest.txt", 1000, 600);
	}
	else if (levelcount==1){
		level.Load("lvl2.txt", 1000, 600);
	}
	for (GameObject a : level.enemiespos)
	{

		Enemy.addEnemy(a.Xpos,a.Ypos);
	}
	

	Player.myTexture = Player.loadPNG("characterstandingpos.png");
	level.myTexture = level.loadPNG("platform.png");
	level.plainTileTexture = level.loadPNG("metalPanel.png");
	level.collectabletexture = level.loadPNG("collectable.png");
	level.goaltexture = level.loadPNG("door.png");
	Background = level.loadPNG("gamebackground.png");
	Player.leftpos = Player.loadPNG("characterstandingpos(left).png");
	Player.jetpackTexture = Player.loadPNG("characterstandingpos(jetpack).png");
	Player.jetpackTexutureleft = Player.loadPNG("characterstandingpos(jetpackleft).png");
	Enemy.texture = Enemy.loadPNG("enemy.png");

	Player.Xpos = level.Playerxpos;//set the players coords on level design
	Player.Ypos = level.Playerypos;
	
}


void Game::ProcessInput(GLfloat dt){

	if (this->State == GAME_ACTIVE){
		if (this->Keys[GLFW_KEY_W])//up
		{
	
			
				Player.Up(dt);
			
	
			
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
	if (Player.remove)
	{
		ResetLevel();
	}
//	if(Player.yVelocity>-500.0f)//max acceleration downwards
	{
		Player.yVelocity -= (gravity*-dt);//apply gravity
	}
	for (BasicEnemy &enem : Enemy.enemies)
	{

		enem.yVelocity -= (gravity*-dt);//apply gravity
	}
		
	//adds resistance to deccelarate character down when let go of movement
	if(Player.xVelocity>1){
		Player.xVelocity -= resistance;
	}
	else if(Player.xVelocity<-1){
		
		Player.xVelocity +=  resistance;
	}
	else{
		Player.xVelocity = 0;
	}
	//max movement speed
	if (Player.xVelocity>180)
	{
		Player.xVelocity = 180.0f;
	}
	if (Player.xVelocity<-180)
	{
		Player.xVelocity = -180.0f;
	}
	for (BasicEnemy &enem : Enemy.enemies)
	{

		if (Player.Xpos > enem.Xpos && (Player.Ypos == enem.Ypos))
		{
			enem.Right();
		}
		else if (Player.Xpos < enem.Xpos&&Player.Ypos == enem.Ypos){
			enem.Left();
		}
		else{
			enem.xVelocity = 0.0f;
		}
	}
	//update player position
	Player.Xpos += Player.xVelocity*dt;
	Player.Ypos += (Player.yVelocity*dt);
	//update enemys positions
	for (BasicEnemy &enem : Enemy.enemies)
	{

		enem.Xpos += enem.xVelocity*dt;
		enem.Ypos += (enem.yVelocity*dt);
	}
	for (GameObject &tile : level.Bricks)//update moving tiles positions
	{
		if (tile.ID == 7||tile.ID == 8)
		{
		
		     tile.Xpos += tile.xVelocity *dt;
			 tile.Ypos += tile.yVelocity*dt;
			
		}
	}
	

}
void Game::Render(){
	if (this->State == GAME_ACTIVE || this->State == GAME_MENU || this->State == GAME_WIN){
		glClear(GL_COLOR_BUFFER_BIT);
		drawBackground();
		glLoadIdentity();
		print(our_font, 790.0, 570.0, "Score:%d", Player.Score);
		//camera follows player
		if (-(Player.Xpos) + 500 < 0)
		{


			glTranslatef(-(Player.Xpos) + 500, 0.0, 0.0);
		}
		if (-(Player.Ypos) + 250 < 0)
		{

			glTranslatef(0.0, -(Player.Ypos) + 250, 0.0);
		}

		//check collisions
		DoCollision();
		level.Draw();
		//draw the objects to screen
		Player.draw();
		for (BasicEnemy &enem : Enemy.enemies)
		{
		if (enem.dead == false)
		{

			Enemy.Draw();

		}
	}
	
	//	glLoadIdentity();
		
		//fonts
	
	     
		
		glFlush();
		
	}
}

void Game::ResetLevel(){

	 Player = Character(true, true, 32.0f, 32.0f, 70, 40);
	 Enemy.enemies.clear();
	 level = GameLevel();
	 Init();
	//reset level when player loses
}
void Game::DoCollision(){
	GLboolean checkJump;
	GLboolean goal = false;
	GLboolean Playerdied = false;

	for (GameObject &tile : level.Bricks){
		for (BasicEnemy &enem : Enemy.enemies)
		{

			if (enem.checkCollision(enem, tile) == true)

			{

				vector<GLfloat> mtd = CalculateMinTrasnlation(tile, enem, FALSE);

				enem.Ypos += mtd[1];
				enem.Xpos += mtd[0];
				if (mtd[0] != 0)
				{
					enem.xVelocity = -enem.xVelocity; //* creates a bounce when thers a collision in x axis
				}
				else if (mtd[1] != 0)
				{
					enem.yVelocity = -enem.yVelocity / 4;//* creates a bounce when thers a collision in y axis
				}

			}
			if (Player.checkCollision(Player, tile) == true)//if there was a collison
			{
				if (tile.IsSolid)
				{

					vector<GLfloat> mtd = CalculateMinTrasnlation(tile, Player, TRUE);

					Player.Ypos += mtd[1];
					Player.Xpos += mtd[0];
					if (mtd[0] != 0)
					{
						Player.xVelocity = -Player.xVelocity; //* creates a bounce when thers a collision in x axis
					}
					else if (mtd[1] != 0)
					{
						Player.yVelocity = -Player.yVelocity / 4;//* creates a bounce when thers a collision in y axis
					}
				}

				if (tile.ID == 2)
				{
					levelcount++;

					goal = true;// reached the goal of the level
				}
				if (tile.ID == 5)
				{
					if (tile.Destroyed == false)
					{

						Player.Score += 10;// add to player score and destroy the tile
					}
					tile.Destroyed = true;
				}
				if (tile.ID == 7)
				{

					if (Player.xVelocity < 100.0f)//if player is less then platform speed
					{


						Player.xVelocity = tile.xVelocity; // match player velocity with tile to keep on platform
					}



				}

			}

			if (tile.ID == 7)
			{

				if (tile.movelength >= tile.Xpos && tile.movelength<tile.Xpos + 1)
				{
					tile.xVelocity = 100.0f;
				}
				if (tile.Xpos > tile.movelength + 300)
				{

					tile.xVelocity = -100.0f;
				}


			}
			if (tile.ID == 8)
			{

				if (tile.movelength >= tile.Ypos && tile.movelength<tile.Ypos + 1)
				{
					tile.yVelocity = 100.0f;
				}
				if (tile.Ypos > tile.movelength + 300)
				{

					tile.yVelocity = -100.0f;
				}


			}





			
			if (Player.checkCollision(Player, enem) == true && enem.dead == false)
			{
			
				if (PlayerEnemyCollision(Player, enem)==false)
				{
					enem.dead = true;
				}
				
				else {
					Playerdied = true;
				}
				
				
				// check if player collide with enemy and resolve it
			}
		}
	}
	if (goal||Playerdied)
		ResetLevel();//if player reacher goal
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

vector<GLfloat> Game::CalculateMinTrasnlation(GameObject tile, GameObject player, GLboolean isPlayer){
	
	vector<GLfloat> mtd(2);
	GLfloat left = tile.Xpos - (player.Xpos + player.Width);
	GLfloat right = (tile.Xpos + tile.Width) - player.Xpos;
	GLfloat top = tile.Ypos - (player.Ypos + player.Height);
	GLfloat bottom = (tile.Ypos + tile.Width) - player.Ypos;
	GLfloat mtdX;//minmun translation distance
	GLfloat mtdY;
	

		//Player.jump = false;
		//calulcate the mtd of the axis
		if (abs(left) < right)
		{

			mtdX = left;

		}
		else {

			mtdX = right;
		}
		//calculate the mtd of the y axis
		if (abs(top) < bottom)
		{

			mtdY = top;
		}
		else{
			mtdY = bottom;
			if (isPlayer && (mtdY < mtdX))//check if it wasnt a horizontal collision
			{

				Player.jump = true;// when on the bottom enable jump
				Player.upintheair = false; //upon landing, reset to false
				Player.DoubleJumpReady = true; //upon landing, reset to true
				Player.Doublejump = false;//end of double jump so can change texture
			}

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

GLboolean Game::PlayerEnemyCollision(GameObject player, GameObject enemy){
	GLfloat left = player.Xpos - (enemy.Xpos + enemy.Width);
	GLfloat right = (player.Xpos + player.Width) - enemy.Xpos;
	GLfloat top = player.Ypos - (enemy.Ypos + enemy.Height);
	GLfloat bottom = (player.Ypos + player.Width) - enemy.Ypos;
	GLfloat mtdX;//minmun translation distance
	GLfloat mtdY;

	//Player.jump = false;
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
		mtdY = bottom;
		//Player.remove = true;

	}
	//assign  the largest mtd to 0 so player is moved the mtd on collision
	if (abs(mtdX) < abs(mtdY))
	{
		
		mtdY = 0;
	}
	else{
		
		mtdX = 0;
	}
	if (mtdY != 0)
	{
		cout << "BANTERMAN" << endl;
		Player.yVelocity = -Player.yVelocity;//* jumping on enemy head bounce
		
		return false;
	}
	else{
		return true;//player dies to enemy restart level
	}
	

}