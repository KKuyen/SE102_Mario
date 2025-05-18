#include "Koopas.h"
#include "Game.h"
#include "debug.h"
#include "Goomba.h"
#include "Mario.h"
#include "Platform.h"
#include "Brick.h"
#include "ColorBox.h"
#include "GiftBox.h"
#include "BreakableBrick.h"
#include "GrassPlatform.h"

CKoopas::CKoopas(float x, float y, int type) : CGameObject(x, y)
{
    this->ax = 0;
    this->ay = KOOPAS_GRAVITY;
    this->nx = -1;
    this->color = 1;
    this->type = type;
    this->isReverse = false;
    if (type == 1)
    {
        SetState(KOOPAS_STATE_DOWN);
    }
    else
    {
        SetState(KOOPAS_STATE_WALKING);
    }
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_SHELL_MOVING || state == KOOPAS_STATE_HELD || state == KOOPAS_STATE_REVERSE)
    {
        left = x - KOOPAS_BBOX_WIDTH / 2 + 2;
        top = y - KOOPAS_BBOX_HEIGHT_SHELL / 2;
        right = left + KOOPAS_BBOX_WIDTH - 2;
        bottom = top + KOOPAS_BBOX_HEIGHT_SHELL;
    }
    else
    {
        left = x - KOOPAS_BBOX_WIDTH / 2;
        top = y - KOOPAS_BBOX_HEIGHT / 2;
        right = left + KOOPAS_BBOX_WIDTH;
        bottom = top + KOOPAS_BBOX_HEIGHT;
    }
}

void CKoopas::OnNoCollision(DWORD dt)
{
    if (type == 1)
    {
        if (state == KOOPAS_STATE_UP)
        {
            y -= KOOPAS_VERTICAL_MOVE_SPEED * dt;
        }
        else if (state == KOOPAS_STATE_DOWN)
        {
            y += KOOPAS_VERTICAL_MOVE_SPEED * dt;
        }
        else if (state == KOOPAS_STATE_WALKING)
        {
            y -= KOOPAS_FALL_SPEED * dt;
        }
    }
    else
    {
        x += vx * dt;
        y += vy * dt;
    }
}

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!e->obj->IsBlocking()) return;
    if (dynamic_cast<CKoopas*>(e->obj)) return;
    if (dynamic_cast<CMario*>(e->obj))
    {
        mario = dynamic_cast<CMario*>(e->obj);
    }
    if (state == KOOPAS_STATE_REVERSE &&
        (dynamic_cast<CPlatform*>(e->obj) || dynamic_cast<CColorBox*>(e->obj) || dynamic_cast<CBrick*>(e->obj) || dynamic_cast<CBreakableBrick*>(e->obj)))
    {
        ax = 0;
        vx = 0;
        vy = 0;
        ay = 0;
        state = KOOPAS_STATE_SHELL;
    }
    if (state == KOOPAS_STATE_FALL &&
        (dynamic_cast<CGrassPlatform*>(e->obj) || dynamic_cast<CPlatform*>(e->obj) || dynamic_cast<CColorBox*>(e->obj) || dynamic_cast<CBrick*>(e->obj)))
    {
        return;
    }
    if (e->ny != 0)
    {
        vy = 0;
    }
    else if (e->nx != 0)
    {
        if (state == KOOPAS_STATE_WALKING)
            SetState(KOOPAS_STATE_WALKING_RIGHT);
        else if (state == KOOPAS_STATE_WALKING_RIGHT)
            SetState(KOOPAS_STATE_WALKING);
        else if (state == KOOPAS_STATE_SHELL_MOVING)
        {
            if (dynamic_cast<CGoomba*>(e->obj))
            {
                CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
                goomba->SetState(GOOMBA_STATE_FALL);
            }
            else if (e->obj->IsBlocking())
            {
                vx = -vx;
                nx = -nx;
            }
            if (dynamic_cast<CGiftBox*>(e->obj))
            {
                CGiftBox* giftbox = dynamic_cast<CGiftBox*>(e->obj);
                if (giftbox->GetState() == GIFTBOX_STATE_SHOWING)
                {
                    giftbox->Open(mario);
                }
            }
        }
    }
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (type == 1)
    {
        if (state == KOOPAS_STATE_UP && y <= MIN_VERTICAL_MOVE)
        {
            SetState(KOOPAS_STATE_DOWN);
        }
        else if (state == KOOPAS_STATE_DOWN && y >= MAX_VERTICAL_MOVE)
        {
            SetState(KOOPAS_STATE_UP);
        }
    }
    else
    {
        vy += ay * dt;
        vx += ax * dt;

        if (state == KOOPAS_STATE_HELD)
        {
            vx = 0;
            vy = 0;
            ay = 0;
            return;
        }

        // Check platform edges
        if (state == KOOPAS_STATE_WALKING || state == KOOPAS_STATE_WALKING_RIGHT)
        {
            bool isOnPlatform = false;
            float platformLeft, platformRight;

            for (LPGAMEOBJECT obj : *coObjects)
            {
                if (dynamic_cast<CGrassPlatform*>(obj) || dynamic_cast<CPlatform*>(obj) ||
                    (dynamic_cast<CColorBox*>(obj) && dynamic_cast<CColorBox*>(obj)->isPlatform == 1) ||
                    dynamic_cast<CBrick*>(obj) || dynamic_cast<CBreakableBrick*>(obj))
                {
                    float l, t, r, b;
                    obj->GetBoundingBox(l, t, r, b);

                    float koopasLeft, koopasTop, koopasRight, koopasBottom;
                    GetBoundingBox(koopasLeft, koopasTop, koopasRight, koopasBottom);

                    if (koopasBottom <= t + 1.0f && koopasBottom >= t - 1.0f &&
                        koopasLeft <= r && koopasRight >= l)
                    {
                        isOnPlatform = true;
                        platformLeft = l;
                        platformRight = r + 16;
                        break;
                    }
                }
            }

            if (isOnPlatform)
            {
                float nextX = x + vx * dt;
                if (state == KOOPAS_STATE_WALKING && nextX <= platformLeft + KOOPAS_BBOX_WIDTH / 2)
                {
                    SetState(KOOPAS_STATE_WALKING_RIGHT);
                }
                else if (state == KOOPAS_STATE_WALKING_RIGHT && nextX >= platformRight - KOOPAS_BBOX_WIDTH / 2)
                {
                    SetState(KOOPAS_STATE_WALKING);
                }
            }
        }

        // Check revive timer
        if ((state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_HELD || state == KOOPAS_STATE_REVERSE) &&
            revive_start != 0 && GetTickCount64() - revive_start >= KOOPAS_REVIVE_TIME)
        {
            y -= 3;
            vy = KOOPAS_JUMP_SPEED;
            ay = KOOPAS_GRAVITY;
            if (nx < 0)
                SetState(KOOPAS_STATE_WALKING);
            else
                SetState(KOOPAS_STATE_WALKING_RIGHT);
        }
    }

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::Render()
{
    if (type == 1)
    {
        int aniId = ID_ANI_WINGED_RED_KOOPA;
        if (state == KOOPAS_STATE_WALKING)
        {
            aniId = ID_ANI_KOOPAS_WALKING;
        }
        LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
        if (ani == nullptr)
        {
            DebugOut(L"[ERROR] Animation ID %d not found!\n", aniId);
            return;
        }
        ani->Render(x, y);
    }
    else
    {
        int aniId;
        if (color == 1)
        {
            aniId = ID_ANI_KOOPAS_WALKING;
            if (state == KOOPAS_STATE_WALKING_RIGHT)
                aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
            if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_HELD)
            {
                if (!isReverse)
                    aniId = ID_ANI_KOOPAS_SHELL;
                else
                    aniId = ID_ANI_KOOPAS_FALL;
            }
            else if (state == KOOPAS_STATE_SHELL_MOVING)
            {
                if (!isReverse)
                    aniId = ID_ANI_KOOPAS_SHELL_MOVING;
                else
                    aniId = ID_ANI_KOOPAS_FALL;
            }
            else if (state == KOOPAS_STATE_FALL || state == KOOPAS_STATE_REVERSE)
                aniId = ID_ANI_KOOPAS_FALL;
        }
        else
        {
            aniId = ID_ANI_KOOPAS_GREEN_WALKING;
            if (state == KOOPAS_STATE_WALKING_RIGHT)
                aniId = ID_ANI_KOOPAS_GREEN_WALKING_RIGHT;
            if (state == KOOPAS_STATE_SHELL || state == KOOPAS_STATE_HELD)
            {
                if (!isReverse)
                    aniId = ID_ANI_KOOPAS_GREEN_SHELL;
                else
                    aniId = ID_ANI_KOOPAS_GREEN_FALL;
            }
            else if (state == KOOPAS_STATE_SHELL_MOVING)
            {
                
                if (!isReverse)
                {
                   
                    aniId = ID_ANI_KOOPAS_GREEN_SHELL_MOVING;
                }
                else
                {
                    aniId = ID_ANI_KOOPAS_GREEN_FALL;
                  
                }
            }
            else if (state == KOOPAS_STATE_FALL || state == KOOPAS_STATE_REVERSE)
                aniId = ID_ANI_KOOPAS_GREEN_FALL;
        }

        LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
        if (ani == nullptr)
        {
            DebugOut(L"[ERROR] Animation ID %d not found!\n", aniId);
            return;
        }
        ani->Render(x, y);
    }
}

void CKoopas::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
        case KOOPAS_STATE_WALKING:
            vx = -KOOPAS_WALKING_SPEED;
            nx = -nx;
            revive_start = 0;
            isReverse = false;
            break;
        case KOOPAS_STATE_WALKING_RIGHT:
            vx = KOOPAS_WALKING_SPEED;
            nx = -nx;
            revive_start = 0;
            isReverse = false;
            break;
        case KOOPAS_STATE_SHELL:
            y -= 5;
            vx = 0;
            vy = KOOPAS_JUMP_SPEED / 4;
            ax = 0;
            ay = KOOPAS_GRAVITY;
            StartReviveTimer();
            isReverse = false;
            break;
        case KOOPAS_STATE_HELD:
            vx = 0;
            vy = 0;
            ax = 0;
            ay = 0;
            StartReviveTimer();
            isReverse = false;
            break;
        case KOOPAS_STATE_SHELL_MOVING:
            vx = nx * KOOPAS_SHELL_MOVING_SPEED;
            vy = 0;
            ay = KOOPAS_GRAVITY;
            StartReviveTimer();
            isReverse = false;
            break;
        case KOOPAS_STATE_FALL:
            vx = nx * KOOPAS_FALL_SPEED_HORIZONTAL;
            vy = KOOPAS_FALL_SPEED;
            ay = KOOPAS_GRAVITY_FALL;
            revive_start = 0;
            isReverse = false;
            break;
        case KOOPAS_STATE_REVERSE:
            isReverse = true;
            vx = nx * KOOPAS_FALL_SPEED_HORIZONTAL;
            vy = KOOPAS_FALL_SPEED * 2;
            ay = KOOPAS_GRAVITY_FALL;
            StartReviveTimer();
            break;
        case KOOPAS_STATE_UP:
            if (type == 1)
            {
                vx = 0;
                vy = 0;
                ay = 0;
                revive_start = 0;
            }
            break;
        case KOOPAS_STATE_DOWN:
            if (type == 1)
            {
                vx = 0;
                vy = 0;
                ay = 0;
                revive_start = 0;
            }
            break;
    }
}