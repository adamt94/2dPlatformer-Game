#include <GLFW/glfw3.h>

class Character{
public:
	GLfloat Height, Width, Xpos, Ypos,xVelocity,yVelocity;

	//constructer
	Character(GLfloat height, GLfloat width, GLfloat  xpos, GLfloat  ypos, GLfloat xVelocity, GLfloat yVelocity);
	
	void draw();
	void remove();
	void Left();
	void Right();
	void Up();
	void Down();

};