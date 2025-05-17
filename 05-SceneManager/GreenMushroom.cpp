#include "GreenMushroom.h"
#include "Mario.h"
#include "Chimney.h"

void CGreenMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

	left = x - GREEN_MUSHROOM_BBOX_WIDTH / 2;
	top = y - GREEN_MUSHROOM_BBOX_HEIGHT / 2;
	right = left + GREEN_MUSHROOM_BBOX_WIDTH;
	bottom = top + GREEN_MUSHROOM_BBOX_HEIGHT - 1;

}

void CGreenMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};


void CGreenMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if (state == GREEN_MUSHROOM_STATE_EATEN)
	{
		isDeleted = true;
		return;
	}
	if (state == GREEN_MUSHROOM_STATE_POP_UP)
	{
		if (this->initY - y >= GREEN_MUSHROOM_BBOX_HEIGHT - 1)
		{
			SetState(GREEN_MUSHROOM_STATE_WALKING);
			vy = 0;

		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CGreenMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GREEN_MUSHROOM_STATE_POP_UP:
		vy = -GREEN_MUSHROOM_POP_UP_SPEED;
		break;
	case GREEN_MUSHROOM_STATE_WALKING:
		float marioX, marioY;
		mario->GetPosition(marioX, marioY);
		if (x < marioX)
			vx = -GREEN_MUSHROOM_WALKING_SPEED;
		else
			vx = GREEN_MUSHROOM_WALKING_SPEED;
		ay = GREEN_MUSHROOM_GRAVITY;
		break;
	case GREEN_MUSHROOM_STATE_EATEN:
		break;
	}
}
void CGreenMushroom::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_GREEN_MUSHROOM_SPRITE)->Draw(x, y);
	//RenderBoundingBox();

}
void CGreenMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CChimney*>(e->obj))
	{
		vx = -vx;

	}
}