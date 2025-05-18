#pragma once
#include "GameObject.h"
#include "Mario.h"

#define BOMERANG_BRO_GRAVITY 0.002f
#define BOMERANG_BRO_WALKING_SPEED 0.02f
#define BOMERANG_BRO_JUMP_SPEED -0.2f
#define BOMERANG_BRO_FALL_SPEED -0.28f
#define BOMERANG_BRO_FALL_SPEED_HORIZONTAL 0.15f

#define BOMERANG_BRO_BBOX_WIDTH 16
#define BOMERANG_BRO_BBOX_HEIGHT 20

#define BOMERANG_BRO_DIE_TIMEOUT 500
#define BOMERANG_BRO_THROW_INTERVAL 3000 
#define BOMERANG_BRO_THROW_PAUSE 2000
#define BOMERANG_BRO_THROW_COOLDOWN 4000 

#define BOMERANG_BRO_STATE_WALKING_RIGHT 100
#define BOMERANG_BRO_STATE_WALKING_LEFT 101
#define BOMERANG_BRO_STATE_DIE 200
#define BOMERANG_BRO_STATE_FALL 300
#define BOMERANG_BRO_STATE_THROW 400

#define ID_ANI_BOMERANG_BRO_WALKING_RIGHT 290005
#define ID_ANI_BOMERANG_BRO_WALKING_LEFT 290012
#define ID_ANI_BOMERANG_BRO_DIE 290006
#define ID_ANI_BOMERANG_BRO_THROW 290007

class CBomerangBro : public CGameObject
{
protected:
    float ax;
    float ay;
    ULONGLONG die_start;
    ULONGLONG throw_start;  
    int throw_count;  
    CMario* mario;

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual int IsCollidable() { return state != BOMERANG_BRO_STATE_FALL; }
    virtual int IsBlocking() { return 0; }
    virtual void OnNoCollision(DWORD dt);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
    CBomerangBro(float x, float y);
    virtual void SetState(int state);
    void SetMario(CMario* m) { mario = m; }
};