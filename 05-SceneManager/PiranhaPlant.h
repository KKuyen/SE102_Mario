#pragma once
#include "GameObject.h"

#define PIRANHA_PLANT_GRAVITY 0.0f // Không chịu ảnh hưởng trọng lực
#define PIRANHA_PLANT_SPEED_Y 0.05f // Tốc độ di chuyển lên xuống
#define PIRANHA_PLANT_BBOX_WIDTH 16
#define PIRANHA_PLANT_RANGE_UP 30
#define PIRANHA_PLANT_BBOX_HEIGHT 24
#define PIRANHA_PLANT_STATE_UP 100 // Trạng thái di chuyển lên
#define PIRANHA_PLANT_STATE_DOWN 200 // Trạng thái di chuyển xuống
#define PIRANHA_PLANT_STATE_IDLE 300 // Trạng thái chờ
#define PIRANHA_PLANT_ANI_UP_DOWN 12000 // ID animation cho trạng thái lên/xuống

#define PIRANHA_PLANT_IDLE_TIME 1000 // Thời gian chờ trước khi đổi trạng thái

class CPiranhaPlant : public CGameObject
{
protected:
    float start_y; // Vị trí y ban đầu (đáy ống)
    float max_y;   // Vị trí y tối đa (đỉnh ống)
    ULONGLONG idle_start; // Thời gian bắt đầu trạng thái chờ

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    virtual void Render();

    virtual int IsCollidable() { return 0; }
    virtual int IsBlocking() { return 0; } // Không chặn Mario
    virtual void OnNoCollision(DWORD dt);
    virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
    CPiranhaPlant(float x, float y, float max_y);
    virtual void SetState(int state);
};