#include "Bullet.h"
#include <cmath>

#define M_PI 3.14159265358979323846

void CBullet::Render() {
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_BULLET)->Render(x, y);
 
}

void CBullet::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - BULLET_BBOX_WIDTH / 2 + 1;
	t = y - BULLET_BBOX_HEIGHT / 2;
	r = l + BULLET_BBOX_WIDTH - 1;
	b = t + BULLET_BBOX_HEIGHT;
}

void CBullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	x += vx * dt;
	y += vy * dt;
	if (GetTickCount64() - fire_start > BULLET_TIMEOUT) {
		this->Delete();
	}

	CGameObject::Update(dt, coObjects);
	//CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBullet::SetUpAngle(float marioX, float marioY)
{
	float deltaX = marioX - x;
	float deltaY = -(marioY - y);
	float angle = atan2(deltaY, deltaX) * 180.0f / M_PI;
	float angleFire;

	if (angle >= -90 && angle <= -10) // 1
	{
		angleFire = -45;
	}
	else if (angle > -10 && angle <= 0) // 2
	{
		angleFire = -20;
	}
	else if (angle > 0 && angle <= 30) //3
	{
		angleFire = 20;
	}
	else if (angle > 30 && angle <= 90) //4
	{
		angleFire = 45;
	}
	else if (angle > 90 && angle <= 160) //5
	{
		angleFire = 135;
	}
	else if (angle > 160 && angle <= 180) //6
	{
		angleFire = 160;
	}
	else if (angle > -180 && angle <= -145) //7
	{
		angleFire = -160;
	}
	else // 8
	{
		angleFire = -135;
	}

	vx = BULLET_V * cos(angleFire * M_PI / 180.0f);
	vy = -BULLET_V * sin(angleFire * M_PI / 180.0f);
}