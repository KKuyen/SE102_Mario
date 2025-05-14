#include "BreakableBrickPart.h"
#include "Game.h"
#include "debug.h"
#include "Textures.h"
#include "BreakableBrick.h"

CBreakableBrickPart::CBreakableBrickPart(float x, float y, float vx, float vy) : CGameObject(x, y)
{
    this->initial_vx = vx;
    this->initial_vy = vy;
    this->vx = vx;
    this->vy = vy;
    this->spawn_time = GetTickCount64();
    this->ay = BRICK_PART_GRAVITY; // Áp dụng trọng lực
}

void CBreakableBrickPart::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    // Cập nhật vận tốc
    vy += ay * dt; // Vận tốc theo trục Y chịu ảnh hưởng của trọng lực

    // Cập nhật vị trí
    x += vx * dt;
    y += vy * dt;

    // Kiểm tra thời gian tồn tại
    if (GetTickCount64() - spawn_time > BRICK_PART_LIFETIME)
    {
        isDeleted = true; // Xóa mảnh vỡ sau khi hết thời gian tồn tại
        return;
    }

    CGameObject::Update(dt, coObjects);
}

void CBreakableBrickPart::Render()
{
    // Vẽ mảnh vỡ (có thể sử dụng sprite đơn giản hoặc hình chữ nhật để mô phỏng)
    CGame* game = CGame::GetInstance();
    CAnimations* animations = CAnimations::GetInstance();
    if(ax<0)
    animations->Get(ID_ANI_BREAKABLE_BRICK_BREAK)->Render(x, y);
    else
        animations->Get(ID_ANI_BREAKABLE_BRICK_BREAK_2)->Render(x, y);


    // RenderBoundingBox(); // Có thể bật để debug
}

void CBreakableBrickPart::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - BRICK_PART_BBOX_WIDTH / 2;
    t = y - BRICK_PART_BBOX_HEIGHT / 2;
    r = l + BRICK_PART_BBOX_WIDTH;
    b = t + BRICK_PART_BBOX_HEIGHT;
}