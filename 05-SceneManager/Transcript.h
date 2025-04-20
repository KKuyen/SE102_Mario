#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#define SPRITE_ID 210000
#define TRANSCRIPT_WIDTH 263
#define TRANSCRIPT_HEIGHT 74

#define NUMBER_0 230000
#define NUMBER_1 230001
#define NUMBER_2 230002
#define NUMBER_3 230003
#define NUMBER_4 230004
#define NUMBER_5 230005
#define NUMBER_6 230006
#define NUMBER_7 230007
#define NUMBER_8 230008
#define NUMBER_9 230009

class CTranscript : public CGameObject {
protected:
	int score;
	int scoreDigits[7];
	int time;
	int timeDigits[3];
	int life;
	int dollar;
	int dollarDigits[2];
	int flag;


public:
	CTranscript(float x, float y) : CGameObject(x, y)
	{
		score = 3000;
		time = 123;
		life = 3;
		dollar = 87;
		flag = 6;
		scoreDigits[0] = score % 10;
		scoreDigits[1] = (score / 10) % 10;
		scoreDigits[2] = (score / 100) % 10;
		scoreDigits[3] = (score / 1000) % 10;
		scoreDigits[4] = (score / 10000) % 10;
		scoreDigits[5] = (score / 100000) % 10;
		scoreDigits[6] = (score / 1000000) % 10;
		timeDigits[0] = time % 10;
		timeDigits[1] = (time / 10) % 10;
		timeDigits[2] = (time / 100) % 10;
		dollarDigits[0] = dollar % 10;
		dollarDigits[1] = (dollar / 10) % 10;

	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	int IsBlocking() { return 0; }
};