#include "stdafx.h"
#include "GameLevel.h"
#include "Game.h"
#include "Character.h"
#include "BasicEnemy.h"
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

void GameLevel::Load(const char *file, GLuint levelWidth, GLuint levelHeight)
{
	
    // Clear old data
	
    this->Bricks.clear();
	GLuint tileCode;
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<GLuint>> tileData;
    if (fstream)
    {
		
        while (std::getline(fstream, line)) // Read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<GLuint> row;
            while (sstream >> tileCode) // Read each word seperated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
			this->init(tileData, levelWidth, levelHeight);
    }

	

}
void GameLevel::Draw(){
	for (GameObject &tile : this->Bricks){
		if (tile.ID==1)
			glBindTexture(GL_TEXTURE_2D, myTexture);
		else if (tile.ID == 2)
		{
			glBindTexture(GL_TEXTURE_2D, goaltexture);
		}
		else if (tile.ID == 5)
		{
			glBindTexture(GL_TEXTURE_2D, collectabletexture);
		}
		else if (tile.ID == 6)
		{
			glBindTexture(GL_TEXTURE_2D, plainTileTexture);
		}
		if (!tile.Destroyed)
		{
			glEnable(GL_BLEND);// enable transparency
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPushMatrix();
			glColor4f(1.0, 0.0, 0.0, 0.0); //set square to transparent
			glBegin(GL_QUADS);
			glVertex3f(tile.Xpos,tile.Ypos,0.0);
			glVertex3f(tile.Xpos+tile.Width,tile.Ypos,0.0);
			glVertex3f(tile.Xpos+tile.Width,tile.Ypos+tile.Height,0.0);
			glVertex3f(tile.Xpos,tile.Ypos+tile.Height,0.0);
			glEnd();
			glPopMatrix();
			//put texture ontop of square
			glEnable(GL_TEXTURE_2D);
			glColor3f(1, 1, 1);//this becomes transparent
			glBegin(GL_QUADS);
			glTexCoord2f(0.0, 0.0);	glVertex2f(tile.Xpos, tile.Ypos);
			glTexCoord2f(1.0, 0.0); glVertex2f(tile.Xpos + tile.Width, tile.Ypos);
			glTexCoord2f(1.0, 1.0); glVertex2f(tile.Xpos + tile.Width, tile.Ypos + tile.Height);
			glTexCoord2f(0.0, 1.0); glVertex2f(tile.Xpos, tile.Ypos + tile.Height);
			glEnd();
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_BLEND);
				
		
		}
	}
		


	
}
void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight){
	GLuint height = tileData.size();
	cout<<"height"<<height<<endl;
			
	GLuint width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
	GLfloat unit_width = 32;
	GLfloat unit_height = 32;
	// Initialize level tiles based on tileData		
	for (GLuint y = 0; y < height; ++y)
	{
		for (GLuint x = 0; x < width; ++x)
		{
			// Check block type from level data (2D level array)
			if (tileData[y][x] == 1) // Solid
			{
				GameObject tile(true, false, unit_height, unit_width, unit_width*x, unit_height*y);
				tile.ID = 1;//ID for a standard tile
				this->Bricks.push_back(tile);
				
				
			}
			else if (tileData[y][x] == 2)	//Goal platform
			{
			
				GameObject tile(false, false, unit_height, unit_width, unit_width*x, unit_height*y);
				tile.ID = 2;
				this->Bricks.push_back(tile);
			
			}
		
			else if (tileData[y][x] == 3)	//player
			{
			
				//Character players(true, false, unit_height, unit_width, unit_width*x, unit_height*y);
				Playerxpos = unit_width*x;
				Playerypos = unit_height*y;
			
			}
			else if (tileData[y][x] == 4)	//BasicEnemy
			{
				GameObject enemy(false, false, unit_height, unit_width, unit_width*x, unit_height*y);
				this->enemiespos.push_back(enemy);

			}
			else if (tileData[y][x] == 5)//collectable
			{
				GameObject collectable(false, false, unit_height, unit_width, unit_width*x, unit_height*y);
				collectable.ID = 5;
				this->Bricks.push_back(collectable);
			}
			else if (tileData[y][x] == 6)//plain tile
			{
				GameObject tile(true, false, unit_height, unit_width, unit_width*x, unit_height*y);
				tile.ID = 6;//ID for a standard tile
			
				this->Bricks.push_back(tile);
			}
			else if (tileData[y][x] == 7)//moving tile in x direction
			{
				GameObject tile(true, false, unit_height, unit_width, unit_width*x, unit_height*y);
				tile.ID = 7;
				tile.movelength = (unit_width*x);
				this->Bricks.push_back(tile);
			}
			else if (tileData[y][x] == 8)//moving tile in y direction
			{
				GameObject tile(true, false, unit_height, unit_width, unit_width*x, unit_height*y);
				tile.ID = 8;
				tile.movelength = (unit_height*y);
				this->Bricks.push_back(tile);
			}
		}
	}
}
GLboolean GameLevel::IsCompleted(){
	for (GameObject &tile : this->Bricks)
	if (!tile.IsSolid && !tile.Destroyed)
		return GL_FALSE;
	return GL_TRUE;
}

