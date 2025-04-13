#include "Mushroom.h"
#include "Mario.h"
 
void CMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

		left = x - MUSHROOM_BBOX_WIDTH / 2;
		top = y - MUSHROOM_BBOX_HEIGHT / 2;
		right = left + MUSHROOM_BBOX_WIDTH;
		bottom = top + MUSHROOM_BBOX_HEIGHT-1;
	
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};
 

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (state == MUSHROOM_STATE_EATEN)
	{
		isDeleted = true;
		return;
	}
	if (state == MUSHROOM_STATE_POP_UP)
	{
		if (this->initY-y>= MUSHROOM_BBOX_HEIGHT-1)
		{
			SetState(MUSHROOM_STATE_WALKING);
			vy = 0;

		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_POP_UP:
		vy = -MUSHROOM_POP_UP_SPEED;
		break;
	case MUSHROOM_STATE_WALKING:
		vx = -MUSHROOM_WALKING_SPEED;
		ay = MUSHROOM_GRAVITY;
		break;
	case MUSHROOM_STATE_EATEN:
		break;
	}
}
void CMushroom::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_MUSHROOM_SPRITE)->Draw(x, y);
	//RenderBoundingBox();

}
