#include "PiranhaPlant.h"
#include "Game.h"
#include "Mario.h"
#include "Platform.h"
#include "Brick.h"
#include "Chimney.h"

CPiranhaPlant::CPiranhaPlant(float x, float y, float max_y) : CGameObject(x, y)
{
    this->start_y = y;
    this->max_y = max_y;
    this->vy = 0;
    this->idle_start = -1;
    SetState(PIRANHA_PLANT_STATE_UP);
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - PIRANHA_PLANT_BBOX_WIDTH / 2;
    top = y - PIRANHA_PLANT_BBOX_HEIGHT / 2;
    right = left + PIRANHA_PLANT_BBOX_WIDTH;
    bottom = top + PIRANHA_PLANT_BBOX_HEIGHT;
}

void CPiranhaPlant::OnNoCollision(DWORD dt)
{
    y += vy * dt;
}

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
    // Bỏ qua va chạm với Platform, Brick, và các đối tượng không phải Mario
    if (!dynamic_cast<CMario*>(e->obj) &&
        !dynamic_cast<CChimney*>(e->obj))
        return;

    if (dynamic_cast<CChimney*>(e->obj))
        return;


   
   
}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    // Cập nhật trạng thái
    if (state == PIRANHA_PLANT_STATE_IDLE)
    {
        if (GetTickCount64() - idle_start > PIRANHA_PLANT_IDLE_TIME)
        {
            if (y >= start_y)
            {

                if (y >= start_y)
                {
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

                    // Check if Mario is nearby
                    if (mario)
                    {
                        float marioX, marioY;
                        mario->GetPosition(marioX, marioY);

                        // Define the detection range
                   
                        // Check if Mario is within the detection range
                        if (abs(marioX - x) >= PIRANHA_PLANT_RANGE_UP)
                        {
                            SetState(PIRANHA_PLANT_STATE_UP);
                        }
                    }
                }
            }
            else
                SetState(PIRANHA_PLANT_STATE_DOWN);
        }
    }
    else if (state == PIRANHA_PLANT_STATE_UP)
    {
        if (y <= max_y)
        {
            SetState(PIRANHA_PLANT_STATE_IDLE);
        }
    }
    else if (state == PIRANHA_PLANT_STATE_DOWN)
    {
        if (y >= start_y)
        {
            SetState(PIRANHA_PLANT_STATE_IDLE);
        }
    }

    CGameObject::Update(dt, coObjects);
    CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::Render()
{
    CAnimations::GetInstance()->Get(PIRANHA_PLANT_ANI_UP_DOWN)->Render(x, y);
    RenderBoundingBox();
}

void CPiranhaPlant::SetState(int state)
{
    CGameObject::SetState(state);
    switch (state)
    {
    case PIRANHA_PLANT_STATE_UP:
        vy = -PIRANHA_PLANT_SPEED_Y;
        break;
    case PIRANHA_PLANT_STATE_DOWN:
        vy = PIRANHA_PLANT_SPEED_Y;
        break;
    case PIRANHA_PLANT_STATE_IDLE:
        vy = 0;
        idle_start = GetTickCount64();
        break;
    }
}