#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "PlayScene.h"
#include "NumberText.h"
#define ENEGY_BLACK_SPRITE 230010
#define ENEGY_WHITE_SPRITE 230014
#define NUMBER_BASE_SPRITE 230000
#define TIMER_CHARACTERS_LENGTH 3
#define COINS_CHARACTERS_LENGTH 2
#define POINTS_CHARACTERS_LENGTH 7
#define LIFES_CHARACTERS_LENGTH 2
#define ENERGY_CHARACTERS_LENGTH 6

class CTranscript : public CGameObject {
protected:
	int width;
	int height;
	int spriteId;
	float posX;
	float posY;
	vector<LPGAMEOBJECT> timer;
	vector<LPGAMEOBJECT> coins;
	vector<LPGAMEOBJECT> points;
	vector<LPGAMEOBJECT> lifes;
	vector<LPGAMEOBJECT> energy;
	CNumberText* PMeter;
	bool isInitUI;
public:
    CTranscript(float x, float y, int widthh, int heightt, int sipriteIdd) : CGameObject(x, y)
    {
       this->width = widthh;
       this->height = heightt;
       this->spriteId = sipriteIdd;
       posX = posY = 0;
       isInitUI = false;
    }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsCollidable() { return 0; }
	int IsBlocking() { return 0; }
	void InitUI();
	void SetPosition(float x, float y);
	void UpdateElements(vector<LPGAMEOBJECT>& elements, DWORD value);
	void UpdateEnergy(vector<LPGAMEOBJECT>& energy, int value);
};