#pragma once
#include "Program.h"

class ExampleProgram final : public Program
{
public:
	static void CreateInstance();

private:
	ExampleProgram();
	~ExampleProgram() override;
	void func();
	void AtProgramStart() override;
	void AddToProgramLoopBegin() override;
	void OnProgramEnd() override;
};

