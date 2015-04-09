#include <vector>

#include "GameObject.h"


class BasicEnemy : public GameObject {
public:
	std::vector<BasicEnemy> Enemies;
	GLuint texture = 0;
	GLboolean dead;
	BasicEnemy();
	BasicEnemy(GLboolean isSolid, GLboolean destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos);
	void Draw();
	void remove();
	void PlayerCollision(GameObject player,BasicEnemy enemy);

};