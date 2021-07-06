//#include "AllocationMetricsTracker.h"
#include "Game.h"
#include "AllocationMetrics.h"

int main(int argc, char* argv[])
{
	//check for memory leaks
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	PrintMemoryUsage("at begin main");
	srand(static_cast<unsigned int>(time(nullptr)));

	Game::CreateInstance();
	PrintMemoryUsage("after create game instance");
	Game* p_GameProgram = dynamic_cast<Game*>(Game::GetInstance());
	PrintMemoryUsage("after get game instance");
	p_GameProgram->ProgramStart();
	PrintMemoryUsage("after program start(which has the program loop)");
	Game::DeleteInstance();
	PrintMemoryUsage("after delete game instance");
	//exit(EXIT_SUCCESS);
	return 0;
}