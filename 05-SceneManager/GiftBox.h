#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mario.h"
#define BOX_WIDTH 16
#define BOX_BBOX_WIDTH 16
#define BOX_BBOX_HEIGHT 16
#define GIFTBOX_STATE_SHOWING 100
#define GIFTBOX_STATE_BOUNCE 200
#define GIFTBOX_STATE_HIDDEN 300
#define GIFTBOX_GRAVITY	0.002f
#define GIFTBOX_BOUNCE_SPEED 0.2f
#define SPRITE_ID_HIDDEN 90004



#include "Mario.h" // Ensure CMario is declared before usage

class CGiftBox : public CGameObject {
protected:
   int animationId;
   int initY;
   int type; 
   int isBoxHidden;
   CMario* mario;
public:

   CGiftBox(float x, float y, int animationId, int type);
   void Render();
   void Open(CMario* mario);
   //void Open( );
   void OpenCoinBox();
   void OpenMushroomBox(CMario* mario);
   void OpenLeafBox();
   void OpenGreenMushroomBox(CMario* mario);
   void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
   void GetBoundingBox(float& l, float& t, float& r, float& b);

};