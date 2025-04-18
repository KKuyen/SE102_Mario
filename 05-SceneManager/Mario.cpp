﻿#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"

#include "Collision.h"
#include "Koopas.h"
#include "WIngedGoomba.h"
#include "GiftBox.h"
#include "Mushroom.h"
#include "Bullet.h"
#include "Flower.h"
 
void CMario::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	if (abs(vx) > abs(maxVx)) vx = maxVx;
	if (!isOnPlatform)
	{
		beforeLand = true;
	}
	if (isOnPlatform && beforeLand)
	{
		isFlying = false;
		run_start = 0;
		beforeLand = false;
	}
	if (state == MARIO_STATE_SLIP_RIGHT)
	{
		if (vx <= 0) 
		{
			SetState(MARIO_STATE_IDLE);  
		}
	}
	if (state == MARIO_STATE_SLIP_LEFT)
	{
		if (vx >= 0)
		{
			SetState(MARIO_STATE_IDLE);
		}
	}
	// Kiểm tra thời gian giữ nút chạy để kích hoạt bay
	if (level == MARIO_LEVEL_MAX && run_start != 0)
	{
		if (GetTickCount64() - run_start >= MARIO_FLY_ACTIVATION_TIME)
		{
			isFlying = true;
		
		}
	}
	// reset untouchable timer if untouchable time has passed
	if ( GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME) 
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	// Update held object position
	if (heldObject != NULL)
	{
		float mx, my;
		GetPosition(mx, my);
		CKoopas* koopas = dynamic_cast<CKoopas*>(heldObject);
		if ( GetTickCount64() - hold_start >= KOOPAS_REVIVE_TIME)
		{

			koopas->SetVy(KOOPAS_JUMP_SPEED);
			koopas->ay = KOOPAS_GRAVITY;
			koopas->nx = nx;
			koopas->SetState(KOOPAS_STATE_WALKING);
			SetHolding(false, nullptr);
			hold_start = 0;
			if (level > MARIO_LEVEL_SMALL)
			{

				level = level - 1;
				StartUntouchable();
			}
			else
			{
				DebugOut(L">>> Mario DIE >>> \n");
				SetState(MARIO_STATE_DIE);

			}

		}
		else
		{
			heldObject->SetPosition(mx + (nx > 0 ? MARIO_BIG_BBOX_WIDTH / 2 + KOOPAS_BBOX_WIDTH / 2 : -MARIO_BIG_BBOX_WIDTH / 2 - KOOPAS_BBOX_WIDTH / 2), my);
			// Kiểm tra thời gian cầm Koopas
		}
	
	
		
	}

	isOnPlatform = false; 
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
	isOnPlatform = false;
}
int CMario::GetDirection()
{
	if (vx > 0)
	{
		return 1;
	}
	else
		return 0;

}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) {
			isOnPlatform = true;
			
		}
	}
	else 
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKooPas(e);
 	else if (dynamic_cast<CWingedGoomba*>(e->obj))
		OnCollisionWithWingedGoomba(e);
	else if (dynamic_cast<CGiftBox*>(e->obj))
		OnCollisionWithGiftBox(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CBullet*>(e->obj))
		OnCollisionWithBullet(e);	
	else if (dynamic_cast<CFlower*>(e->obj))
		OnCollisionWithFlower(e);

}
void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	DebugOut(L"[INFO] Mario collided with Mushroom, nx = %f, ny = %f\n", e->nx, e->ny);
	CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
	mushroom->SetState(MUSHROOM_STATE_EATEN);
	if (level == MARIO_LEVEL_SMALL)
		SetLevel(MARIO_LEVEL_BIG);
}
void CMario::OnCollisionWithBullet(LPCOLLISIONEVENT e)
{
	CBullet* bullet = dynamic_cast<CBullet*>(e->obj);
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			StartUntouchable();
			level = level - 1;
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}
void CMario::OnCollisionWithFlower(LPCOLLISIONEVENT e)
{
	CBullet* bullet = dynamic_cast<CBullet*>(e->obj);
	if (untouchable == 0)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			StartUntouchable();
			level = level - 1;
		}
		else
		{
			DebugOut(L">>> Mario DIE >>> \n");
			SetState(MARIO_STATE_DIE);
		}
	}
}
void CMario::OnCollisionWithGiftBox(LPCOLLISIONEVENT e)
{
	CGiftBox* giftbox = dynamic_cast<CGiftBox*>(e->obj);

	if (e->ny > 0) {
		giftbox->Open();
	}
	 
 
}

void CMario::OnCollisionWithKooPas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		


		if (koopas->GetState() != KOOPAS_STATE_SHELL && koopas->GetState() != KOOPAS_STATE_SHELL_MOVING)
		{
			koopas->SetState(KOOPAS_STATE_SHELL);
			
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() == KOOPAS_STATE_SHELL)
		{
			koopas->SetState(KOOPAS_STATE_SHELL_MOVING);
			koopas->SetVy(KOOPAS_JUMP_SPEED/2);
			if(vx>0)
				koopas->nx = 1;
			else
				koopas->nx = -1;
		}
			
		
	}
	else 
	{
		if (untouchable == 0)
		{
			if (koopas->GetState() == KOOPAS_STATE_FALL)
				return;
			if (koopas->GetState() != KOOPAS_STATE_SHELL&& koopas->GetState() != KOOPAS_STATE_HELD)
			{
				if (level > MARIO_LEVEL_SMALL)
				{

					level = level - 1;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);

				}
			}
			else
			{
				
				CGame* game = CGame::GetInstance();
				if (game->IsKeyDown(DIK_A)) // Run key
				{
					hold_start = GetTickCount64();
					SetHolding(true, koopas);
					koopas->SetState(KOOPAS_STATE_HELD); 
				}
				else
				{
					koopas->nx = this->nx;
					koopas->SetState(KOOPAS_STATE_SHELL_MOVING);
				}

			
			}
		}
	}
}


void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	float goomba_vx, goomba_vy;
	goomba->GetSpeed(goomba_vx, goomba_vy);
	bool areFacingEachOther = (nx == 1 && goomba_vx < 0) || (nx == -1 && goomba_vx > 0);

	
	if (e->ny < 0)
	{
	
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if (isHolding && heldObject != NULL ) {

		goomba->SetState(GOOMBA_STATE_FALL);
		
		CKoopas* koopas= dynamic_cast<CKoopas*>(heldObject);
		SetHolding(false, nullptr);
		koopas->nx = nx;
		koopas->SetState(KOOPAS_STATE_FALL);
		if (!areFacingEachOther)
		{
			if (untouchable == 0)
			{
				if (goomba->GetState() != GOOMBA_STATE_DIE || GOOMBA_STATE_FALL)
				{
					if (level > MARIO_LEVEL_SMALL)
					{

						level = level - 1;
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);

					}
				}
			}
		}
		
		
	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != GOOMBA_STATE_DIE|| GOOMBA_STATE_FALL)
			{
				if (level > MARIO_LEVEL_SMALL)
				{
					
					level = level-1;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);
				
				}
			}
		}
	}
}
void CMario::OnCollisionWithWingedGoomba(LPCOLLISIONEVENT e)
{
	CWingedGoomba* goomba = dynamic_cast<CWingedGoomba*>(e->obj);
	float goomba_vx, goomba_vy;
	goomba->GetSpeed(goomba_vx, goomba_vy);
	bool areFacingEachOther = (nx == 1 && goomba_vx < 0) || (nx == -1 && goomba_vx > 0);
	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() == WINGED_GOOMBA_STATE_WALKING)
		{
			
			goomba->SetState(WINGED_GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		if (goomba->GetState() == WINGED_GOOMBA_STATE_FLYING)
		{

			goomba->SetState(WINGED_GOOMBA_STATE_WALKING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else if (isHolding && heldObject != NULL)
	{
		goomba->SetState(WINGED_GOOMBA_STATE_FALL);
		CKoopas* koopas = dynamic_cast<CKoopas*>(heldObject);
		SetHolding(false, nullptr);
		koopas->SetState(KOOPAS_STATE_FALL);
		if (!areFacingEachOther)
		{
			if (untouchable == 0)
			{
				if (goomba->GetState() != GOOMBA_STATE_DIE || GOOMBA_STATE_FALL)
				{
					if (level > MARIO_LEVEL_SMALL)
					{

						level = level - 1;
						StartUntouchable();
					}
					else
					{
						DebugOut(L">>> Mario DIE >>> \n");
						SetState(MARIO_STATE_DIE);

					}
				}
			}
		}

	}
	else // hit by Goomba
	{
		if (untouchable == 0)
		{
			if (goomba->GetState() != WINGED_GOOMBA_STATE_DIE|| WINGED_GOOMBA_STATE_FALL)
			{
				if (level > MARIO_LEVEL_SMALL)
				{

					level = level - 1;
					StartUntouchable();
				}
				else
				{
					DebugOut(L">>> Mario DIE >>> \n");
					SetState(MARIO_STATE_DIE);

				}
			}
		}
	}
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	coin++;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	CPortal* p = (CPortal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}

//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (isHolding)
	{
		if (vx != 0)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_HOLD_LEFT;
		}
		else
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT;
		}
	}
	else
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else

				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (state != MARIO_STATE_SLIP_RIGHT)
					{
						if (ax < 0)
							aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
						else if (ax == MARIO_ACCEL_RUN_X)
							aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
						else if (ax == MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
					}
					else
					{
						aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
					}
				
				}
				else // vx < 0
				{

					if (state != MARIO_STATE_SLIP_LEFT)
					{
						if (ax > 0)
							aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
						else if (ax == -MARIO_ACCEL_RUN_X)
							aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
						else if (ax == -MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
					}
					else
					{
						aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
					}
				}
	}
	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}


//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (isHolding)
	{
		if (vx != 0)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_HOLD_LEFT;
		}
		else
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_HOLD_IDLE_RIGHT;
			else
				aniId = ID_ANI_MARIO_HOLD_IDLE_LEFT;
		}
	}
	else
	{

		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (state != MARIO_STATE_SLIP_RIGHT)
					{
						if (ax < 0)
							aniId = ID_ANI_MARIO_BRACE_RIGHT;
						else if (ax == MARIO_ACCEL_RUN_X)
							aniId = ID_ANI_MARIO_RUNNING_RIGHT;
						else if (ax == MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_WALKING_RIGHT;
					}
					else
					{
						aniId = ID_ANI_MARIO_WALKING_RIGHT;
					}
				
				}
				else // vx < 0
				{

					if (state != MARIO_STATE_SLIP_LEFT)
					{
						if (ax > 0)
							aniId = ID_ANI_MARIO_BRACE_LEFT;
						else if (ax == -MARIO_ACCEL_RUN_X)
							aniId = ID_ANI_MARIO_RUNNING_LEFT;
						else if (ax == -MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_WALKING_LEFT;
					}
					else
					{
						aniId = ID_ANI_MARIO_WALKING_LEFT;
					}
				}

		if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;
	}
	return aniId;
}
int CMario::GetAniIdMax()
{
	int aniId = -1;
	if (isHolding)
	{
		if (vx != 0)
		{

			if (nx > 0)
				aniId = ID_ANI_MARIO_MAX_HOLD_RIGHT;
			else
				aniId = ID_ANI_MARIO_MAX_HOLD_LEFT;
		}
		else
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_MAX_HOLD_IDLE_RIGHT;
			else
				aniId = ID_ANI_MARIO_MAX_HOLD_IDLE_LEFT;
		}
	}
	else if (isFlying ) 
	{
		if (isOnPlatform)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_MAX_FLYING_RUNNING_RIGHT;
			else
				aniId = ID_ANI_MARIO_MAX_FLYING_RUNNING_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_MAX_FLYING_RIGHT;
			else
				aniId = ID_ANI_MARIO_MAX_FLYING_LEFT;
		}


	}
	else
	{
		if (!isOnPlatform)
		{
			if (abs(ax) == MARIO_ACCEL_RUN_X)
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_MAX_JUMP_RUN_RIGHT;
				else
					aniId = ID_ANI_MARIO_MAX_JUMP_RUN_LEFT;
			}
			else
			{
				if (nx >= 0)
					aniId = ID_ANI_MARIO_MAX_JUMP_WALK_RIGHT;
				else
					aniId = ID_ANI_MARIO_MAX_JUMP_WALK_LEFT;
			}
		}
		else
			if (isSitting)
			{
				if (nx > 0)
					aniId = ID_ANI_MARIO_MAX_SIT_RIGHT;
				else
					aniId = ID_ANI_MARIO_MAX_SIT_LEFT;
			}
			else
				if (vx == 0)
				{
					if (nx > 0) aniId = ID_ANI_MARIO_MAX_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_MAX_IDLE_LEFT;
				}
				else if (vx > 0)
				{
					if (state != MARIO_STATE_SLIP_RIGHT)
					{
						if (ax < 0)
							aniId = ID_ANI_MARIO_MAX_BRACE_RIGHT;
						else if (ax == MARIO_ACCEL_RUN_X)
							aniId = ID_ANI_MARIO_MAX_RUNNING_RIGHT;
						else if (ax == MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_MAX_WALKING_RIGHT;
					}
					else
					{
						aniId = ID_ANI_MARIO_MAX_WALKING_RIGHT;
					}
				
				}
				else // vx < 0
				{

					if (state != MARIO_STATE_SLIP_LEFT)
					{
						if (ax > 0)
							aniId = ID_ANI_MARIO_MAX_BRACE_LEFT;
						else if (ax == -MARIO_ACCEL_RUN_X)
							aniId = ID_ANI_MARIO_MAX_RUNNING_LEFT;
						else if (ax == -MARIO_ACCEL_WALK_X)
							aniId = ID_ANI_MARIO_MAX_WALKING_LEFT;
					}
					else
					{
						aniId = ID_ANI_MARIO_MAX_WALKING_LEFT;
					}

				}
	}
	if (aniId == -1) aniId = ID_ANI_MARIO_MAX_IDLE_RIGHT;

	return aniId;
}

void CMario::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_MAX)
		aniId = GetAniIdMax();

	animations->Get(aniId)->Render(x, y);

	RenderBoundingBox();
	
	DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) return; 

	switch (state)
	{
	case MARIO_STATE_HOLD:
		
		if (!isHolding) break;
		
		break;
	case MARIO_STATE_HOLD_RELEASE:
		hold_start = 0;
		if (isHolding && heldObject != NULL)
		{
			CKoopas* koopas = dynamic_cast<CKoopas*>(heldObject);
			if (koopas)
			{
				koopas->SetState(KOOPAS_STATE_SHELL_MOVING);
				// Throw shell in facing direction
				koopas->SetSpeed(nx > 0 ? KOOPAS_SHELL_MOVING_SPEED : -KOOPAS_SHELL_MOVING_SPEED, 0);
				float kx, ky;
			
				
				koopas->GetPosition(kx, ky);
				if (level == MARIO_LEVEL_SMALL)
					ky -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT)/2;
				koopas->SetPosition(kx, ky);
			
			}
			SetHolding(false, NULL);
		}
		break;
	case MARIO_STATE_RUNNING_RIGHT:
		

		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		StartRunning();
		
		break;
	case MARIO_STATE_RUNNING_LEFT:
		
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		StartRunning();
		break;
	case MARIO_STATE_WALKING_RIGHT:
		
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		
		break;
	case MARIO_STATE_WALKING_LEFT:
		
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		
		if (isOnPlatform)
		{
			if (isFlying )
				vy = -MARIO_JUMP_FLY_SPEED_Y; 
			else if (abs(this->vx) == MARIO_RUNNING_SPEED)
				vy = -MARIO_JUMP_RUN_SPEED_Y;
			else
				vy = -MARIO_JUMP_SPEED_Y;
		}
		else
		{
			if (isFlying)
			{
				vy = -MARIO_JUMP_FLY_SPEED_Y;

			}
		}
		
	
		
		break;

	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		if (vy == 0)
		{
			vx = 0;
		}
	
		break;

	case MARIO_STATE_SIT:
		isFlying = false;
		StopRunning();
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y +=MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	case MARIO_STATE_SLIP_RIGHT:
		
		if (isOnPlatform)  
		{
			maxVx = MARIO_SLIP_SPEED;  
			ax = -MARIO_SLIP_DECEL;    
			                  
		}
		break;
	case MARIO_STATE_SLIP_LEFT:
		if (isOnPlatform)  
		{
			maxVx = -MARIO_SLIP_SPEED; 
			ax = MARIO_SLIP_DECEL;      
			                  
		}
		break;
		
	}
	

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (level==MARIO_LEVEL_BIG)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else 
		{
			left = x - MARIO_BIG_BBOX_WIDTH/2;
			top = y - MARIO_BIG_BBOX_HEIGHT/2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if(level == MARIO_LEVEL_MAX)
	{
		if (isSitting)
		{
			left = x - MARIO_MAX_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_MAX_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_MAX_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_MAX_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_MAX_BBOX_WIDTH / 2;
			top = y - MARIO_MAX_BBOX_HEIGHT / 2;
			right = left + MARIO_MAX_BBOX_WIDTH;
			bottom = top + MARIO_MAX_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH/2;
		top = y - MARIO_SMALL_BBOX_HEIGHT/2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT+1;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	level = l;
}

