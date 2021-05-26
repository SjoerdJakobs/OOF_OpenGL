#pragma once
#include "Program.h"

class Rectangle;

class Game final : public Program
{
public:
	static void CreateInstance();
	static void DeleteInstance();

	~Game() override;
private:
	Game();
	void AtProgramStart() override;
	void AddToProgramLoopBegin() override;
	void OnProgramEnd() override;
};
