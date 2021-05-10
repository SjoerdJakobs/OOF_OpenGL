#include "SpriteSheetFramePicker.h"

#include "Rectangle.h"
#include "glm/glm.hpp"

void SpriteSheetFramePicker::PickFrame(const float widthSprites, const  float heightSprites, const  int frameToPick, Rectangle* rectangle)
{
	float xStep = (1 / widthSprites);
	float yStep = (1 / heightSprites);
	int column = frameToPick % (int)widthSprites;
	int row = frameToPick / widthSprites;

	float xStart = static_cast<float>(column) * xStep;
	float yStart = static_cast<float>(row) * yStep;
	rectangle->DrawWithSpritesheetTextureAnimation(xStart, xStart + xStep, yStart, yStart + yStep);
}
