#pragma once

class StandardObject;

class PriorityGroup
{
public:
	PriorityGroup(int priority):PriorityNr(priority){}
	int PriorityNr;
	std::vector<StandardObject*> standardObjects;
	bool operator<(const PriorityGroup& group) const
	{
		return (group.PriorityNr < this->PriorityNr);
	}
};
