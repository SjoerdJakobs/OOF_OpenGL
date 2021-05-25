#pragma once

enum class SceneNames
{
	MainMenu = 0,
	HowToPlay = 1,
	Options = 2,
	Scene1 = 3
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