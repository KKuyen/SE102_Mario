#pragma once
#include "GameObject.h"

#define BRICK_PART_BBOX_WIDTH 8
#define BRICK_PART_BBOX_HEIGHT 8

#define BRICK_PART_SPEED_Y 0.2f
#define BRICK_PART_SPEED_X 0.05f
#define BRICK_PART_GRAVITY 0.0008f
#define BRICK_PART_LIFETIME 1000 // Thời gian tồn tại của mảnh vỡ (ms)

class CBreakableBrickPart : public CGameObject
{
protected:

    ULONGLONG spawn_time; // Thời điểm mảnh vỡ được tạo ra
    float initial_vx; // Vận tốc ban đầu theo trục X
    float initial_vy; // Vận tốc ban đầu theo trục Y

public:
    float ax;
    float ay;
    CBreakableBrickPart(float x, float y, float vx, float vy);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();
    virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

    virtual int IsCollidable() { return 0; } // Không va chạm với các đối tượng khác
    virtual int IsBlocking() { return 0; } // Không chặn các đối tượng khác
};