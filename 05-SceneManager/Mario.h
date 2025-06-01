#pragma once
#include "GameObject.h"
#include "Game.h" // Ensure the header file for CGame is included

#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0005f
#define MARIO_ACCEL_RUN_X	0.0007f
#define MARIO_SLIP_SPEED 0.3f       // Tốc độ trượt ban đầu
#define MARIO_SLIP_DECEL 0.00025f     // Gia tốc giảm dần khi trượt

#define MARIO_JUMP_SPEED_Y		0.40f
#define MARIO_JUMP_RUN_SPEED_Y	0.45f
#define MARIO_JUMP_FLY_SPEED_Y 0.5f
#define MARIO_FLY_ACTIVATION_TIME 1100
#define MARIO_TELEPORT_DURATION 1000

#define MARIO_WHIP_TIME 150 



#define MARIO_GRAVITY			0.00100f
#define MARIO_GRAVITY_FLY		0.00100f

#define MARIO_JUMP_DEFLECT_SPEED  0.2f

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
#define MARIO_STATE_GROWING 900
#define MARIO_STATE_SHRINKING 901
#define MARIO_STATE_WIN 123456
//#define MARIO_STATE_DIVE_IN_CHIMNNEY 911


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
#define ID_ANI_MARIO_DIVE_IN 1006


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
#define ID_ANI_MARIO_DEF_GRAVITY_RIGHT 4010
#define ID_ANI_MARIO_DEF_GRAVITY_LEFT 4011




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

#define MARIO_TELEPORT_IN 1
#define MARIO_TELEPORT_IN_POSITION_Y 200
#define MARIO_TELEPORT_IN_POSITION_X_MOVE 163
#define MARIO_TELEPORT_OUT 2
#define MARIO_TELEPORT_OUT_POSITION_Y 160
#define MARIO_TELEPORT_NONE 0
#define MOVABLEPLATFORM_NUM 13


#define MARIO_SLOW_FALL_SPEED_Y 0.05f  // Tốc độ rơi chậm khi kìm
#define MARIO_SLOW_FALL_GRAVITY 0.0005f // Trọng lực giảm khi kìm
#define MARIO_SLOW_FALL_MAX_TIME 700  // Thời gian tối đa có thể kìm (ms)


#define MARIO_TRANSITION_TIME 500
struct MarioState {
    float x, y; // Vị trí
    float vx, vy; // Vận tốc
    int level; // Cấp độ (small, big)
    int coin; // Số xu
    int untouchable; // Trạng thái bất tử
    ULONGLONG untouchable_start; // Thời gian bắt đầu bất tử
    bool isSitting; // Trạng thái ngồi
    bool isOnPlatform; // Trạng thái trên nền
    int nx; // Hướng (1 hoặc -1)
    int state; // Trạng thái hiện tại
};
class CMario : public CGameObject
{
	BOOLEAN isSitting;
	



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
	void OnCollisionWithWingedKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithCPiranhaPlant(LPCOLLISIONEVENT e);
 	void OnCollisionWithCHiddenButton(LPCOLLISIONEVENT e);
	void OnCollisionWithButton(LPCOLLISIONEVENT e);
	void OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e);
 	void OnCollisionWithCMovablePlatform(LPCOLLISIONEVENT e);
	void OnCollisionWithBomerangBro(LPCOLLISIONEVENT e);
	void OnCollisionWithBomerang(LPCOLLISIONEVENT e);
	void OnCollisionWithCoinBrick(LPCOLLISIONEVENT e);
 	void OnCollisionWithGreenMushroom(LPCOLLISIONEVENT e);
 	void OnCollisionWithWingedRedKoopa(LPCOLLISIONEVENT e);
	void OnCollisionWithBlackGiftBox(LPCOLLISIONEVENT e);

 	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdMax();
	ULONGLONG hold_start;
	ULONGLONG lastEnergyUpdate; // Thời điểm cập nhật energy gần nhất
public:
	ULONGLONG transition_start; // Thời điểm bắt đầu hiệu ứng
	int target_level; // Cấp độ mục tiêu (để biết phóng to hay thu nhỏ)
	BOOLEAN isSlowFalling;      // Trạng thái đang kìm tốc độ rơi
	ULONGLONG slow_fall_start;  // Thời gian bắt đầu kìm tốc độ
	int untouchable;
	int level;
	bool isWon;
	float winDistance;

	BOOLEAN isFallingFromHeight;

	BOOLEAN isOnPlatform;
	bool isFlying;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	float maxVx;
	bool isOpenBlackBox;
	ULONGLONG run_start;

	bool isVisible;
	bool isWaitingForLevelUp = false;
	DWORD timeWaitingStart = 0;
	float saved_x, saved_y;

	ULONGLONG whip_start;
	float teleport;
	float teleportState;
	int renderedGoombaNum;
	int renderedKoopas;
 	int renderedMovablePlatforms [MOVABLEPLATFORM_NUM];
	ULONGLONG teleport_start;
	ULONGLONG teleport_start_out;
	bool onMovable;
	bool isBomerangBroRendered;
	bool typeout;

	CMario(float x, float y) : CGameObject(x, y)
	{
		CGame* cgame = CGame::GetInstance();
		level = cgame->marioLevel;
		typeout = 1;
		onMovable = false;
		isVisible = true;
		isSitting = false;
		maxVx = 0.0f;
		ax = 0.0f;
		ay = MARIO_GRAVITY;
		isBomerangBroRendered = false;
		isWon = false;

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
		isOpenBlackBox = false;
		winDistance = 0;

		teleport = 0;
		teleportState = 0;
		renderedGoombaNum = 0;
		renderedKoopas = 0;
 		isSlowFalling = false;      // Khởi tạo trạng thái kìm tốc độ
		slow_fall_start = 0;
 		for (int i = 0; i < MOVABLEPLATFORM_NUM; i++)
		{
			renderedMovablePlatforms[i] = 0;
		}

		transition_start = -1;
		target_level = MARIO_LEVEL_BIG;
 		teleport_start = -1;
		teleport_start_out = -1;
 		lastEnergyUpdate = 0;
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
	void StartSlowFalling() { isSlowFalling = true; slow_fall_start = GetTickCount64(); }
	void StopSlowFalling() { isSlowFalling = false; slow_fall_start = 0; ay = MARIO_GRAVITY; }
	BOOLEAN IsSlowFalling() { return isSlowFalling; }
	

};