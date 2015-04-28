#ifndef GAME_H
#define GAME_H
#include <vector>
#include <glew.h>

#include "GameObject.h"
#include <GLFW\glfw3.h>

//represent the game state
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};
class Game
{
	
public:

	GameState	State;
	GLboolean	Keys[1024];
	GLboolean   KeysProcessed[1024];
	GLuint		Width, Height;
	GLuint Background, Background2,Background3 ;
	GLint		levelcounter;//counter of each level
	GLuint play, playselected, help, helpselected, exits, exitselected, back, helpagetex;//textures for menu
	GLboolean helppage;
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	//~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	void DoCollision();
	//Reset
	void ResetLevel();
	void ResetPlayer();
	void drawBackground();
	void NextLevel();
	std::vector<GLfloat> CalculateMinTrasnlation(GameObject tile,GameObject Player, GLboolean isPlayer);//boolean checks if its player to enable jumping
	GLboolean PlayerEnemyCollision(GameObject player, GameObject enemy);//collision resolution for player and enemy
	void GameLevelAlgorithm(GLint width, GLint height);
	void drawMenu();
	void helpPage();
	
};
#endif