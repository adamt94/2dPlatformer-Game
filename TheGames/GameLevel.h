#include <vector>
#include "GameObject.h"

class GameLevel : public GameObject
{
public:
	GLuint myTexture,goaltexture, collectabletexture,plainTileTexture, levelcounts;
	GLfloat Playerxpos, Playerypos; // the players starting position on the level
    // Level state
    std::vector<GameObject> Bricks;//platforms
	std::vector<GameObject> enemiespos; //contain all the positions of the enemys from the txt file
    // Constructor
	GameObject player;//object for player starting position on level
    GameLevel() { }
    // Loads level from file
    void      Load(const char *file, GLuint levelWidth, GLuint levelHeight);
    // Render level
    void      Draw();
    // Check if the level is completed (all non-solid tiles are destroyed)
    GLboolean IsCompleted();
private:
    // Initialize level from tile data
    void      init(std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};