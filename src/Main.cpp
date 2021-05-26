#include "Game.h"

//dont even ask i have probably forgotten how this works by the moment you ask me, but here is a video about it:
//https://www.youtube.com/watch?v=p8u_k2LIZyo

inline float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;
	//this number has changed compared to th original code cus wikipedia said it was better and i decided to just take their word for it >_>
	//https://en.wikipedia.org/wiki/Fast_inverse_square_root#:~:text=The%20inverse%20square%20root%20of%20a%20floating%20point%20number%20is,every%20second%20to%20simulate%20lighting.
	i = 0x5F375A86 - (i >> 1);
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));

	return y;
}

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
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(static_cast<unsigned int>(time(nullptr)));
	
	Game::CreateInstance();
	Game* p_GameProgram = dynamic_cast<Game*>(Game::GetInstance());
	p_GameProgram->ProgramStart();
	Game::DeleteInstance();
	exit(EXIT_SUCCESS);
	//return 0;
}