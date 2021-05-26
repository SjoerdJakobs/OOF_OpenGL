#pragma once
class Rectangle;

class SpriteSheetFramePicker final
{
public:

	void PickFrameHorizontal(const float widthSprites, const  float heightSprites, const  int frameToPick, Rectangle* rectangle);
	void PickFrameVertical(const float widthSprites, const  float heightSprites, const  int frameToPick, Rectangle* rectangle);
};
