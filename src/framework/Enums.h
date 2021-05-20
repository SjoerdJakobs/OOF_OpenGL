#pragma once

enum class SceneNames
{
	MainMenu = 0,
	Tutorial = 1,
	Scene1 = 2
};


enum class LoopType
{
	input = 0,
	update = 1,
	fixedUpdate = 2,
	render = 3,
	imGuiRender = 4,
	debugRender = 5
};