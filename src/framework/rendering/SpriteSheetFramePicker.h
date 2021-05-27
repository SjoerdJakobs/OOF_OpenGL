#pragma once
class Rectangle;

class SpriteSheetFramePicker final
{
public:

	void PickFrameHorizontalDownUp(const float widthSprites, const  float heightSprites, const  int frameToPick, Rectangle* rectangle);
	void PickFrameVertical(const float widthSprites, const  float heightSprites, const  int frameToPick, Rectangle* rectangle);
};
