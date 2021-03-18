#pragma once
#include <memory>
#include <vector>
#include "StandardObject.h"

struct PriorityGroup
{	
	int PriorityNr{};
	std::vector<StandardObject> standardObjects {};	
};
