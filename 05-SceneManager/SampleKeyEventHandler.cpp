﻿#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario *)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer(); 

	switch (KeyCode)
	{
	case DIK_DOWN:
		if (alreadySit == false)
		{
			alreadySit = true;
			if (!(mario->isFlying && !mario->isOnPlatform))

				mario->SetState(MARIO_STATE_SIT);
		}
		break;
	case DIK_A:
		mario->whip_start = 0;
		mario->StartWhip();
		break;
	case DIK_S:
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_MAX);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:


		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		holdingS = false;
		break;
	case DIK_DOWN:
		alreadySit = false;
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A: 
		if(mario->isOnPlatform)
		mario->StopRunning();
		if (GetTickCount64() - mario->whip_start > MARIO_WHIP_TIME)
		mario->StopWhip();
		mario->SetState(MARIO_STATE_HOLD_RELEASE);
		break;
	case DIK_RIGHT:
		if (mario->isOnPlatform)
		mario->StopRunning();
		break;
	case DIK_LEFT:
		if (mario->isOnPlatform)
		mario->StopRunning();
		break;


	}
}

void CSampleKeyHandler::KeyState(BYTE *states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	// Kiểm tra trạng thái kìm tốc độ rơi
	if (game->IsKeyDown(DIK_DOWN))
	{
		
		if (game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT))
		{
			if (alreadySit)
			{
				alreadySit = false;
				mario->SetState(MARIO_STATE_SIT_RELEASE);
			}
		}
		else
		{
			
			if (!alreadySit)
			{
				alreadySit = true;
				if (!(mario->isFlying && !mario->isOnPlatform))
					mario->SetState(MARIO_STATE_SIT);
			}
		}
	}
	if (game->IsKeyDown(DIK_S) && mario->level == MARIO_LEVEL_MAX && mario->vy > 0 && mario->isOnPlatform==false)
	{
		
		if (holdingS==false)
		{
			holdingS = true;
			mario->StartSlowFalling();
		}
	}
	else
	{

	}
	if (mario->IsHolding())
	{
		mario->SetState(MARIO_STATE_HOLD);
	}	
	if (game->IsKeyDown(DIK_RIGHT) &&mario->teleport == 0)
	{
	
	
		mario->maxVx = MARIO_RUNNING_SPEED;
		mario->ax = MARIO_ACCEL_RUN_X;
		if(mario->isFlying ==true)
		/*mario->ay = MARIO_GRAVITY_FLY;*/
		mario->nx = 1;
		if (game->IsKeyDown(DIK_A))
		{

			
			mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		}
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT)&&mario->teleport==0)
	{
		mario->maxVx = -MARIO_RUNNING_SPEED;
		mario->ax = -MARIO_ACCEL_RUN_X;
		mario->nx = 1;
		
		if (game->IsKeyDown(DIK_A))
			mario->SetState(MARIO_STATE_RUNNING_LEFT);
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
	{
		if (mario->GetDirection() == 1)
			mario->SetState(MARIO_STATE_SLIP_RIGHT);
		else
			mario->SetState(MARIO_STATE_SLIP_LEFT);	}
}