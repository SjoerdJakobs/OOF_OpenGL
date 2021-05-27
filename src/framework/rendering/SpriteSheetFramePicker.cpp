#include "SpriteSheetFramePicker.h"

#include "Rectangle.h"

void SpriteSheetFramePicker::PickFrameHorizontalDownUp(const float widthSprites, const  float heightSprites, const  int frameToPick, Rectangle* rectangle)
{
	float xStep = (1 / widthSprites);
	float yStep = (1 / heightSprites);
	int column = frameToPick % (int)widthSprites;
	int row = static_cast<int>(frameToPick / widthSprites);

	float xStart = static_cast<float>(column) * xStep;
	float yStart = static_cast<float>(row) * yStep;
	rectangle->DrawWithSpritesheetTextureAnimation(xStart, xStart + xStep, yStart, yStart + yStep);
}

void SpriteSheetFramePicker::PickFrameVertical(const float widthSprites, const float heightSprites,	const int frameToPick, Rectangle* rectangle)
{
	float xStep = (1 / widthSprites);
	float yStep = (1 / heightSprites);
	int row = frameToPick % (int)heightSprites;
	int column = static_cast<int>(frameToPick / heightSprites);

	float xStart = static_cast<float>(column) * xStep;
	float yStart = static_cast<float>(row) * yStep;
	rectangle->DrawWithSpritesheetTextureAnimation(xStart, xStart + xStep, yStart, yStart + yStep);
}
//
//void SpriteSheetFramePicker::PickFrameHorizontalUpDown(const float widthSprites, const float heightSprites,
//	const int maxFrames, const int frameToPick, Rectangle* rectangle)
//{
//	float xStep = (1 / widthSprites);
//	float yStep = (1 / heightSprites);
//	int column = frameToPick % (int)widthSprites;
//	int row = maxFrames - static_cast<int>(frameToPick / widthSprites);
//
//	float xStart = static_cast<float>(column) * xStep;
//	float yStart = static_cast<float>(row) * yStep;
//	rectangle->DrawWithSpritesheetTextureAnimation(xStart, xStart + xStep, yStart, yStart + yStep);
//}
