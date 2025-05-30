#include "MovablePlatform.h"
#include "Mario.h"
#include "Game.h"
#include "Debug.h"

void CMovablePlatform::Render()
{
	CSprites* s = CSprites::GetInstance();
	s->Get(ID_MOVABLE_PLATFORM1)->Draw(x, y);
	s->Get(ID_MOVABLE_PLATFORM2)->Draw(x+16, y);
	s->Get(ID_MOVABLE_PLATFORM3)->Draw(x+16*2, y);

	//RenderBoundingBox();
}

void CMovablePlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - PLATFORM_WIDTH / 2 + 16;
	t = y - PLATFORM_HEIGHT / 2;
	r = l + PLATFORM_WIDTH;
	b = t + PLATFORM_HEIGHT;
}

void CMovablePlatform::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive == 1) {
		x += vx * dt;
		y += vy * dt;
	}
	else {
		float cx, cy;
		CGame::GetInstance()->GetCamPos(cx, cy);
 		if(cx<2540)
			if (x < cx + SCREEN_WIDTH) {
 				isActive = 1;
			}
		
	}
}
 

void CMovablePlatform::Falling() {
 	if (vy == 0) {
		vx = 0;
		vy = PLATFORM_GRAVITY;
	}
}
int CMovablePlatform::IsDirectionColliable(float nx, float ny)
{
	if (nx == 0 && ny == -1) return 1;
	else return 0;
}

