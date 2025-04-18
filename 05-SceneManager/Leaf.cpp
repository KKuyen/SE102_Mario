#include "Leaf.h"

void CLeaf::Render()
{
	CSprites* s = CSprites::GetInstance();
	if (direction == 1)
		s->Get(ID_RIGHT_LEAF)->Draw(x, y);
	else
		s->Get(ID_LEFT_LEAF)->Draw(x, y);
	//RenderBoundingBox();
}

void CLeaf::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LEAF_BBOX_WIDTH / 2;
	t = y - LEAF_BBOX_HEIGHT / 2;
	r = l + LEAF_BBOX_WIDTH;
	b = t + LEAF_BBOX_HEIGHT;
}

void CLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == LEAF_STATE_SOAR) {
		if (y > PLATFORM_Y - LEAF_SOAR_HEIGHT) {
			y -= LEAF_SOAR_SPEED * dt;
		}
		else {
			direction = 1;
			SetState(LEAF_STATE_FALL);
		}
	}
	if(state == LEAF_STATE_FALL) {
		y += LEAF_GRAVITY_Y * dt;
		x += LEAF_GRAVITY_X * direction * dt;
		if (x + LEAF_BBOX_WIDTH > initX + AMPLITUDE) {
			direction = -1;
		}
		if (x < initX) {
			direction = 1;
		}
		if (y > PLATFORM_Y + 16) {
			this->Delete();
		}
	}
  	
	CGameObject::Update(dt, coObjects);
}