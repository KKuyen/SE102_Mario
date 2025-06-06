#include "BreakableBrick.h"
#include "Mario.h"
#include "Game.h"
#include "debug.h"
#include "Koopas.h"
#include "PlayScene.h"
#include "BreakableBrickPart.h"
#include "WIngedKoopas.h"
#include "Coin.h"
void CBreakableBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (state == BREAKABLE_BRICK_STATE_NORMAL ||state == BREAKABLE_BRICK_STATE_MOVE) {
		LPANIMATION ani = animations->Get(ID_ANI_BREAKABLE_BRICK);
		if (ani) {
			ani->Render(x, y);
		}
		else {
			DebugOut(L"[ERROR] Breakable brick animation ID %d not found\n", ID_ANI_BREAKABLE_BRICK);
		}
	}
	else if (state == BREAKABLE_BRICK_STATE_COIN) {
		LPANIMATION ani = animations->Get(ID_ANI_COIN);
		if (ani) {
			ani->Render(x, y);
		}
		else {
			DebugOut(L"[ERROR] Coin animation ID %d not found\n", ID_ANI_COIN);
		}
	}
	// RenderBoundingBox();
}

void CBreakableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BREAKABLE_BRICK_BBOX_WIDTH / 2;
	t = y - BREAKABLE_BRICK_BBOX_HEIGHT / 2;
	r = l + BREAKABLE_BRICK_BBOX_WIDTH;
	b = t + BREAKABLE_BRICK_BBOX_HEIGHT;
}
void CBreakableBrick :: Upp(float& t)
{
	
}

void CBreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BREAKABLE_BRICK_STATE_MOVE)
	{
		vy += BREAKABLE_BRICK_GRAVITY * dt; // Apply gravity
		y += vy * dt; // Update position

		// Check if brick has returned to initial position
		if (vy > 0 && y >= inity) // Only transition when falling back down
		{
			vy = 0;
			y = inity;
			SetState(BREAKABLE_BRICK_STATE_NORMAL);
		}
	}
	else
	{
		vx = vy = 0;
	}

	// Check if in coin state and timeout has elapsed
	if (state == BREAKABLE_BRICK_STATE_COIN && GetTickCount64() - coin_state_start > COIN_STATE_TIMEOUT&& coin_state_start!=0)
	{
		SetState(BREAKABLE_BRICK_STATE_NORMAL);
	}
	

	
}

void CBreakableBrick::SetState(int state)
{
	CGameObject::SetState(state);
	this->state = state;
	switch (state)
	{
	case BREAKABLE_BRICK_STATE_MOVE:
	{

		vy = BREAKABLE_BRICK_MOVE_SPEED_Y;
		break;

	}
	case BREAKABLE_BRICK_STATE_NORMAL:
	{
		coin_state_start = 0; // Reset timer when returning to normal state
		break;
	}
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
	case BREAKABLE_BRICK_STATE_COIN:
	{
		

		coin_state_start = GetTickCount64();
		
		break;

	}
	


	}
}

void CBreakableBrick::OnCollisionWith(LPCOLLISIONEVENT e)
{

	vx = vy = 0;

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