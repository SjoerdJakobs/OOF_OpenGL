#pragma once

class StandardObject
{
protected:
	StandardObject(bool startsActivated);
	~StandardObject();

	bool m_shouldDestruct;
	bool m_isActive;//says if the object should be active or not

private:
	bool m_activated;//is the actual active/inactive state of the object

};