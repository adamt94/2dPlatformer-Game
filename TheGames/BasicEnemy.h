#include <vector>

#include "GameObject.h"

const GLfloat  emaxSpeed = 100.0f;
class BasicEnemy : public GameObject {
public:
	std::vector<BasicEnemy> enemies;
	GLuint texture ;
	GLboolean dead;
	BasicEnemy();
	BasicEnemy(GLboolean isSolid, GLboolean destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos);
	void Draw();
	void remove();
	void PlayerCollision(GameObject player,BasicEnemy enemy);
	void Right();
	void Left();
	void addEnemy(GLfloat Xpos, GLfloat Ypos);


};