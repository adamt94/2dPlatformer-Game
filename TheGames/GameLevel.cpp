#include "stdafx.h"
#include "GameLevel.h"
#include <fstream>
#include <sstream>


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
void GameLevel::Draw(){}
void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight){}
GLboolean GameLevel::IsCompleted(){return false;}

