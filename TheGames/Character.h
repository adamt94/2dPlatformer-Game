#include <GLFW/glfw3.h>
#include "GameObject.h"
const GLfloat  maxSpeed = 400.0f;
class Character : public GameObject{
public:
	GLfloat xVelocity,yVelocity;
	

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