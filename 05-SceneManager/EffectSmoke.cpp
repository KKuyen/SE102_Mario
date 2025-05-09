#include "EffectSmoke.h"

void CEffectSmoke::Render()
{
   static DWORD startTime = GetTickCount();
   DWORD elapsedTime = GetTickCount() - startTime;

   if (elapsedTime <= ANI_TIME)
   {
       CAnimations* ani = CAnimations::GetInstance();
       ani->Get(SMOKE_ANI)->Render(x, y);
       //RenderBoundingBox();
   }
}

void CEffectSmoke::GetBoundingBox(float& l, float& t, float& r, float& b)
{
   l = x - EF_SMOKE_WIDTH / 2;
   t = y - EF_SMOKE_HEIGHT / 2;
   r = l + EF_SMOKE_WIDTH - 1;
   b = t + EF_SMOKE_HEIGHT;
}

void CEffectSmoke::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
   // Update logic if needed
}