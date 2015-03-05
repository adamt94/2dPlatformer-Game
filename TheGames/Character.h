#include <GLFW/glfw3.h>
#include "GameObject.h"

const GLfloat  maxSpeed = 400.0f;
const GLfloat maxJump = 700.0f;
class Character : public GameObject{
public:
	GLfloat xVelocity,yVelocity;
	GLboolean jump;

	//constructer
	Character();
	Character(GLboolean IsSolid, GLboolean Destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos);
	
	void draw();
	void remove();
	void Left();
	void Right();
	void Up();
	void Down();

};