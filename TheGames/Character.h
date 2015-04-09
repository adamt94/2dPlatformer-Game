
#include <Windows.h>


#include "GameObject.h"

const GLfloat  maxSpeed = 400.0f;
const GLfloat maxJump = 800.0f;
class Character : public GameObject{
public:
	GLboolean jump;
	GLboolean upintheair = false;
	GLboolean DoubleJumpReady = false;
	GLboolean playerleft = false; //check if player walking left
	GLboolean Doublejump = false;
	GLuint myTexture = 0;
	GLuint leftpos = 0;
	GLuint jetpackTexture = 0;
	GLuint jetpackTexutureleft = 0;
	
	//constructer
	Character();
	Character(GLboolean IsSolid, GLboolean Destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos);
	
	void draw();
	void Remove();
	void Left();
	void Right();
	void Up();
	void Down();
	

};