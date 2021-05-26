#include "Game.h"

int ScreenWidth = 1280;
int ScreenHeight = 800;

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

static void glfw_window_size_callback(GLFWwindow* m_pWindow, int width, int height) {
	ScreenWidth = width;
	ScreenHeight = height;

	/* update any perspective matrices used here */
}

int main(int argc, char* argv[])
{
	//check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(static_cast<unsigned int>(time(nullptr)));
	
	Game::CreateInstance();
	Game* p_GameProgram = dynamic_cast<Game*>(Game::GetInstance());
	p_GameProgram->ProgramStart();
	Game::DeleteInstance();
	exit(EXIT_SUCCESS);
	//return 0;
}