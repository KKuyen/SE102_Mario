#include "BreakableBrick.h"
#include "Mario.h"
#include "Game.h"
#include "debug.h"
#include "Koopas.h"
#include "PlayScene.h"
#include "BreakableBrickPart.h"
#include "WIngedKoopas.h"
void CBreakableBrick::Render()
{
	if (state == BREAKABLE_BRICK_STATE_NORMAL)
	{
		CAnimations* animations = CAnimations::GetInstance();
		animations->Get(ID_ANI_BREAKABLE_BRICK)->Render(x, y);
	}

	RenderBoundingBox();
}

void CBreakableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BREAKABLE_BRICK_BBOX_WIDTH / 2;
	t = y - BREAKABLE_BRICK_BBOX_HEIGHT / 2;
	r = l + BREAKABLE_BRICK_BBOX_WIDTH;
	b = t + BREAKABLE_BRICK_BBOX_HEIGHT;
}

void CBreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBreakableBrick::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BREAKABLE_BRICK_STATE_BREAK:
	{
		CPlayScene* scene = (CPlayScene*)CGame::GetInstance()->GetCurrentScene();
		scene->PushBackGameObject(new CBreakableBrickPart(x, y, -BRICK_PART_SPEED_X, -BRICK_PART_SPEED_Y));
		scene->PushBackGameObject(new CBreakableBrickPart(x, y, BRICK_PART_SPEED_X, -BRICK_PART_SPEED_Y));
		scene->PushBackGameObject(new CBreakableBrickPart(x, y, -BRICK_PART_SPEED_X * 0.5f, -BRICK_PART_SPEED_Y * 1.2f));
		scene->PushBackGameObject(new CBreakableBrickPart(x, y, BRICK_PART_SPEED_X * 0.5f, -BRICK_PART_SPEED_Y * 1.2f));
		isDeleted = true;
		break;
	}
	case BREAKABLE_BRICK_STATE_INVISIBLE:
	{
		isDeleted = true;
		break;


	}

	}
}

void CBreakableBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CKoopas*>(e->obj))
	{
		CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
		if (koopas->GetState() == KOOPAS_STATE_SHELL_MOVING)
		{
			SetState(BREAKABLE_BRICK_STATE_BREAK);
			koopas->SetVx(-koopas->GetVx());
		}



	}
	if (dynamic_cast<CWingedKoopas*>(e->obj))
	{
		CWingedKoopas* koopas = dynamic_cast<CWingedKoopas*>(e->obj);
		if (koopas->GetState() == WINGED_KOOPAS_STATE_SHELL_MOVING)
		{
			SetState(BREAKABLE_BRICK_STATE_BREAK);
			koopas->SetVx(-koopas->GetVx());
		}



	}
}