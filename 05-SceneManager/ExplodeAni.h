#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define ID_ANI_EXPLODE 80000 // ID cho animation nổ
#define EXPLODE_DURATION 300 // Thời gian tồn tại: 1 giây (1000ms)
#define EXPLODE_BBOX_WIDTH 16
#define EXPLODE_BBOX_HEIGHT 16

class CExplodeAni : public CGameObject
{
protected:
    ULONGLONG start_time; // Thời điểm bắt đầu hiệu ứng

public:
    CExplodeAni(float x, float y);
    void Render() override;
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL) override;
    void GetBoundingBox(float& left, float& top, float& right, float& bottom) override;
    int IsCollidable() { return 0; } // Không va chạm
    int IsBlocking() { return 0; } // Không chặn
}; 
