#include "ExplodeAni.h"
#include "Game.h"
#include "BreakableBrick.h"

CExplodeAni::CExplodeAni(float x, float y) : CGameObject(x, y)
{
    start_time = GetTickCount64(); // Lưu thời điểm bắt đầu
}

void CExplodeAni::Render()
{
    CAnimations* animations = CAnimations::GetInstance();
    animations->Get(ID_ANI_EXPLODE)->Render(x, y);
    // RenderBoundingBox(); // Có thể bật để debug
}

void CExplodeAni::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    // Kiểm tra nếu đã tồn tại quá 1 giây
    if (GetTickCount64() - start_time > EXPLODE_DURATION)
    {
        isDeleted = true; // Đánh dấu đối tượng để xóa
        return;
    }

    CGameObject::Update(dt, coObjects);
}

void CExplodeAni::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
    left = x - EXPLODE_BBOX_WIDTH / 2;
    top = y - EXPLODE_BBOX_HEIGHT / 2;
    right = left + EXPLODE_BBOX_WIDTH;
    bottom = top + EXPLODE_BBOX_HEIGHT;
}