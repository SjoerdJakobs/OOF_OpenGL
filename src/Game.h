#pragma once
#include "Program.h"

class Player;

class Game final : public Program
{
public:
	static void CreateInstance();
	void ProgramStart() override;

private:
	Game();
	~Game() override;
	void AtProgramStart() override;
	void AddToProgramLoopBegin() override;
	Player* m_Player;
};
