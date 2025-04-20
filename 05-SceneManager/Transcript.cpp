#include "Transcript.h"
#include "Game.h"
#include "PlayScene.h"

void CTranscript::Render()
{
    float screenWidth = (float)CGame::GetInstance()->GetBackBufferWidth();
    float screenHeight = (float)CGame::GetInstance()->GetBackBufferHeight();
    float camX, camY;
    CGame::GetInstance()->GetCamPos(camX, camY);
    float renderX = x + camX;
    float renderY = y + camY;

    CSprites* s = CSprites::GetInstance();
    LPSPRITE sprite = s->Get(SPRITE_ID);
    if (sprite != nullptr)
    {
        sprite->Draw(renderX, renderY);
    }
    else
    {
        DebugOut(L"[ERROR] Transcript sprite ID %d not found\n", SPRITE_ID);
    }
	//Draw score
     for (int i = 0; i < 7; i++)
    {
        LPSPRITE digitSprite = s->Get(NUMBER_0 + scoreDigits[i]);
        if (digitSprite != nullptr)
        {
            digitSprite->Draw(renderX -63 + i * 8, renderY -3);
        }
        else
        {
            DebugOut(L"[ERROR] Number sprite ID %d not found\n", NUMBER_0 + scoreDigits[i]);
        }
    }
	 //Draw time
     for (int i = 0; i < 3; i++)
    {
        int digitIndex = 2 - i; 
        LPSPRITE digitSprite = s->Get(NUMBER_0 + timeDigits[digitIndex]);
        if (digitSprite != nullptr)
        {
            digitSprite->Draw(renderX +8 + i * 8, renderY -3); 
        }
        else
        {
            DebugOut(L"[ERROR] Number sprite ID %d not found\n", NUMBER_0 + timeDigits[digitIndex]);
        }
    }
	 //Draw life
     LPSPRITE digitSprite = s->Get(NUMBER_0 + life);
     if (digitSprite != nullptr)
     {
         digitSprite->Draw(renderX  -85, renderY - 3);
     }
     else
     {
         DebugOut(L"[ERROR] Number sprite ID %d not found\n", NUMBER_0 +life);
     }
	 //Draw dollar
	 for (int i = 0; i < 2; i++)
	 {
		 int digitIndex = 2 - i;
		 LPSPRITE digitSprite3 = s->Get(NUMBER_0 + dollarDigits[digitIndex]);
		 if (digitSprite3 != nullptr)
		 {
             digitSprite3->Draw(renderX +18 + i * 8, renderY - 11);
		 }
		 else
		 {
			 DebugOut(L"[ERROR] Number sprite ID %d not found\n", NUMBER_0 + dollarDigits[digitIndex]);
		 }
	 }
	 //Draw flag
     for (int i = 0; i < flag; i++)
     {
		 LPSPRITE digitSprite = s->Get(NUMBER_0 + 10);
		 if (digitSprite != nullptr)
		 {
			 digitSprite->Draw(renderX - 63 + i * 8, renderY - 11);
		 }
		 else
		 {
			 DebugOut(L"[ERROR] Number sprite ID %d not found\n", NUMBER_0 + 10);
		 }
     }
     LPSPRITE digitSprite4 = s->Get(NUMBER_0 + 11);
     if (digitSprite4 != nullptr)
     {
         digitSprite4->Draw(renderX - 10, renderY - 11);
     }
     else
     {
         DebugOut(L"[ERROR] Number sprite ID %d not found\n", NUMBER_0 + life);
     }
       
    //RenderBoundingBox();
}

void CTranscript::GetBoundingBox(float& l, float& t, float& r, float& b)
{
    l = x - TRANSCRIPT_WIDTH / 2 + 1;
    t = y - TRANSCRIPT_HEIGHT / 2;
    r = l + TRANSCRIPT_WIDTH - 1;
    b = t + TRANSCRIPT_HEIGHT;
}