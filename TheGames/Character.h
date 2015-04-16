
#include <Windows.h>


#include "GameObject.h"

const GLfloat  maxSpeed = 400.0f;
const GLfloat maxJump = 800.0f;
class Character : public GameObject{
public:
	GLboolean jump;
	GLboolean upintheair;
	GLboolean DoubleJumpReady ;
	GLboolean playerleft ; //check if player walking left
	GLboolean Doublejump ;
	GLuint myTexture ;
	GLuint leftpos ;
	GLuint jetpackTexture ;
	GLuint jetpackTexutureleft ;
	GLuint Score;
	
	//constructer
	Character();
	
	Character(GLboolean IsSolid, GLboolean Destroyed, GLint height, GLint width, GLfloat xpos, GLfloat ypos);
	
	void draw();
	void Remove();
	void Left();
	void Right();
	void Up(GLfloat dt);
	void Down();
	

};