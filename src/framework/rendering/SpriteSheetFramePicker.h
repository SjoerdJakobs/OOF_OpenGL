#pragma once
class Rectangle;

class SpriteSheetFramePicker
{
public:

	void PickFrame(const float widthSprites, const  float heightSprites, const  int frameToPick, Rectangle* rectangle);
};

