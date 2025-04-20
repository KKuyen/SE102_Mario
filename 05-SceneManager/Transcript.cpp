#include "Transcript.h"
#include "Game.h"

void CTranscript::Render()
{
 	float screenWidth = (float)CGame::GetInstance()->GetBackBufferWidth();
	float screenHeight = (float)CGame::GetInstance()->GetBackBufferHeight();
 	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);
  	float renderX = x + camX;
	float renderY = y + camY;

	CSprites* s = CSprites::GetInstance();
	s->Get(SPRITE_ID)->Draw(renderX, renderY);

	//RenderBoundingBox();
}

void CTranscript::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x -  TRANSCRIPT_WIDTH / 2 + 1;
	t = y -  TRANSCRIPT_HEIGHT / 2;
	r = l +  TRANSCRIPT_WIDTH - 1;
	b = t +  TRANSCRIPT_HEIGHT;
}
