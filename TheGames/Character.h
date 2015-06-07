
<<<<<<< HEAD
#include <Windows.h>
=======
>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76


#include "GameObject.h"

<<<<<<< HEAD
const GLfloat  maxSpeed = 100.0f;
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
	
=======

const GLfloat  maxSpeed = 400.0f;
const GLfloat maxJump = 700.0f;
class Character : public GameObject{
public:
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
>>>>>>> 0128f88f96302477a0a4f292e14878866b2a1b76

};