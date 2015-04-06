#include "GameObject.h"
#include "Character.h"

class Tile : public GameObject
{
public:
	Tile(GLuint idnumber);
	void CollisionResolution(Tile tile, Character player);
};