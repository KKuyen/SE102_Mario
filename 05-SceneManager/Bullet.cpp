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
	float angle = atan2(deltaY, deltaX) * CONST180 / M_PI;
	float angleFire;

	if (angle >= -ANGLE_90 && angle <= -ANGLE_10)
	{
		angleFire = -ANGLE_45;
	}
	else if (angle > -ANGLE_10 && angle <= 0) 
	{
		angleFire = -ANGLE_20;
	}
	else if (angle > 0 && angle <= ANGLE_30) 
	{
		angleFire = ANGLE_20;
	}
	else if (angle > ANGLE_30 && angle <= ANGLE_90) 
	{
		angleFire = ANGLE_45;
	}
	else if (angle > ANGLE_90 && angle <= ANGLE_160) 
	{
		angleFire = ANGLE_135;
	}
	else if (angle > ANGLE_160 && angle <= ANGLE_180) 
	{
		angleFire = ANGLE_160;
	}
	else if (angle > -ANGLE_180 && angle <= -ANGLE_145) 
	{
		angleFire = -ANGLE_160;
	}
	else
	{
		angleFire = -ANGLE_135;
	}

	vx = BULLET_V * cos(angleFire * M_PI / CONST180);
	vy = -BULLET_V * sin(angleFire * M_PI / CONST180);
}