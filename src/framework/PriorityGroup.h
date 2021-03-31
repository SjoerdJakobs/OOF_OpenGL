#pragma once
#include "Program.h"


class StandardObject;

class PriorityGroup
{
public:
	PriorityGroup(int priority):PriorityNr(priority){}
	int PriorityNr;
	std::vector<StandardObject*> standardObjects;	
};
