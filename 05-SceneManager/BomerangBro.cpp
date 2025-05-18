#include "BomerangBro.h"
#include "Bomerang.h"
#include "Koopas.h"
#include "PlayScene.h"

CBomerangBro::CBomerangBro(float x, float y) : CGameObject(x, y)
{
    this->ax = 0;
    this->ay = BOMERANG_BRO_GRAVITY;
    die_start = -1;
    throw_start = -1;
    throw_count = 0;
    SetState(BOMERANG_BRO_STATE_WALKING_RIGHT);
    mario = nullptr;
}

void CBomerangBro::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - BOMERANG_BRO_BBOX_WIDTH / 2;
    top = y - BOMERANG_BRO_BBOX_HEIGHT / 2;
    right = left + BOMERANG_BRO_BBOX_WIDTH;
    bottom = top + BOMERANG_BRO_BBOX_HEIGHT;
}

void CBomerangBro::OnNoCollision(DWORD dt)
{
    x += vx * dt;
    y += vy * dt;
}

void CBomerangBro::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!e->obj->IsBlocking()) return;

    if (e->ny != 0)
    {
        vy = 0;
    }
    else if (e->nx != 0)
    {
        vx = -vx;
    }
}

void CBomerangBro::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    vy += ay * dt;
    vx += ax * dt;

    // ?i?u ch?nh h??ng theo Mario
    if (mario != nullptr)
    {
        float mario_x, mario_y;
        mario->GetPosition(mario_x, mario_y);
        bool isMarioRight = (mario_x > x);
        if (isMarioRight && vx < 0)
        {
            vx = -vx;
        }
        else if (!isMarioRight && vx > 0)
        {
            vx = -vx;
        }

        // Ném boomerang: 2 l?n liên ti?p, sau ?ó ngh?
        ULONGLONG now = GetTickCount64();
        if (state != BOMERANG_BRO_STATE_DIE && state != BOMERANG_BRO_STATE_FALL)
        {
            if (throw_count < 2 && (throw_start == -1 || now - throw_start > BOMERANG_BRO_THROW_INTERVAL))
            {
                SetState(BOMERANG_BRO_STATE_THROW);
                throw_start = now;
                throw_count++;

                // T?o boomerang
                float direction = isMarioRight ? 1.0f : -1.0f;
                CBoomerang* boomerang = new CBoomerang(x, y, direction, this);
                CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
                if (currentScene)
                {
                    currentScene->PushBackGameObject(boomerang);
                }
            }
            else if (throw_count >= 2 && now - throw_start > BOMERANG_BRO_THROW_COOLDOWN)
            {
                throw_count = 0; // Reset ?? b?t ??u chu k? ném m?i
                throw_start = -1;
            }
        }

        // K?t thúc tr?ng thái ném
        if (state == BOMERANG_BRO_STATE_THROW && now - throw_start > BOMERANG_BRO_THROW_PAUSE)
        {
            SetState(isMarioRight ? BOMERANG_BRO_STATE_WALKING_RIGHT : BOMERANG_BRO_STATE_WALKING_LEFT);
        }
    }

    // X? lý tr?ng thái ch?t
    if ((state == BOMERANG_BRO_STATE_DIE) && (GetTickCount64() - die_start > BOMERANG_BRO_DIE_TIMEOUT))
    {
        isDeleted = true;
        return;
    }

    // C?p nh?t tr?ng thái di chuy?n
    if (vx < 0)
    {
        if (state == BOMERANG_BRO_STATE_WALKING_RIGHT)
            SetState(BOMERANG_BRO_STATE_WALKING_LEFT);
    }
    else if (vx > 0)
    {
        if (state == BOMERANG_BRO_STATE_WALKING_LEFT)
            SetState(BOMERANG_BRO_STATE_WALKING_RIGHT);
    }

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBomerangBro::Render()
{
    int aniId;
    if (state == BOMERANG_BRO_STATE_WALKING_RIGHT)
    {
        aniId = ID_ANI_BOMERANG_BRO_WALKING_RIGHT;
    }
    else if (state == BOMERANG_BRO_STATE_WALKING_LEFT)
    {
        aniId = ID_ANI_BOMERANG_BRO_WALKING_LEFT;
    }
    else if (state == BOMERANG_BRO_STATE_DIE || state == BOMERANG_BRO_STATE_FALL)
    {
        aniId = ID_ANI_BOMERANG_BRO_DIE;
        CSprites::GetInstance()->Get(aniId)->Draw(x, y);
        return;
    }
    else if (state == BOMERANG_BRO_STATE_THROW)
    {
        aniId = ID_ANI_BOMERANG_BRO_THROW;
    }

    CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CBomerangBro::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case BOMERANG_BRO_STATE_DIE:
        die_start = GetTickCount64();
        vx = 0;
        vy = 0;
        ay = 0;
        break;
    case BOMERANG_BRO_STATE_WALKING_RIGHT:
        vx = BOMERANG_BRO_WALKING_SPEED;
        break;
    case BOMERANG_BRO_STATE_WALKING_LEFT:
        vx = -BOMERANG_BRO_WALKING_SPEED;
        break;
    case BOMERANG_BRO_STATE_FALL:
        die_start = GetTickCount64();
        vx = nx * BOMERANG_BRO_FALL_SPEED_HORIZONTAL;
        vy = BOMERANG_BRO_FALL_SPEED;
        ay = BOMERANG_BRO_GRAVITY;
        break;
    case BOMERANG_BRO_STATE_THROW:
        vx = 0; // T?m d?ng di chuy?n khi ném
        break;
    }
}