#include "Bomerang.h"
#include "Game.h"
#include "Sprites.h"
#include "Animations.h"
#include "debug.h"
#include "BomerangBro.h"
#include "Mario.h"

CBoomerang::CBoomerang(float x, float y, float direction, CBomerangBro* owner) : CGameObject(x, y)
{
    this->startX = x;
    this->startY = y;
    this->owner = owner;
    this->isReturning = false;
    this->vx = direction * BOOMERANG_SPEED;
    this->vy = 0.0f;
    this->ax = 0.0f;
    this->ay = 0.0f; 
    this->startTime = GetTickCount();
}

void CBoomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - BOOMERANG_BBOX_WIDTH / 2;
    t = y - BOOMERANG_BBOX_HEIGHT / 2;
    r = l + BOOMERANG_BBOX_WIDTH;
    b = t + BOOMERANG_BBOX_HEIGHT;
}

void CBoomerang::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}


void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    ULONGLONG now = GetTickCount();
    DWORD elapsed = now - startTime;
     float angle = (elapsed % (DWORD)CYCLE_TIME) * 2 * PI / CYCLE_TIME;

     if (!isReturning)
    {
         vy = BOOMERANG_AMPLITUDE * sin(angle) * 0.001f;  
        y = startY - BOOMERANG_AMPLITUDE * sin(angle);  
    }
    else
    {
         vy = -BOOMERANG_AMPLITUDE * sin(angle) * 0.001f;  
        y = startY + BOOMERANG_AMPLITUDE * sin(angle);  

         float dx = startX - x;
        if (abs(dx) < 1.0f)  
        {
            DebugOut(L"[INFO] Boomerang reached starting x position (%f) at 04:07 PM +07, May 18, 2025\n", startX);
            isDeleted = true;
            return;
        }
        else
        {
             vx = dx * 0.0015f;  
            y = startY + BOOMERANG_AMPLITUDE * sin(angle); 
        }
    }

     float distance = abs(x - startX);
    if (!isReturning && distance > BOOMERANG_MAX_DISTANCE)
    {
        isReturning = true;
        vx = -vx;  
        startTime = now;
    }

     if (owner && owner->IsDeleted())
    {
        owner = nullptr;
    }

    x += vx * dt;
    y += vy * dt;

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBoomerang::Render()
{
    CAnimations::GetInstance()->Get(ID_ANI_BOOMERANG)->Render(x, y);
}