﻿#pragma once  
#include "GameObject.h"  
#include "Mario.h"  
#define KOOPAS_GRAVITY 0.0002f  
#define KOOPAS_GRAVITY_FALL 0.001f  
#define KOOPAS_WALKING_SPEED 0.03f  
#define KOOPAS_SHELL_MOVING_SPEED 0.2f  
#define KOOPAS_JUMP_SPEED -0.05f   
#define KOOPAS_FALL_SPEED -0.1f  
#define KOOPAS_FALL_SPEED_HORIZONTAL 0.1f  
#define KOOPAS_BBOX_WIDTH 16  
#define KOOPAS_BBOX_HEIGHT 25  
#define KOOPAS_BBOX_HEIGHT_SHELL 12  


#define KOOPAS_STATE_WALKING 100  
#define KOOPAS_STATE_WALKING_RIGHT 101  
#define KOOPAS_STATE_SHELL 200  
#define KOOPAS_STATE_SHELL_MOVING 300  
#define KOOPAS_STATE_HELD 202  
#define KOOPAS_STATE_FALL 203  
#define KOOPAS_STATE_REVERSE 204  
#define KOOPAS_STATE_JUMP 400

#define ID_ANI_KOOPAS_WALKING 6000  
#define ID_ANI_KOOPAS_WALKING_RIGHT 6003  
#define ID_ANI_KOOPAS_SHELL 6001  
#define ID_ANI_KOOPAS_SHELL_MOVING 6002  
#define ID_ANI_KOOPAS_SHELL_MOVING_REVERSE 6012  
#define ID_ANI_KOOPAS_FALL 6004  
#define ID_ANI_KOOPAS_GREEN_WALKING 7000  
#define ID_ANI_KOOPAS_GREEN_WALKING_RIGHT 7003  
#define ID_ANI_KOOPAS_GREEN_SHELL 7001  
#define ID_ANI_KOOPAS_GREEN_SHELL_MOVING 7002  
#define ID_ANI_KOOPAS_GREEN_SHELL_MOVING_REVERSE 7012  
#define ID_ANI_KOOPAS_GREEN_FALL 7004  
#define KOOPAS_REVIVE_TIME 4000   
#define KOOPAS_COLOR_ORANGE 1
#define KOOPAS_COLOR_GREEN 2
#define KOOPAS_DIE_POS_X 2230
#define KOOPAS_DIE_POS_Y 185
class CKoopas : public CGameObject  
{  
protected:  

   // Thời điểm bắt đầu đếm để hồi sinh  

   virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);  
   virtual void Render();  

   virtual int IsCollidable() {  
       return state != KOOPAS_STATE_HELD && state != KOOPAS_STATE_FALL;  
   }  
   virtual int IsBlocking() { return state == KOOPAS_STATE_SHELL_MOVING; }  

   virtual void OnNoCollision(DWORD dt);  

   virtual void OnCollisionWith(LPCOLLISIONEVENT e);  
   void StartReviveTimer() { revive_start = GetTickCount64(); }  
public:  
    ULONGLONG revive_start;
    float lastShakeOffset; // Track previous shaking offset
    int shakeFrameCounter; // Count frames for toggle-based shaking
   bool isReverse;  
   float ax;  
   float ay;  
   int nx;  
   int color;  
   CMario* mario;  
   CKoopas(float x, float y,int color=1);  
   virtual void SetState(int state);  
   virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};