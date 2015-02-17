#ifndef GAME_H
#define GAME_H
#include <GLFW/glfw3.h>
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
	
};
#endif