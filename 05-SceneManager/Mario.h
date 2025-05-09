#pragma once
#include "GameObject.h"

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f
#define MARIO_SLIP_SPEED 0.5f       // Tốc độ trượt ban đầu
#define MARIO_SLIP_DECEL 0.00015f     // Gia tốc giảm dần khi trượt

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f
#define MARIO_JUMP_FLY_SPEED_Y 0.75f
#define MARIO_FLY_ACTIVATION_TIME 1500
#define MARIO_WHIP_TIME 250 



#define MARIO_GRAVITY			0.00165f
#define MARIO_GRAVITY_FLY		0.00160f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601
#define MARIO_STATE_SLIP_RIGHT      700
#define MARIO_STATE_SLIP_LEFT       701
#define MARIO_STATE_HOLD 800
#define MARIO_STATE_HOLD_RELEASE 801


#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999
#define ID_ANI_MARIO_HOLD_RIGHT 1002
#define ID_ANI_MARIO_HOLD_LEFT 1003
#define ID_ANI_MARIO_HOLD_IDLE_RIGHT 1004
#define ID_ANI_MARIO_HOLD_IDLE_LEFT 1005


// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601
#define ID_ANI_MARIO_SMALL_HOLD_RIGHT 1602
#define ID_ANI_MARIO_SMALL_HOLD_LEFT 1603
#define ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT 1604
#define ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT 1605
// MAX MARIO
#define ID_ANI_MARIO_MAX_IDLE_RIGHT 1700
#define ID_ANI_MARIO_MAX_IDLE_LEFT 1702

#define ID_ANI_MARIO_MAX_WALKING_RIGHT 1800
#define ID_ANI_MARIO_MAX_WALKING_LEFT 1801

#define ID_ANI_MARIO_MAX_RUNNING_RIGHT 1900
#define ID_ANI_MARIO_MAX_RUNNING_LEFT 1901

#define ID_ANI_MARIO_MAX_BRACE_RIGHT 2000
#define ID_ANI_MARIO_MAX_BRACE_LEFT 2001

#define ID_ANI_MARIO_MAX_JUMP_WALK_RIGHT 2100
#define ID_ANI_MARIO_MAX_JUMP_WALK_LEFT 2101

#define ID_ANI_MARIO_MAX_JUMP_RUN_RIGHT 2200
#define ID_ANI_MARIO_MAX_JUMP_RUN_LEFT 2201
#define ID_ANI_MARIO_MAX_HOLD_RIGHT 2202
#define ID_ANI_MARIO_MAX_HOLD_LEFT 2203
#define ID_ANI_MARIO_MAX_SIT_RIGHT 4008	
	

#define ID_ANI_MARIO_MAX_SIT_LEFT 4009
#define ID_ANI_MARIO_MAX_HOLD_IDLE_RIGHT 2204
#define ID_ANI_MARIO_MAX_HOLD_IDLE_LEFT 2205
#define ID_ANI_MARIO_MAX_FLYING_RUNNING_RIGHT 3001 
#define ID_ANI_MARIO_MAX_FLYING_RUNNING_LEFT 3002
#define ID_ANI_MARIO_MAX_FLYING_RIGHT 3003 
#define ID_ANI_MARIO_MAX_FLYING_LEFT 3004
#define ID_ANI_MARIO_WHIP_RIGHT 4006// Animation đặc biệt khi chạy
#define ID_ANI_MARIO_WHIP_LEFT 4007


#pragma endregion

#define GROUND_Y 160.0f




#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_MAX     3

#define MARIO_BIG_BBOX_WIDTH  13
#define MARIO_BIG_BBOX_HEIGHT 26
#define MARIO_BIG_SITTING_BBOX_WIDTH  13
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_MAX_BBOX_WIDTH  20
#define MARIO_MAX_BBOX_HEIGHT 26
#define MARIO_MAX_SITTING_BBOX_WIDTH  13
#define MARIO_MAX_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500

class CMario : public CGameObject
{
	BOOLEAN isSitting;
	


	int untouchable; 
	ULONGLONG untouchable_start;

	int coin; 
	BOOLEAN isHolding; 
	LPGAMEOBJECT heldObject; 
	
	bool beforeLand;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithKooPas(LPCOLLISIONEVENT e);
 	void OnCollisionWithWingedGoomba(LPCOLLISIONEVENT e);
 	void OnCollisionWithGiftBox(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithBullet(LPCOLLISIONEVENT e);
	void OnCollisionWithFlower(LPCOLLISIONEVENT e);
	void OnCollisionWithLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithChimney(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdMax();
	ULONGLONG hold_start;
public:

	int level;


	BOOLEAN isFallingFromHeight;

	BOOLEAN isOnPlatform;
	bool isFlying;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float maxVx;
	ULONGLONG run_start;

	bool isVisible;
	bool isWaitingForLevelUp = false;
	DWORD timeWaitingStart = 0;
	float saved_x, saved_y;

	ULONGLONG whip_start;
	float teleport;
	float teleportState;
	int renderedGoombaNum;

	CMario(float x, float y) : CGameObject(x, y)
	{
		isVisible = true;
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;

		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		isOnPlatform = false;
		coin = 0;
		isHolding = false;
		heldObject = NULL;
		hold_start = 0;
		isFlying = false;
		run_start = 0;
		whip_start = 0;
		beforeLand = false;

		teleport = 0;
		teleportState = 0;
		renderedGoombaNum = 0;
	

	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);

	int IsCollidable()
	{ 
		return (state != MARIO_STATE_DIE); 
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable==0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);

	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	int GetDirection();
	BOOLEAN IsHolding() { return isHolding; } 
	void SetHolding(BOOLEAN holding, LPGAMEOBJECT obj = NULL) 
	{
		isHolding = holding;
		heldObject = obj;
		if (isHolding)
			StartHoldTimer(); 
		else
			ResetHoldTimer(); 
	}
	void StartHoldTimer() { hold_start = GetTickCount64(); } 
	void ResetHoldTimer() { hold_start = 0; } 
	void StartRunning() { 
		if(run_start==0)
		run_start = GetTickCount64(); }
	void StartWhip() {
		if (whip_start == 0)
			whip_start = GetTickCount64();
	}
	void StopWhip() { whip_start = 0; }
	void StopRunning() { run_start = 0; isFlying = false; }
	bool IsFlying() { return isFlying; }
	int getLevel() {
		return level;
	}
	

};