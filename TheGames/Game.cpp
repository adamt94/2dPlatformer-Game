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
#include <iostream>
#include <fstream>
using namespace std;
Character Player = Character(true, true, 26.0f, 26, 140, 40);
GameLevel level = GameLevel();
BasicEnemy Enemy = BasicEnemy();
//BasicEnemy Enemy = BasicEnemy(true,true,32.0f,32.0f,240,40);
int random;
int random2;
int random3;
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
	GameLevelAlgorithm(10, 10);
	random = rand() % 3 + 1;
	random2 = rand() % 3 + 1;
	random3 = rand() % 3 + 1;
	
	cout << "levelcount " << levelcount << endl;
	our_font.init("kenvector_future.ttf", 22);
	if (levelcount == 0)
	{
		cout << "SHOULD LOAD THIS" << endl;
		level.Load("lvltest.txt", 1000, 600);
	}
	else if (levelcount==1){
		cout << "SHOULD LOAD NO" << endl;
		level.Load("lvl2.txt", 1000, 600);
	}
	
	for (GameObject a : level.enemiespos)
	{

		Enemy.addEnemy(a.Xpos,a.Ypos);
	}
	
	//creates random background from 3 textures
	
		Background = level.loadPNG("gamebackground.png");
	
	
		Background2 = level.loadPNG("gamebackground2.png");
	
	
		Background3 = level.loadPNG("gamebackground3.png");
	
	Player.myTexture = Player.loadPNG("characterstandingpos.png");//player
	level.myTexture = level.loadPNG("platform.png");//tile
	level.plainTileTexture = level.loadPNG("metalPanel.png");//plain tile
	level.collectabletexture = level.loadPNG("collectable.png");//collectable
	level.goaltexture = level.loadPNG("door.png");// goal tile
	
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
		//camera follows player stops moving if gets to edges of level
		if (-(Player.Xpos) + 500 < 0)
		{


			glTranslatef(-(Player.Xpos) + 500, 0.0, 0.0);
		}
		if (-(Player.Ypos) + 250 < 0)
		{

			glTranslatef(0.0, -(Player.Ypos) + 250, 0.0);
		}
		if (((Player.Xpos)+500 > 3000))
		{
			glTranslatef((Player.Xpos)  -2500,0.0 , 0.0);
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
	
	 Player = Character(true, true, 26.0f, 26.0f, 70, 40);
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
			if (tile.ID==5)//collectable
				break;
			
			//cout << "enemy" << enem.Xpos << " tile " << tile.Xpos << endl;
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
			if (Player.checkCollision(Player, enem) == true && enem.dead == false)
			{

				if (PlayerEnemyCollision(Player, enem) == false)
				{
					enem.dead = true;
				}

				else {
					Playerdied = true;
				}


				// check if player collide with enemy and resolve it
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






		
		

	}
	if (Playerdied)
		ResetLevel();//if player reacher goal
	else if (goal)
	{

		levelcount++;
		ResetLevel();
	}
}

void Game::drawBackground(){
	//get 3 different random numbers to generate a random texture of the 3 and repeats this 3 times 
	if (random == 1)
	{

		glBindTexture(GL_TEXTURE_2D, Background);
	}
	else if (random == 2){
		glBindTexture(GL_TEXTURE_2D, Background2);
	}
	else{
		glBindTexture(GL_TEXTURE_2D, Background3);
	}//creates random background texture
	
	glPushMatrix();
	glEnable(GL_BLEND);// enable transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 0.0, 0.0, 0.0); //set square to transparent
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0 + 1000,0);
	glVertex2f(0 + 1000, 0 + 1200);
	glVertex2f(0, 0 + 1200);
	glEnd();

	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);//this becomes transparent
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);	glVertex2f(0, 0);
	glTexCoord2f(1.0, 0.0); glVertex2f(0 + 1000, 0);
	glTexCoord2f(1.0, 2.0); glVertex2f(0 + 1000, 0 + 1200);
	glTexCoord2f(0.0, 2.0); glVertex2f(0, 0 + 1200);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
	if (random2 == 1)
	{

		glBindTexture(GL_TEXTURE_2D, Background);
	}
	else if (random2 == 2){
		glBindTexture(GL_TEXTURE_2D, Background2);
	}
	else{
		glBindTexture(GL_TEXTURE_2D, Background3);
	}//creates random background texture
	//2nd texture mapping
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);//this becomes transparent
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);	glVertex2f(1000, 0);
	glTexCoord2f(1.0, 0.0); glVertex2f(1000 + 1000, 0);
	glTexCoord2f(1.0, 2.0); glVertex2f(1000 + 1000, 0 + 1200);
	glTexCoord2f(0.0, 2.0); glVertex2f(1000, 0 + 1200);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();

		if (random3 == 1)
	{

		glBindTexture(GL_TEXTURE_2D, Background);
	}
	else if (random3 == 2){
		glBindTexture(GL_TEXTURE_2D, Background2);
	}
	else{
		glBindTexture(GL_TEXTURE_2D, Background3);
	}//creates random background texture

	//3rd texture mapping
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);//this becomes transparent
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);	glVertex2f(2000, 0);
	glTexCoord2f(1.0, 0.0); glVertex2f(2000 + 1000, 0);
	glTexCoord2f(1.0, 2.0); glVertex2f(2000 + 1000, 0 + 1200);
	glTexCoord2f(0.0, 2.0); glVertex2f(2000, 0 + 1200);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();

	

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
		
		Player.yVelocity = -Player.yVelocity;//* jumping on enemy head bounce
		
		return false;
	}
	else{
		return true;//player dies to enemy restart level
	}
	

}


void Game::GameLevelAlgorithm(GLint width, GLint height){
	ofstream myfile;
	GLuint tileData[30][40] = { 0 };
	int randomnumber = 0;
	myfile.open("lvl2.txt");
	//starting platform
	tileData[0][0] = 1;
	tileData[0][1] = 1;
	tileData[0][2] = 1;
	
	//player spawn
	tileData[4][0] = 3;
	//goal




	for (int i = 0; i < 30; i++)
	{

		for (int j = 0; j < 40; j++)
		{
			
				//1 in 20 chance to spawn a tile
				randomnumber = rand()%20 + 1;
			//cout << randomnumber << endl;
			if (randomnumber == 1)
			{
				tileData[i][j] = 1;

				//give a 50% chance to spawn a tile each side of it
				randomnumber = rand() % 1;
				if (randomnumber == 0)
				{
					//check its not outside of array
					if ((j - 1) >= 0)
					{
						tileData[i][j - 1] = 1;
					}
					randomnumber = rand() % 3;
					if ((j - 2) >= 0)
					{
						tileData[i][j - 2] = 1;
					}
				}
				randomnumber = rand() % 1;
				if (randomnumber == 0)
				{
					//check its not outside of array
					if ((j + 1) < 40)
					{
						tileData[i][j + 1] = 1;
					}
				}
				randomnumber = rand() % 3;
				if (randomnumber == 0)
				{
					//check its not outside of array
					if ((j + 2) < 40)
					{
						tileData[i][j + 2] = 1;
					}
					
				}
			
				

				
				
			}
		
			
		}
		
		
	}
	//adding moving platforms
	for (int i = 0; i < 30; i++)
	{

		for (int j = 0; j < 40; j++)
		{
			
				if ((i + 1) < 30)
				{
					//spawn a plain tile as its under another tile
					if (tileData[i][j] == 1 && tileData[i + 1][j])
					{
						tileData[i][j] = 6;
					}
					//spawn enemies
					
				}
				if (tileData[i][j]==0)
				{
					//spawn enemy above platform if its a 3 length platform
					if ((i - 1 > 0 && (j + 1) < 30 && (j - 1) > 0))//check its not out of bounds
					{
						if (tileData[i - 1][j - 1] == 1 && tileData[i - 1][j] == 1 && tileData[i - 1][j + 1])
						{
							//% chance of spawning
							randomnumber = rand() % 25;
							if (randomnumber == 0)
							{

								tileData[i][j] = 4;
							}
						}
					}
				}
		}
		
	}

	tileData[29][39] = 2;
	for (int i = 0; i < 30; i++)
	{

		for (int j = 0; j < 40; j++)
		{
			myfile << tileData[i][j]<<" ";
		}
		myfile << "\n";
	}

}