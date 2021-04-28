#pragma once
#include "Program.h"

class ExampleProgram final : public Program
{
public:
	static void CreateInstance();
	void ProgramStart() override;

private:
	ExampleProgram();
	~ExampleProgram() override;
	void func();
	void AtProgramStart() override;
	void AddToProgramLoopBegin() override;
protected:
};

