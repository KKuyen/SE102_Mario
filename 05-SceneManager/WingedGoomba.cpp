#include "WingedGoomba.h"
#include "Koopas.h"
#include "Goomba.h"
#include "WIngedKoopas.h"

CWingedGoomba::CWingedGoomba(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = WINGED_GOOMBA_GRAVITY;
	die_start = -1;
	jump_start = GetTickCount64();
	prepareRotate = false;
	SetState(WINGED_GOOMBA_STATE_FLYING);
}

void CWingedGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == WINGED_GOOMBA_STATE_DIE)
	{
		left = x - WINGED_GOOMBA_BBOX_WIDTH / 2;
		top = y - WINGED_GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + WINGED_GOOMBA_BBOX_WIDTH;
		bottom = top + WINGED_GOOMBA_BBOX_HEIGHT_DIE;
	}
	else
	{
		left = x - WINGED_GOOMBA_BBOX_WIDTH / 2;
		top = y - WINGED_GOOMBA_BBOX_HEIGHT / 2;
		right = left + WINGED_GOOMBA_BBOX_WIDTH;
		bottom = top + WINGED_GOOMBA_BBOX_HEIGHT;
	}
}

void CWingedGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CWingedGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == WINGED_GOOMBA_STATE_WALKING && dynamic_cast<CGoomba*>(e->obj))\
	{
		vx = -vx;
			CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
			goomba->SetVx(-goomba->GetVx());
	}
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CWingedGoomba*>(e->obj)) return;
	if (dynamic_cast<CKoopas*>(e->obj))
	{
		CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
		if (koopas->GetState() == KOOPAS_STATE_SHELL_MOVING || koopas->GetState() == KOOPAS_STATE_HELD)
			SetState(WINGED_GOOMBA_STATE_FALL);

	}
	else if (dynamic_cast<CWingedKoopas*>(e->obj))
	{
		CWingedKoopas* koopas = dynamic_cast<CWingedKoopas*>(e->obj);
		if (koopas->GetState() == WINGED_KOOPAS_STATE_SHELL_MOVING || koopas->GetState() == WINGED_KOOPAS_STATE_HELD)
			SetState(WINGED_GOOMBA_STATE_FALL);

	}
	else
	{

		if (e->ny != 0)
		{
			vy = 0;
			if (e->ny < 0 && isJumping)
			{
				isJumping = false; 
				jump_start = GetTickCount64(); 
				
			}
		}
		else if (e->nx != 0 && !isJumping)
		{
			vx = -vx;
		}
	}
}

void CWingedGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	
	if ((state == WINGED_GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > WINGED_GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	// Kiểm tra thời gian để nhảy trong trạng thái fly
	if (state == WINGED_GOOMBA_STATE_FLYING && !isJumping && GetTickCount64() - jump_start > WINGED_GOOMBA_JUMP_INTERVAL)
	{
		isJumping = true;
		vy = -WINGED_GOOMBA_JUMP_SPEED_Y; // Nhảy lên
		// Find Mario in the list of game objects
		CMario* mario = nullptr;
		for (LPGAMEOBJECT obj : *coObjects)
		{
			if (dynamic_cast<CMario*>(obj))
			{
				mario = dynamic_cast<CMario*>(obj);
				break;
			}
		}

		// If Mario is found, adjust the Winged Goomba's movement to follow him
		if (mario)
		{
			float marioX, marioY;
			mario->GetPosition(marioX, marioY);

			// Adjust horizontal velocity to move towards Mario
			if (x < marioX)
				vx = WINGED_GOOMBA_WALKING_SPEED; // Move right
			else if (x > marioX)
				vx = -WINGED_GOOMBA_WALKING_SPEED; // Move left

			// Adjust vertical velocity to simulate jumping towards Mario
			if (state == WINGED_GOOMBA_STATE_FLYING && !isJumping && GetTickCount64() - jump_start > WINGED_GOOMBA_JUMP_INTERVAL)
			{
				isJumping = true;
				vy = -WINGED_GOOMBA_JUMP_SPEED_Y; // Jump up
			}
		}
		
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CWingedGoomba::Render()
{
	int aniId = ID_ANI_WINGED_GOOMBA_WALKING;
	if (state == WINGED_GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_WINGED_GOOMBA_DIE;
	}
	else if (state == WINGED_GOOMBA_STATE_FALL)
	{
		aniId = ID_ANI_WINGED_GOOMBA_FALL;
	
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
//render canhs phai
	if (state == WINGED_GOOMBA_STATE_FLYING)
	{
		aniId = ID_ANI_WINGED_GOOMBA_FLYING;
		CAnimations::GetInstance()->Get(aniId)->Render(x+WINGED_GOOMBA_BBOX_WIDTH/2, y-WINGED_GOOMBA_BBOX_HEIGHT/2);
	}
	
	//render canh trai
	if (state == WINGED_GOOMBA_STATE_FLYING)
	{
		aniId = ID_ANI_WINGED_GOOMBA_FLYING_LEFT;
		CAnimations::GetInstance()->Get(aniId)->Render(x -WINGED_GOOMBA_BBOX_WIDTH / 2, y - WINGED_GOOMBA_BBOX_HEIGHT / 2);
	}
	RenderBoundingBox();

}

void CWingedGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case WINGED_GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		y += (WINGED_GOOMBA_BBOX_HEIGHT - WINGED_GOOMBA_BBOX_HEIGHT_DIE)/2;
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case WINGED_GOOMBA_STATE_WALKING:
		vx = -WINGED_GOOMBA_WALKING_SPEED;
		break;
	case WINGED_GOOMBA_STATE_FLYING:
		vx = -WINGED_GOOMBA_WALKING_SPEED;
		ay = WINGED_GOOMBA_GRAVITY;
		isJumping = false;
		jump_start = GetTickCount64();
		break;
	case WINGED_GOOMBA_STATE_FALL:
		die_start = GetTickCount64();
		vx = WINGED_GOOMBA_FALL_SPEED_HORIZONTAL;
		vy = WINGED_GOOMBA_FALL_SPEED; // Nảy lên
		ay = WINGED_GOOMBA_GRAVITY; // Trọng lực sẽ kéo xuống
		break;

	
	}

}
