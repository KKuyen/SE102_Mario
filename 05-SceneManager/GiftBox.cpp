#include "GiftBox.h"

void CGiftBox::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(BOX_SPRITEID)->Draw(x, y);

	//RenderBoundingBox();
}

void CGiftBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BOX_BBOX_WIDTH / 2 + 2;
	t = y - BOX_BBOX_HEIGHT / 2;
	r = l + BOX_BBOX_WIDTH;
	b = t + BOX_BBOX_HEIGHT;
}