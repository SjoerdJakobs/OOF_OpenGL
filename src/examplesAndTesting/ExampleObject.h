#pragma once
#include "StandardObject.h"
class ExampleObject : public StandardObject
{
private:
	float m_Counter{ 0 };
	float m_DeathPoint{ 0 };

	_LONGDOUBLE* m_pBigNr0;
	_LONGDOUBLE* m_pBigNr1;
	_LONGDOUBLE* m_pBigNr2;
	_LONGDOUBLE* m_pBigNr3;
	_LONGDOUBLE* m_pBigNr4;
	_LONGDOUBLE* m_pBigNr5;
	_LONGDOUBLE* m_pBigNr6;
	_LONGDOUBLE* m_pBigNr7;
	_LONGDOUBLE* m_pBigNr8;
	_LONGDOUBLE* m_pBigNr9;
public:
	ExampleObject(int priority);
	~ExampleObject();
	void Start() override;
	void Awake() override;
	void Sleep() override;
	void OnDestroy() override;
	void Input(float deltaTime) override;
	void Update(float deltaTime) override;
	void Render(float deltaTime) override;
	void ImGuiRender(float deltaTime) override;
};

