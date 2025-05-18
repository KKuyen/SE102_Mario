#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "BomerangBro.h"

#define BOOMERANG_SPEED 0.06f  
#define BOOMERANG_BBOX_WIDTH 16
#define BOOMERANG_BBOX_HEIGHT 16
#define BOOMERANG_MAX_DISTANCE 180.0f
#define BOOMERANG_GRAVITY 0.0005f
#define BOOMERANG_AMPLITUDE 32.0f  

#define ID_ANI_BOOMERANG 310000

class CBoomerang : public CGameObject
{
protected:
    float startX;
    float startY;
    float ax, ay;
    CBomerangBro* owner;
    bool isReturning;
    DWORD startTime;

public:
    CBoomerang(float x, float y, float direction, CBomerangBro* owner);
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void GetBoundingBox(float& l, float& t, float& r, float& b);
    void OnNoCollision(DWORD dt);
     int IsCollidable() { return 1; }
    int IsBlocking() { return 0; }
};