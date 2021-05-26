#pragma once

class StandardObject;

class PriorityGroup final
{
public:
	PriorityGroup(unsigned int priority) :PriorityNr(priority) {}
	~PriorityGroup()
	{
		m_StandardObjects.clear();
	}
	
	unsigned int PriorityNr;
	std::vector<StandardObject*> m_StandardObjects;
	bool operator<(const PriorityGroup& group) const
	{
		return (group.PriorityNr < this->PriorityNr);
	}
};
