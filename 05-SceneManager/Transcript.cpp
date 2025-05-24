#include "Transcript.h"
#include "PlayScene.h"
#include "debug.h"
#include "GameManager.h"
#include "NumberText.h"

void CTranscript::Render()
{
	CSprites* s = CSprites::GetInstance();
	CSprite* sprite = s->Get(this->spriteId);
 	sprite->Draw(x, y);
	 
}

void CTranscript::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - this->width / 2 + 1;
	t = y - this->height / 2 + 1;
	r = l + this->width;
	b = t + this->height;
}


void CTranscript::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isInitUI)
	{
		this->InitUI();
	}
	else {
		UpdateElements(timer, CGameManager::GetInstance()->timer);
		UpdateElements(coins, CGameManager::GetInstance()->coins);
		UpdateElements(points, CGameManager::GetInstance()->points);
		UpdateElements(lifes, CGameManager::GetInstance()->lifes);
	}
	CGameObject::Update(dt, coObjects);
}

void CTranscript::InitUI()
{
	isInitUI = true;
	LPSCENE s = CGame::GetInstance()->GetCurrentScene();
	CPlayScene* p = dynamic_cast<CPlayScene*>(s);
	for (int i = 0; i < 3; i++)
	{
		LPGAMEOBJECT numtext = new CNumberText(x, y, false);
		p->PushBackGameObject(numtext);
		timer.push_back(numtext);
	}
	for (int i = 0; i < 2; i++)
	{
		LPGAMEOBJECT numtext = new CNumberText(x, y, false);
		p->PushBackGameObject(numtext);
		coins.push_back(numtext);
	}
	for (int i = 0; i < 7; i++)
	{
		LPGAMEOBJECT numtext = new CNumberText(x, y, false);
		p->PushBackGameObject(numtext);
		points.push_back(numtext);
	}
	for (int i = 0; i < 2; i++)
	{
		LPGAMEOBJECT numtext = new CNumberText(x, y, false);
		p->PushBackGameObject(numtext);
		lifes.push_back(numtext);
	}
	for (int i = 0; i < 6; i++)
	{
		LPGAMEOBJECT numtext = new CNumberText(x, y, false);
		CNumberText* temp = dynamic_cast<CNumberText*>(numtext);
		temp->SetIdSprite(230010);
		p->PushBackGameObject(numtext);
		energy.push_back(numtext);
	}
	LPGAMEOBJECT numtext = new CNumberText(x, y, true);
	CNumberText* temp = dynamic_cast<CNumberText*>(numtext);
 	p->PushBackGameObject(numtext);
	PMeter = numtext;
}

void CTranscript::SetPosition(float x, float y)
{
	this->x = x;
	this->y = y;
	if (PMeter != nullptr)
	{
		PMeter->SetPosition(x-12, y - 12);
	}
	if (timer.size() > 0)
	{
		for (int i = 0; i < timer.size(); i++)
		{
			timer[i]->SetPosition(x + i * 8 + 10, y - 4);
		}
	}
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i]->SetPosition(x + i * 8 + 18, y - 12);
	}
	for (int i = 0; i < points.size(); i++)
	{
		points[i]->SetPosition(x + i * 8 - 64, y - 4);
	}
	for (int i = 0; i < lifes.size(); i++)
	{
		lifes[i]->SetPosition(x + i * 8 - 86, y - 4);
	}
	for (int i = 0; i < energy.size(); i++)
	{
		energy[i]->SetPosition(x + i * 8 - 64, y - 12);
	}
}

void CTranscript::UpdateElements(vector<LPGAMEOBJECT>& elements, DWORD value)
{
	std::string valueStr = std::to_string(value);
	while (valueStr.length() < elements.size())
	{
		valueStr = "0" + valueStr;
	}

	int index = elements.size() - 1;
	for (int i = valueStr.length() - 1; i >= 0 && index >= 0; --i, --index)
	{
		int digit = valueStr[i] - '0';
		dynamic_cast<CNumberText*>(elements[index])->SetIdSprite(230000 + digit);
	}
}