#include "stdafx.h"
#include "GameLevel.h"
#include <fstream>
#include <sstream>

#include <math.h>


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
	for (GameObject &tile : this->Bricks)
	if (!tile.Destroyed)
	{
		cout << "YOU WOT M( DRAW MTE" << endl;
		glColor3f(0.0f,1.0f,0.0f);
		glBegin(GL_QUADS);
		glVertex3f(-10.5f, -10.5f, 0.0); // The bottom left corner  
		glVertex3f(-10.5f, 10.5f, 0.0); // The top left corner  
		glVertex3f(10.5f, 10.5f, 0.0); // The top right corner  
		glVertex3f(10.5f, -10.5f, 0.0); // Start drawing a quad primitive  
		glEnd();
		
	}
		


	
}
void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight){
	GLuint height = tileData.size();
	GLuint width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
	GLfloat unit_width = levelWidth / static_cast<GLfloat>(width);
	GLfloat unit_height = levelHeight / height;
	// Initialize level tiles based on tileData		
	for (GLuint y = 0; y < height; ++y)
	{
		for (GLuint x = 0; x < width; ++x)
		{
			// Check block type from level data (2D level array)
			if (tileData[y][x] == 1) // Solid
			{
				GameObject tile(true, false, unit_height*x, unit_width*y, x, y);

				this->Bricks.push_back(tile);
				Draw();
				
			}
			else if (tileData[y][x] > 1)	// Non-solid; now determine its color based on level data
			{
			

			
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

