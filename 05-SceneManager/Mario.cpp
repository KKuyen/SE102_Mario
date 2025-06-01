#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"

#include "Collision.h"
#include "Koopas.h"
#include "WIngedGoomba.h"
#include "GiftBox.h"
#include "Mushroom.h"
#include "Bullet.h"
#include "Flower.h"
#include "PlayScene.h"
#include "EffectGiftBoxCoin.h"
#include "EffectPoint.h"
#include "Leaf.h"
#include "EffectSmoke.h"
#include "Chimney.h"
#include "WingedKoopas.h"
#include "PiranhaPlant.h"
#include "HiddenButton.h"
#include "Button.h"
#include "BreakableBrick.h"
#include "ExplodeAni.h"
#include "MovablePlatform.h"
#include "BomerangBro.h"
#include "Bomerang.h"
#include "CoinBrick.h"
#include "GreenMushroom.h"
#include "GameManager.h"
#include "WingedRedKoopa.h"
#include "BlackGiftBox.h"
#include "SampleKeyEventHandler.h"

#define RENDER_POINT_1  704
#define RENDER_POINT_2  736
#define RENDER_POINT_3  816
#define RENDER_POSITION_Y 150
#define RENDER_POSITION_Y2 130
#define RENDER_POSITION_X1 855
#define RENDER_POSITION_X2 925
#define RENDER_POSITION_X3 995
#define CHIMMNEY_1_POSITION_X 2265
#define CHIMMNEY_2_POSITION_X 2326
#define CHIMMNEY_14_POSITION_X 1952
#define BOMERANG_BRO_RENDER_POS 2200
#define BOMERANG_BRO_X 2105
#define BOMERANG_BRO_Y 122



void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    if (level == MARIO_LEVEL_MAX && whip_start != 0 && GetTickCount64() - whip_start <= MARIO_WHIP_TIME)
    {
        float mx, my;
        GetPosition(mx, my);

        // Define the search range (16px in x and y)
        float range = BREAKABLE_BRICK_BBOX_WIDTH;
        float checkLeft, checkRight, checkTop, checkBottom;

        // Determine the direction Mario is facing
        if (nx > 0) // Facing right
        {
            checkLeft = mx;
            checkRight = mx + MARIO_BIG_BBOX_WIDTH / 2 + range;
        }
        else // Facing left
        {
            checkLeft = mx - MARIO_BIG_BBOX_WIDTH / 2 - range;
            checkRight = mx;
        }
        checkTop = my - MARIO_BIG_BBOX_HEIGHT / 2 - range;
        checkBottom = my + MARIO_BIG_BBOX_HEIGHT / 2 + range;

        // Check for breakable bricks in the specified range
        for (size_t i = 0; i < coObjects->size(); i++)
        {
            LPGAMEOBJECT obj = coObjects->at(i);
            if (dynamic_cast<CBreakableBrick*>(obj)) // Assuming CBreakableBrick is the class
            {
                float bl, bt, br, bb;
                obj->GetBoundingBox(bl, bt, br, bb);

                // Check if the brick is within the 16px range
                if (bl < checkRight && br > checkLeft && bt < checkBottom && bb > checkTop && IsInWhipRegion(obj))
                {
                    obj->SetState(BREAKABLE_BRICK_STATE_BREAK);
                }
            }
        }
    }
  
    if (isFlying && GetTickCount64() - fly_timer > MARIO_MAX_FLY_ACTIVATION_TIME && fly_timer!=0)
    {
        isFlying = false;
        fly_timer = 0;
    }

    if (isWon && isOnPlatform)
    {
        vx = 0.08f; // tốc độ chạy liên tục
        x += vx * dt;
        winDistance += vx * dt;
        if (winDistance >= 140)
            isWon = false;
        if (x > 2815)
            CGame::GetInstance()->InitiateSwitchScene(2);
        return;
    }
    if (!isOnPlatform)
    {
        run_start = 0;
    }
    if (teleport_start_out != -1 && GetTickCount64() - teleport_start_out <= MARIO_TELEPORT_DURATION)

    {

       
        if (CGame::GetInstance()->GetCurrentScene()->GetId() == 1)
        {
            if (x <= CHIMMNEY_1_POSITION_X - MARIO_TELEPORT_IN_POSITION_X_MOVE + 10)
            {
                x = CHIMMNEY_1_POSITION_X - MARIO_TELEPORT_IN_POSITION_X_MOVE;
                y += 0.65;
                return;
            }
            else
            {
                y -= 0.6511;

                return;

            }
        }
        else 
        {

          
          
                
            
                y -= 0.6511;
                return;

        }
      
    }
    if (vx == 0 && (state == MARIO_STATE_RUNNING_RIGHT || state == MARIO_STATE_RUNNING_LEFT))
    {
        isFlying = false;
        fly_timer = 0;
        run_start = 0;

    }

        CScene* currentScene = CGame::GetInstance()->GetCurrentScene();
        if (currentScene->GetId() == 1) {



            if (x > RENDER_POINT_1 && renderedGoombaNum == 0)
            {
                LPGAMEOBJECT goomba = new CGoomba(RENDER_POSITION_X1, RENDER_POSITION_Y);

                LPSCENE s = CGame::GetInstance()->GetCurrentScene();
                LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
                p->AddGameObject(goomba);
                renderedGoombaNum = 1;
            }
            if (x > RENDER_POINT_2 && renderedGoombaNum == 1)
            {
                LPGAMEOBJECT goomba = new CGoomba(RENDER_POSITION_X2, RENDER_POSITION_Y);

                LPSCENE s = CGame::GetInstance()->GetCurrentScene();
                LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
                p->AddGameObject(goomba);
                renderedGoombaNum = 2;
            }
            if (x > RENDER_POINT_3 && renderedGoombaNum == 2)
            {
                LPGAMEOBJECT goomba = new CWingedGoomba(RENDER_POSITION_X3, RENDER_POSITION_Y);

                LPSCENE s = CGame::GetInstance()->GetCurrentScene();
                LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
                p->AddGameObject(goomba);
                renderedGoombaNum = 3;
            }

        }
        else {
            if (x >= BOMERANG_BRO_RENDER_POS && isBomerangBroRendered == false)
            {
                CBomerangBro* bomerang_bro = new CBomerangBro(BOMERANG_BRO_X, BOMERANG_BRO_Y);

                LPSCENE s = CGame::GetInstance()->GetCurrentScene();
                LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
                p->AddGameObject(bomerang_bro);
                bomerang_bro->SetMario(this);
                isBomerangBroRendered = true;

            }

        }

        if (teleport != 0)
        {
            if (teleport == MARIO_TELEPORT_IN && GetTickCount64() - teleport_start > MARIO_TELEPORT_DURATION && teleport_start != -1)
            {


                if (CGame::GetInstance()->GetCurrentScene()->GetId() == 1)
                {
                    x = x - MARIO_TELEPORT_IN_POSITION_X_MOVE;
                    y = MARIO_TELEPORT_IN_POSITION_Y;

                }
                else
                {
                    x = x + MARIO_TELEPORT_IN_POSITION_X_MOVE + 92;
                    y += 44;

                }
                teleport = MARIO_TELEPORT_NONE;
                teleportState = 1;
                SetState(MARIO_STATE_WALKING_RIGHT);
                teleport_start = -1;

                teleport_start_out = GetTickCount64();
               

            }
            else if (teleport == MARIO_TELEPORT_OUT && GetTickCount64() - teleport_start > MARIO_TELEPORT_DURATION && teleport_start != -1)
            {
                y = MARIO_TELEPORT_OUT_POSITION_Y;
                DebugOut(L"[TELEPORT OUTTTTTTTTTTTTTTTTTTTTTTTTTTTT]");

                teleport = MARIO_TELEPORT_NONE;
                teleportState = 0;
                SetState(MARIO_STATE_WALKING_RIGHT);
                teleport_start = -1;
               
                teleport_start_out = GetTickCount64();
              
            }
            else
            {
                if (teleport == MARIO_TELEPORT_IN)
                {
                    if (CGame::GetInstance()->GetCurrentScene()->GetId() == 1)
                    {

                        x = CHIMMNEY_1_POSITION_X;

                    }
                    else
                    {
                        x = CHIMMNEY_14_POSITION_X;
                    }
                    y = y + 0.65;
                    return;
                }
                else
                {
                    x = CHIMMNEY_2_POSITION_X;
                    y = y - 0.65;
                    return;

                }
            }

        }
        if (isOnPlatform)
        {
            isSlowFalling = false;
            slow_fall_start = 0;
        }
      
        if (level == MARIO_LEVEL_MAX && vy > 0 && isSlowFalling)
        {
            // Kiểm tra thời gian kìm tối đa
            if (GetTickCount64() - slow_fall_start > MARIO_SLOW_FALL_MAX_TIME)
            {
                isSlowFalling = false;
                ay = MARIO_GRAVITY; // Trở lại trọng lực bình thường
            }
            else
            {
                // Áp dụng tốc độ rơi chậm và trọng lực nhỏ
                if (vy > MARIO_SLOW_FALL_SPEED_Y)
                    vy = MARIO_SLOW_FALL_SPEED_Y;
                ay = MARIO_SLOW_FALL_GRAVITY;
            }
        }
        if (level == MARIO_LEVEL_MAX && isFlying)
        {
            ay = MARIO_GRAVITY_FLY;
        }
        else if (!isSlowFalling && vy > 0)
        {
            // Nếu không kìm, sử dụng trọng lực bình thường
            ay = MARIO_GRAVITY;
        }
    
        vy += ay * dt;
        vx += ax * dt;

        if (abs(vx) > abs(maxVx)) vx = maxVx;

        if (!isOnPlatform)
        {
            beforeLand = true;
        }
        if (isOnPlatform && beforeLand)
        {
            isFlying = false;
            fly_timer = 0;
            run_start = 0;
            beforeLand = false;
        }
        if (state == MARIO_STATE_SLIP_RIGHT)
        {
            if (vx <= 0)
            {
                SetState(MARIO_STATE_IDLE);
            }
        }
        if (state == MARIO_STATE_SLIP_LEFT)
        {
            if (vx >= 0)
            {
                SetState(MARIO_STATE_IDLE);
            }
        }
        // Kiểm tra thời gian giữ nút chạy để kích hoạt bay
                 if (GetTickCount64() - run_start >= MARIO_FLY_ACTIVATION_TIME&& run_start != 0)
            {
                isFlying = true;
            }
       
        // reset untouchable timer if untouchable time has passed
        if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
        {
            untouchable_start = 0;
            untouchable = 0;
        }
        // Update held object position

        if (heldObject != NULL)
        {
            float mx, my;
            GetPosition(mx, my);
            const DWORD SHAKE_TIME = 500; // 0.5 seconds
            ULONGLONG elapsedHoldTime = GetTickCount64() - hold_start;
            float shakeOffset = 0.0f;

            // Calculate shaking offset if in shaking window
            if (elapsedHoldTime >= KOOPAS_REVIVE_TIME - SHAKE_TIME && elapsedHoldTime < KOOPAS_REVIVE_TIME)
            {
                shakeFrameCounter++;
                shakeOffset = (shakeFrameCounter % 10 < 5) ? 1.0f : -1.0f; // Toggle ±1 every 5 frames
                DebugOut(L"[DEBUG] Held Koopas shaking, offset=%.2f, frame=%d\n", shakeOffset, shakeFrameCounter);
            }
            else
            {
                shakeOffset = 0.0f; // No shaking outside window
            }

            if (dynamic_cast<CKoopas*>(heldObject))
            {
                CKoopas* koopas = dynamic_cast<CKoopas*>(heldObject);
                if (elapsedHoldTime >= KOOPAS_REVIVE_TIME)
                {
                    koopas->SetVy(KOOPAS_JUMP_SPEED);
                    koopas->ay = KOOPAS_GRAVITY;
                    koopas->nx = nx;
                    koopas->SetState(KOOPAS_STATE_WALKING);
                    SetHolding(false, nullptr);
                   
                    shakeFrameCounter = 0; // Reset shaking
                    lastShakeOffset = 0;
                    if (level > MARIO_LEVEL_SMALL)
                    {
                        level = level - 1;
                        StartUntouchable();
                    }
                    else
                    {
                        DebugOut(L">>> Mario DIE >>> \n");
                        SetState(MARIO_STATE_DIE);
                    }
                }
                else
                {
                    float baseX = mx + (nx > 0 ? MARIO_BIG_BBOX_WIDTH / 2 + KOOPAS_BBOX_WIDTH / 2 : -MARIO_BIG_BBOX_WIDTH / 2 - KOOPAS_BBOX_WIDTH / 2);
                    float baseY = my;
                    heldObject->SetPosition(baseX, baseY + shakeOffset - lastShakeOffset);
                    lastShakeOffset = shakeOffset;
                }
            }
            else if (dynamic_cast<CWingedKoopas*>(heldObject))
            {
                CWingedKoopas* koopas = dynamic_cast<CWingedKoopas*>(heldObject);
                if (elapsedHoldTime >= KOOPAS_REVIVE_TIME)
                {
                    SetHolding(false, nullptr);
                    koopas->SetVy(WINGED_KOOPAS_JUMP_SPEED);
                    koopas->ay = WINGED_KOOPAS_GRAVITY;
                    koopas->nx = nx;
                    koopas->SetState(WINGED_KOOPAS_STATE_WALKING);
                  
               
                    shakeFrameCounter = 0; // Reset shaking
                    lastShakeOffset = 0;
                    if (level > MARIO_LEVEL_SMALL)
                    {
                        level = level - 1;
                        StartUntouchable();
                    }
                    else
                    {
                        DebugOut(L">>> Mario DIE >>> \n");
                        SetState(MARIO_STATE_DIE);
                    }
                }
                else
                {
                    float baseX = mx + (nx > 0 ? MARIO_BIG_BBOX_WIDTH / 2 + KOOPAS_BBOX_WIDTH / 2 : -MARIO_BIG_BBOX_WIDTH / 2 - KOOPAS_BBOX_WIDTH / 2);
                    float baseY = my;
                    heldObject->SetPosition(baseX+shakeOffset, baseY  - lastShakeOffset);
                    lastShakeOffset = shakeOffset;
                }
            }
        }

        // Kiểm tra thời gian chờ để biến thành Mario chồn
        if (isWaitingForLevelUp && GetTickCount() - timeWaitingStart >= 400)
        {
            SetLevel(MARIO_LEVEL_MAX);
            isVisible = true;
            isWaitingForLevelUp = false;
        }
        // Không cập nhật vị trí nếu Mario đang hóa chồn
        if (!isVisible)
        {
            vx = 0;
            vy = 0;
            x = saved_x;
            y = saved_y;
            return;
        }
        //isOnPlatform = false;
        CCollision::GetInstance()->Process(this, dt, coObjects);

        // --- ENERGY SYSTEM ---
        int runningState = (state == MARIO_STATE_RUNNING_LEFT || state == MARIO_STATE_RUNNING_RIGHT);
        int& energy = CGameManager::GetInstance()->energy;
        ULONGLONG now = GetTickCount64();
        const int ENERGY_MAX = 6;
        const DWORD ENERGY_INTERVAL = 200;

        if (lastEnergyUpdate == 0) lastEnergyUpdate = now;

        if (runningState)
        {
            if (energy < ENERGY_MAX && now - lastEnergyUpdate >= ENERGY_INTERVAL)
            {
                energy++;
                if (energy > ENERGY_MAX) energy = ENERGY_MAX;
                lastEnergyUpdate = now;
            }
        }
        else
        {
            if (energy > 0 && now - lastEnergyUpdate >= ENERGY_INTERVAL)
            {
                energy--;
                if (energy < 0) energy = 0;
                lastEnergyUpdate = now;
            }
        }

    }

void CMario::OnNoCollision(DWORD dt)
{
    x += vx * dt;
  
    if (!onMovable)
    {

        y += vy * dt;
        isOnPlatform = false;
    }
    }
 


int CMario::GetDirection()
{
    if (vx > 0)
    {
        return 1;
    }
    else
        return 0;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
    if (!dynamic_cast<CMovablePlatform*>(e->obj))
    if (e->ny != 0 && e->obj->IsBlocking())
    {
        vy = 0;
        if (e->ny < 0) {
            isOnPlatform = true;
        }
    }
    else if (e->nx != 0 && e->obj->IsBlocking())
    {
        vx = 0;
    }
	if (!dynamic_cast<CMovablePlatform*>(e->obj))
	{
        onMovable = false;
	}

    if (dynamic_cast<CGoomba*>(e->obj))
        OnCollisionWithGoomba(e);
    else if (dynamic_cast<CCoin*>(e->obj))
        OnCollisionWithCoin(e);
    else if (dynamic_cast<CPortal*>(e->obj))
        OnCollisionWithPortal(e);
    else if (dynamic_cast<CKoopas*>(e->obj))
        OnCollisionWithKooPas(e);
    else if (dynamic_cast<CWingedGoomba*>(e->obj))
        OnCollisionWithWingedGoomba(e);
    else if (dynamic_cast<CGiftBox*>(e->obj))
        OnCollisionWithGiftBox(e);
    else if (dynamic_cast<CCoinBrick*>(e->obj))
        OnCollisionWithCoinBrick(e);
    else if (dynamic_cast<CMushroom*>(e->obj))
        OnCollisionWithMushroom(e);
    else if (dynamic_cast<CBullet*>(e->obj))
        OnCollisionWithBullet(e);
    else if (dynamic_cast<CFlower*>(e->obj))
        OnCollisionWithFlower(e);
    else if (dynamic_cast<CLeaf*>(e->obj))
        OnCollisionWithLeaf(e);
    else if (dynamic_cast<CChimney*>(e->obj))
        OnCollisionWithChimney(e);
    else if (dynamic_cast<CWingedKoopas*>(e->obj))
        OnCollisionWithWingedKoopas(e);
    else if (dynamic_cast<CPiranhaPlant*>(e->obj))
        OnCollisionWithCPiranhaPlant(e);
    else if (dynamic_cast<CHiddenButton*>(e->obj))
        OnCollisionWithCHiddenButton(e);
    else if (dynamic_cast<CButton*>(e->obj))
        OnCollisionWithButton(e);
    else if (dynamic_cast<CBreakableBrick*>(e->obj))
        OnCollisionWithBreakableBrick(e);
    else if (dynamic_cast<CMovablePlatform*>(e->obj))
        OnCollisionWithCMovablePlatform(e);
    else if (dynamic_cast<CBomerangBro*>(e->obj))
        OnCollisionWithBomerangBro(e);
    else if (dynamic_cast<CBoomerang*>(e->obj))
        OnCollisionWithBomerang(e);
     else if (dynamic_cast<CGreenMushroom*>(e->obj))
    OnCollisionWithGreenMushroom(e);
    else if (dynamic_cast<CWingedRedKoopa*>(e->obj))
        OnCollisionWithWingedRedKoopa(e);
	else if (dynamic_cast<CBlackGiftBox*>(e->obj))
		OnCollisionWithBlackGiftBox(e);
 }
void CMario::OnCollisionWithGreenMushroom(LPCOLLISIONEVENT e) {
    CGreenMushroom* mushroom = dynamic_cast<CGreenMushroom*>(e->obj);
    mushroom->SetState(GREEN_MUSHROOM_STATE_EATEN);
    LPGAMEOBJECT effectPoint = new CEffectPoint(x, y, 1);
    LPSCENE s = CGame::GetInstance()->GetCurrentScene();
    LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
    p->PushBackGameObject(effectPoint);
}
void CMario::OnCollisionWithBlackGiftBox(LPCOLLISIONEVENT e) {
    CBlackGiftBox* m = dynamic_cast<CBlackGiftBox*>(e->obj);
   
     if(isOpenBlackBox==false)
     {
         m->OpenGiftBox();
		 isWon = true;
         isOpenBlackBox = true;
     }
}

void CMario::OnCollisionWithWingedRedKoopa(LPCOLLISIONEVENT e)
{
    CWingedRedKoopa* koopas = dynamic_cast<CWingedRedKoopa*>(e->obj);
    koopas->mario = this;

    // jump on top >> kill Goomba and deflect a bit 
    if (e->ny < 0)
    {
        if (koopas->GetState() != KOOPAS_STATE_SHELL && koopas->GetState() != KOOPAS_STATE_SHELL_MOVING)
        {
            koopas->SetState(KOOPAS_STATE_WALKING);
            vy = -MARIO_JUMP_DEFLECT_SPEED;
            LPGAMEOBJECT effectPoint = new CEffectPoint(x, y, 100);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->AddGameObject(effectPoint);

        }

    }

    else
    {
        if (untouchable == 0)
        {
            if (koopas->GetState() == KOOPAS_STATE_FALL)
                return;
            if (koopas->GetState() != KOOPAS_STATE_SHELL && koopas->GetState() != KOOPAS_STATE_HELD)
            {
                if (level > MARIO_LEVEL_SMALL)
                {

                    level = level - 1;
                    StartUntouchable();
                }
                else
                {
                    DebugOut(L">>> Mario DIE >>> \n");
                    SetState(MARIO_STATE_DIE);

                }
            }
            else
            {

                CGame* game = CGame::GetInstance();
                if (game->IsKeyDown(DIK_A)) // Run key
                {
                    
                    hold_start = GetTickCount64();
                    SetHolding(true, koopas);
                    koopas->SetState(KOOPAS_STATE_HELD);
                }
                else
                {
                    koopas->nx = this->nx;
                    koopas->SetState(KOOPAS_STATE_SHELL_MOVING);
                }


            }
        }
    }
}
bool CMario::IsInWhipRegion(CGameObject* obj)
{
    // Get Mario's bounding box
    float ml, mt, mr, mb;
    GetBoundingBox(ml, mt, mr, mb);

    // Calculate whip region (bottom half)
    float marioHeight = mb - mt;
    float halfHeight = marioHeight * 1.0f / 2.0f;
    float whipTop = mb - halfHeight; // Top of the whip region

    // Get object's bounding box
    float l, t, r, b;
    obj->GetBoundingBox(l, t, r, b);

    // Check if object's vertical range overlaps with Mario's whip region
    bool isOverlapping = (t <= mb && b >= whipTop);

    DebugOut(L"[DEBUG] Checking whip region for obj at (%.1f, %.1f), t=%.1f, b=%.1f, whip region: %.1f to %.1f, overlap=%d\n",
        obj->x, obj->y, t, b, whipTop, mb, isOverlapping);

    return isOverlapping;
}

void CMario::OnCollisionWithBreakableBrick(LPCOLLISIONEVENT e)
{
    CBreakableBrick* brick = dynamic_cast<CBreakableBrick*>(e->obj);
    if (brick->state == BREAKABLE_BRICK_STATE_NORMAL)
    {
       
        if ((level == MARIO_LEVEL_MAX && whip_start != 0 && GetTickCount64() - whip_start <= MARIO_WHIP_TIME && e->nx != 0))
        {
            if (IsInWhipRegion(brick))
            {

                brick->SetState(BREAKABLE_BRICK_STATE_BREAK);
            }
        }
        else if (e->ny > 0)
        {
            if (level == MARIO_LEVEL_SMALL)
                brick->SetState(BREAKABLE_BRICK_STATE_MOVE);
            else
                brick->SetState(BREAKABLE_BRICK_STATE_BREAK);
        

        }
    }
    else if (brick->state == BREAKABLE_BRICK_STATE_COIN)
    {
        brick->SetState(BREAKABLE_BRICK_STATE_INVISIBLE);
    }
}

void CMario::OnCollisionWithButton(LPCOLLISIONEVENT e)
{
    CButton* button = dynamic_cast<CButton*>(e->obj);
    if (!button->isPressed && e->ny < 0) // Mario jumps on top of the button
    {
        button->isPressed = true;
        vy = -MARIO_JUMP_DEFLECT_SPEED; // Deflect Mario upward
        button->y = button->y + 5;
        CPlayScene* currentScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
        if (currentScene)
        {
            vector<LPGAMEOBJECT>& objects = currentScene->GetObjects();
            for (size_t i = 0; i < objects.size(); i++)
            {
                if (dynamic_cast<CBreakableBrick*>(objects[i]))
                {
                    CBreakableBrick* brick = dynamic_cast<CBreakableBrick*>(objects[i]);
                 
                        brick->SetState(BREAKABLE_BRICK_STATE_COIN);
                        
                  
                }
            }
        }
    }
}

void CMario::OnCollisionWithCHiddenButton(LPCOLLISIONEVENT e)
{
    CHiddenButton* hiddenbutton = dynamic_cast<CHiddenButton*>(e->obj);
    if ((e->ny > 0 || (level == MARIO_LEVEL_MAX && whip_start != 0 && GetTickCount64() - whip_start <= MARIO_WHIP_TIME)) && hiddenbutton->isActivated == false)
    {
        hiddenbutton->isActivated = true;
        float bx, by;
        hiddenbutton->GetPosition(bx, by);
        float buttonX = bx;
        float buttonY = by - 16.0f;
        if (hiddenbutton->type == HIDDEN_BUTTON_TYPE_BUTTON)
        {
            CButton* button = new CButton(buttonX, buttonY);
            CExplodeAni* explode = new CExplodeAni(buttonX, buttonY);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            if (p) p->AddGameObject(explode);
            if (p) p->AddGameObject(button);
        }
        if (hiddenbutton->type == HIDDEN_BUTTON_TYPE_GIFT_BOX_LEAF)
        {
            CGiftBox* giftbox = new CGiftBox(bx, by, 91000, 2);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            if (p) p->AddGameObject(giftbox);
            giftbox->Open(this);
        }
        if (hiddenbutton->type == HIDDEN_BUTTON_TYPE_GIFT_BOX_GREEN_MUSHROOM)
        {
            CGiftBox* giftbox = new CGiftBox(bx, by, 91000, 3);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            if (p) p->AddGameObject(giftbox);
            giftbox->Open(this);
        }
    }
}

void CMario::OnCollisionWithCPiranhaPlant(LPCOLLISIONEVENT e)
{
    CPiranhaPlant* piranhaplant = dynamic_cast<CPiranhaPlant*>(e->obj);
    if (untouchable == 0)
    {
        if (level == MARIO_LEVEL_MAX && whip_start != 0 && GetTickCount64() - whip_start <= MARIO_WHIP_TIME && e->nx != 0)
        {
            float x, y;
            piranhaplant->GetPosition(x, y);
            CExplodeAni* exp = new CExplodeAni(x, y);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->AddGameObject(exp);
            piranhaplant->Delete();
        }
        else if (level > MARIO_LEVEL_SMALL)
        {
            StartUntouchable();
            level = level - 1;
        }
        else
        {
            DebugOut(L">>> Mario DIE >>> \n");
            SetState(MARIO_STATE_DIE);
        }
    }
}

void CMario::OnCollisionWithCMovablePlatform(LPCOLLISIONEVENT e)
{
    if (e->ny > 0)
    {
        return;
    }
    onMovable = true;
    CMovablePlatform* movablePlatform = dynamic_cast<CMovablePlatform*>(e->obj);
    if (e->ny < 0) {
        // Mario đứng trên platform, luôn cho phép nhảy kể cả khi platform rơi
        isOnPlatform = true;
        // Mario sẽ bám vận tốc rơi của platform
        y = movablePlatform->y;
        movablePlatform->Falling();
    }
}

void CMario::OnCollisionWithBomerang(LPCOLLISIONEVENT e)
{
    if (untouchable == 0)
    {
        if (level > MARIO_LEVEL_SMALL)
        {
            level = level - 1;
            StartUntouchable();
        }
        else
        {
            SetState(MARIO_STATE_DIE);
        }
    }
}

void CMario::OnCollisionWithBomerangBro(LPCOLLISIONEVENT e)
{
    CBomerangBro* bomerangBro = dynamic_cast<CBomerangBro*>(e->obj);
    if (e->ny < 0)
    {
        if (bomerangBro->GetState() != BOMERANG_BRO_STATE_FALL)
        {
            bomerangBro->SetState(BOMERANG_BRO_STATE_FALL);
            vy = -MARIO_JUMP_DEFLECT_SPEED;
            LPGAMEOBJECT effectPoint = new CEffectPoint(x, y, 1000);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->PushBackGameObject(effectPoint);
        }
    }
    if (untouchable == 0)
    {
        if (bomerangBro->GetState() != BOMERANG_BRO_STATE_FALL)
        {
            if (level > MARIO_LEVEL_SMALL)
            {
                level = level - 1;
                StartUntouchable();
            }
            else
            {
                DebugOut(L">>> Mario DIE >>> \n");
                SetState(MARIO_STATE_DIE);
            }
        }
    }
}

void CMario::OnCollisionWithChimney(LPCOLLISIONEVENT e)
{
    CChimney* chimney = dynamic_cast<CChimney*>(e->obj);
    CGame* game = CGame::GetInstance();
    if (e->ny < 0 && chimney->getType() == 2&&teleport==0&& game->IsKeyDown(DIK_DOWN))
    {
      
            DebugOut(L"alo");
            teleport = MARIO_TELEPORT_IN;
            teleport_start = GetTickCount64();
        
    }
    if (chimney->getType() == 3 && teleport == 0&& game->IsKeyDown(DIK_UP))
    {
       
            teleport = MARIO_TELEPORT_OUT;
            teleport_start = GetTickCount64();
        
    }
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
    DebugOut(L"[INFO] Mario collided with Mushroom, nx = %f, ny = %f\n", e->nx, e->ny);
    CMushroom* mushroom = dynamic_cast<CMushroom*>(e->obj);
    mushroom->SetState(MUSHROOM_STATE_EATEN);
    if (level == MARIO_LEVEL_SMALL)
        SetLevel(MARIO_LEVEL_BIG);
    LPGAMEOBJECT effectPoint = new CEffectPoint(x, y, 1000);
    LPSCENE s = CGame::GetInstance()->GetCurrentScene();
    LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
    p->PushBackGameObject(effectPoint);
}

void CMario::OnCollisionWithLeaf(LPCOLLISIONEVENT e)
{
    DebugOut(L"[INFO] Mario collided with Leaf, nx = %f, ny = %f\n", e->nx, e->ny);
    CLeaf* leaf = dynamic_cast<CLeaf*>(e->obj);
    saved_x = x;
    saved_y = y;
    leaf->Delete();
    if (level == MARIO_LEVEL_BIG && !isWaitingForLevelUp)
    {
        isVisible = false;
        isWaitingForLevelUp = true;
        timeWaitingStart = GetTickCount();
    }
    LPGAMEOBJECT effectPoint = new CEffectPoint(x, y, 1000);
    LPGAMEOBJECT effectSmoke = new CEffectSmoke(x, y);
    LPSCENE s = CGame::GetInstance()->GetCurrentScene();
    LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
    p->PushBackGameObject(effectPoint);
    p->PushBackGameObject(effectSmoke);
}

void CMario::OnCollisionWithBullet(LPCOLLISIONEVENT e)
{
    CBullet* bullet = dynamic_cast<CBullet*>(e->obj);
    if (untouchable == 0)
    {
        if (level > MARIO_LEVEL_SMALL)
        {
            StartUntouchable();
            level = level - 1;
        }
        else
        {
            DebugOut(L">>> Mario DIE >>> \n");
            SetState(MARIO_STATE_DIE);
        }
    }
}

void CMario::OnCollisionWithFlower(LPCOLLISIONEVENT e)
{
    CFlower* flower = dynamic_cast<CFlower*>(e->obj);
    if (untouchable == 0)
    {
        if (level == MARIO_LEVEL_MAX && whip_start != 0 && GetTickCount64() - whip_start <= MARIO_WHIP_TIME && e->nx != 0)
        {
            float x, y;
            flower->GetPosition(x, y);
            CExplodeAni* exp = new CExplodeAni(x, y);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->AddGameObject(exp);
            flower->Delete();
        }
        else if (level > MARIO_LEVEL_SMALL)
        {
            StartUntouchable();
            level = level - 1;
        }
        else
        {
            DebugOut(L">>> Mario DIE >>> \n");
            SetState(MARIO_STATE_DIE);
        }
    }
}

void CMario::OnCollisionWithGiftBox(LPCOLLISIONEVENT e)
{
    CGiftBox* giftbox = dynamic_cast<CGiftBox*>(e->obj);
    if (e->ny > 0) {
        giftbox->Open(this);
    }
}

void CMario::OnCollisionWithCoinBrick(LPCOLLISIONEVENT e)
{
    CCoinBrick* coinbrick = dynamic_cast<CCoinBrick*>(e->obj);
    if (e->ny > 0) {
        coinbrick->OpenCoinBox();
    }
}

void CMario::OnCollisionWithKooPas(LPCOLLISIONEVENT e)
{
    CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
    koopas->mario = this;
    bool areFacingEachOther = 1;
    if ((nx > 0 && koopas->vx > 0 && koopas->x < x) || (nx < 0 && koopas->vx < 0 && koopas->x > x))
    {
        areFacingEachOther = 0;
    }

    // jump on top >> kill Goomba and deflect a bit 
    if (e->ny < 0)
    {



        if (koopas->GetState() != KOOPAS_STATE_SHELL && koopas->GetState() != KOOPAS_STATE_SHELL_MOVING && koopas->GetState() != KOOPAS_STATE_REVERSE)
        {
            koopas->SetState(KOOPAS_STATE_SHELL);

            vy = -MARIO_JUMP_DEFLECT_SPEED;
            LPGAMEOBJECT effectPoint = new CEffectPoint(x, y, 100);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->PushBackGameObject(effectPoint);
        }
        else if (koopas->GetState() == KOOPAS_STATE_REVERSE)
        {
            koopas->SetState(KOOPAS_STATE_SHELL_MOVING);

            if (x <= koopas->x)
            {
                koopas->nx = 1;
                vx = abs(vx);
            }
            else
            {
                koopas->nx = -1;
                vx = -abs(vx);
            }
        }
        else if (koopas->GetState() == KOOPAS_STATE_SHELL_MOVING)
        {
            vy = -MARIO_JUMP_DEFLECT_SPEED;
            koopas->SetState(KOOPAS_STATE_SHELL);
            koopas->ax = 0;


        }
        else if (koopas->GetState() == KOOPAS_STATE_SHELL)
        {
            koopas->SetState(KOOPAS_STATE_SHELL_MOVING);

            if (x <= koopas->x)
            {
                koopas->nx = 1;
                vx = abs(vx);
            }
            else
            {
                koopas->nx = -1;
                vx = -abs(vx);
            }
        }


    }
    else if (level == MARIO_LEVEL_MAX && whip_start != 0 && GetTickCount64() - whip_start <= MARIO_WHIP_TIME)
    {

        if (IsInWhipRegion(koopas))
        {
            koopas->nx = nx;
            koopas->SetState(KOOPAS_STATE_REVERSE);
        }
    }
    else if (isHolding && heldObject != NULL && !dynamic_cast<CKoopas*>(heldObject)) {
        if (areFacingEachOther)
        {

            koopas->SetState(WINGED_KOOPAS_STATE_FALL);
            float x, y;
            koopas->GetPosition(x, y);
            CExplodeAni* exp = new CExplodeAni(x, y);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->AddGameObject(exp);

            CWingedKoopas* koopas2 = dynamic_cast<CWingedKoopas*>(heldObject);
            SetHolding(false, nullptr);
            koopas2->nx = nx;
            koopas2->SetState(WINGED_KOOPAS_STATE_FALL);
        }
        else
        {
            if (dynamic_cast<CKoopas*>(heldObject))
            {
                CKoopas* koopas = dynamic_cast<CKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(KOOPAS_STATE_FALL);
            }
            else if (dynamic_cast<CWingedKoopas*>(heldObject))
            {
                CWingedKoopas* koopas = dynamic_cast<CWingedKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(WINGED_KOOPAS_STATE_FALL);
            }
            if (untouchable == 0)
            {
                if (koopas->GetState() != KOOPAS_STATE_FALL)
                {
                    if (level > MARIO_LEVEL_SMALL)
                    {
                        level = level - 1;
                        StartUntouchable();
                    }
                    else
                    {
                        DebugOut(L">>> Mario DIE >>> \n");
                        SetState(MARIO_STATE_DIE);
                    }
                }
            }
        }
   

    }
    else
    {
        if (untouchable == 0)
        {
            if (koopas->GetState() == KOOPAS_STATE_FALL)
                return;
            if (koopas->GetState() != KOOPAS_STATE_SHELL && koopas->GetState() != KOOPAS_STATE_HELD && koopas->GetState() != WINGED_KOOPAS_STATE_REVERSE)
            {
                if (level > MARIO_LEVEL_SMALL)
                {

                    level = level - 1;
                    StartUntouchable();
                }
                else
                {
                    DebugOut(L">>> Mario DIE >>> \n");
                    SetState(MARIO_STATE_DIE);

                }
            }
            else
            {

                CGame* game = CGame::GetInstance();
                if (game->IsKeyDown(DIK_A)) // Run key
                {
                    if(hold_start==0)
                    hold_start = GetTickCount64();
                    SetHolding(true, koopas);
                    koopas->SetState(KOOPAS_STATE_HELD);
                }
                else
                {
                    koopas->nx = this->nx;
                    koopas->SetState(KOOPAS_STATE_SHELL_MOVING);
                }


            }
        }
    }
}

void CMario::OnCollisionWithWingedKoopas(LPCOLLISIONEVENT e)
{
    CWingedKoopas* koopas = dynamic_cast<CWingedKoopas*>(e->obj);
    koopas->mario = this;
    bool areFacingEachOther = 1;
    if((nx > 0 && koopas->vx > 0 && koopas->x < x)|| (nx < 0 && koopas->vx < 0 && koopas->x > x))
    {
        areFacingEachOther = 0;
    }

    if (e->ny < 0)
    {
        if (koopas->canFly)
        {
            koopas->canFly = false;
            vy = -MARIO_JUMP_DEFLECT_SPEED;
        }
        else
        {
            if (koopas->GetState() != KOOPAS_STATE_SHELL && koopas->GetState() != KOOPAS_STATE_SHELL_MOVING && koopas->GetState() != KOOPAS_STATE_REVERSE)
            {
                koopas->SetState(KOOPAS_STATE_SHELL);
                vy = -MARIO_JUMP_DEFLECT_SPEED;
                LPGAMEOBJECT effectPoint = new CEffectPoint(x, y, 100);
                LPSCENE s = CGame::GetInstance()->GetCurrentScene();
                LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
                p->PushBackGameObject(effectPoint);
            }
            else if (koopas->GetState() == KOOPAS_STATE_SHELL_MOVING)
            {
                vy = -MARIO_JUMP_DEFLECT_SPEED;
                koopas->SetState(KOOPAS_STATE_SHELL);
                koopas->ax = 0;
            }
            else if (koopas->GetState() == WINGED_KOOPAS_STATE_SHELL)
            {
                koopas->SetState(WINGED_KOOPAS_STATE_SHELL_MOVING);
                if (vx > 0)
                    koopas->nx = 1;
                else
                    koopas->nx = -1;
            }
            else if (koopas->GetState() == WINGED_KOOPAS_STATE_REVERSE)
            {
                koopas->SetState(WINGED_KOOPAS_STATE_SHELL_MOVING);
                if (x <= koopas->x)
                    koopas->nx = 1;
                else
                    koopas->nx = -1;
            }
            else if (koopas->GetState() == KOOPAS_STATE_SHELL_MOVING)
            {
                vy = -MARIO_JUMP_DEFLECT_SPEED;
                koopas->SetState(KOOPAS_STATE_FALL);
                koopas->ax = 0;
            }
        }
    }
    else if (isHolding && heldObject != NULL && !dynamic_cast<CWingedKoopas*>(heldObject)) {
        if (areFacingEachOther)
        {
            koopas->SetState(WINGED_KOOPAS_STATE_FALL);
            float x, y;
            koopas->GetPosition(x, y);
            CExplodeAni* exp = new CExplodeAni(x, y);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->AddGameObject(exp);
            CKoopas* koopas2 = dynamic_cast<CKoopas*>(heldObject);
            SetHolding(false, nullptr);
            koopas2->nx = nx;
            koopas2->SetState(KOOPAS_STATE_FALL);
        }
        else
        {
            if (dynamic_cast<CKoopas*>(heldObject))
            {
                CKoopas* koopas = dynamic_cast<CKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(KOOPAS_STATE_FALL);
            }
            else if (dynamic_cast<CWingedKoopas*>(heldObject))
            {
                CWingedKoopas* koopas = dynamic_cast<CWingedKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(WINGED_KOOPAS_STATE_FALL);
            }
            if (untouchable == 0)
            {
                if (koopas->GetState() != WINGED_KOOPAS_STATE_FALL)
                {
                    if (level > MARIO_LEVEL_SMALL)
                    {
                        level = level - 1;
                        StartUntouchable();
                    }
                    else
                    {
                        DebugOut(L">>> Mario DIE >>> \n");
                        SetState(MARIO_STATE_DIE);
                    }
                }
            }
        }
    }
    else if (level == MARIO_LEVEL_MAX && whip_start != 0 && GetTickCount64() - whip_start <= MARIO_WHIP_TIME)
    {
        if (IsInWhipRegion(koopas))
        {
            koopas->nx = nx;
            koopas->SetState(WINGED_KOOPAS_STATE_REVERSE);
        }
     
    }
    else
    {
        if (untouchable == 0)
        {
            if (koopas->GetState() == WINGED_KOOPAS_STATE_FALL)
                return;
            if (koopas->GetState() != WINGED_KOOPAS_STATE_SHELL && koopas->GetState() != WINGED_KOOPAS_STATE_HELD && koopas->GetState() != WINGED_KOOPAS_STATE_REVERSE)
            {
                if (level > MARIO_LEVEL_SMALL)
                {
                    level = level - 1;
                    StartUntouchable();
                }
                else
                {
                    DebugOut(L">>> Mario DIE >>> \n");
                    SetState(MARIO_STATE_DIE);
                }
            }
            else
            {
                CGame* game = CGame::GetInstance();
                if (game->IsKeyDown(DIK_A))
                {
                    if (hold_start == 0)
                    hold_start = GetTickCount64();
                    SetHolding(true, koopas);
                    koopas->SetState(WINGED_KOOPAS_STATE_HELD);
                }
                else
                {
                    koopas->nx = this->nx;
                    koopas->SetState(WINGED_KOOPAS_STATE_SHELL_MOVING);
                }
            }
        }
    }
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
    CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
    float goomba_vx, goomba_vy;
    goomba->GetSpeed(goomba_vx, goomba_vy);
    float epsilon = 0.01f;
    bool areFacingEachOther = 1;
    if ((nx > 0 && goomba_vx > 0 && goomba->x < x) || (nx < 0 && goomba_vx < 0 && goomba->x > x))
    {
        areFacingEachOther = 0;
    }
    if (e->ny < 0)
    {
        if (goomba->GetState() != GOOMBA_STATE_DIE)
        {
            goomba->SetState(GOOMBA_STATE_DIE);
            vy = -MARIO_JUMP_DEFLECT_SPEED;
            LPGAMEOBJECT effectPoint = new CEffectPoint(x, y, 100);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->PushBackGameObject(effectPoint);
        }
    }
    else if (isHolding && heldObject != NULL)
    {
        if (areFacingEachOther)
        {

            goomba->SetState(GOOMBA_STATE_FALL);
            float x, y;
            goomba->GetPosition(x, y);
            CExplodeAni* exp = new CExplodeAni(x, y);
            
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->AddGameObject(exp);

            if (dynamic_cast<CKoopas*>(heldObject))
            {
                CKoopas* koopas = dynamic_cast<CKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(KOOPAS_STATE_FALL);
            }
            else if (dynamic_cast<CWingedKoopas*>(heldObject))
            {
                CWingedKoopas* koopas = dynamic_cast<CWingedKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(WINGED_KOOPAS_STATE_FALL);
            }
            else
            {
                DebugOut(L"error");
            }
    }
        else
        {
            if (dynamic_cast<CKoopas*>(heldObject))
            {
                CKoopas* koopas = dynamic_cast<CKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(KOOPAS_STATE_FALL);
            }
            else if (dynamic_cast<CWingedKoopas*>(heldObject))
            {
                CWingedKoopas* koopas = dynamic_cast<CWingedKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(WINGED_KOOPAS_STATE_FALL);
            }
            if (untouchable == 0)
            {
                if (goomba->GetState() != WINGED_GOOMBA_STATE_DIE || WINGED_GOOMBA_STATE_FALL)
                {
                    if (level > MARIO_LEVEL_SMALL)
                    {
                        level = level - 1;
                        StartUntouchable();
                    }
                    else
                    {
                        DebugOut(L">>> Mario DIE >>> \n");
                        SetState(MARIO_STATE_DIE);
                    }
                }
            }
        }
    }
    else if (level == MARIO_LEVEL_MAX && whip_start != 0 && GetTickCount64() - whip_start <= MARIO_WHIP_TIME)
    {
        
        goomba->SetState(GOOMBA_STATE_FALL);
        CExplodeAni* exp = new CExplodeAni(x, y);
        float x, y;
        goomba->GetPosition(x, y);
        LPSCENE s = CGame::GetInstance()->GetCurrentScene();
        LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
        p->AddGameObject(exp);
    }
    else
    {
        if (untouchable == 0)
        {
            if (goomba->GetState() != GOOMBA_STATE_DIE || GOOMBA_STATE_FALL)
            {
                if (level > MARIO_LEVEL_SMALL)
                {
                    level = level - 1;
                    StartUntouchable();
                }
                else
                {
                    DebugOut(L">>> Mario DIE >>> \n");
                    SetState(MARIO_STATE_DIE);
                }
            }
        }
    }
}

void CMario::OnCollisionWithWingedGoomba(LPCOLLISIONEVENT e)
{
    CWingedGoomba* goomba = dynamic_cast<CWingedGoomba*>(e->obj);
    float goomba_vx, goomba_vy;
    goomba->GetSpeed(goomba_vx, goomba_vy);
    float epsilon = 0.01f;
    bool areFacingEachOther = 1;
    if((nx > 0 && goomba_vx > 0 && goomba->x < x)|| (nx < 0 && goomba_vx < 0 && goomba->x > x))
    {
        areFacingEachOther = 0;
    }

    if (e->ny < 0)
    {
        if (goomba->GetState() == WINGED_GOOMBA_STATE_WALKING)
        {
            goomba->SetState(WINGED_GOOMBA_STATE_DIE);
            vy = -MARIO_JUMP_DEFLECT_SPEED;
            LPGAMEOBJECT effectPoint = new CEffectPoint(x, y, 200);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->PushBackGameObject(effectPoint);
        }
        if (goomba->GetState() == WINGED_GOOMBA_STATE_FLYING)
        {
            goomba->SetState(WINGED_GOOMBA_STATE_WALKING);
            vy = -MARIO_JUMP_DEFLECT_SPEED;
            LPGAMEOBJECT effectPoint = new CEffectPoint(x, y, 100);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->PushBackGameObject(effectPoint);
        }
    }
    else if (isHolding && heldObject != NULL)
    {
        if (areFacingEachOther)
        {

            goomba->SetState(WINGED_GOOMBA_STATE_FALL);
            float x, y;
            goomba->GetPosition(x, y);
            CExplodeAni* exp = new CExplodeAni(x, y);
            LPSCENE s = CGame::GetInstance()->GetCurrentScene();
            LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
            p->AddGameObject(exp);
            if (dynamic_cast<CKoopas*>(heldObject))
            {
                CKoopas* koopas = dynamic_cast<CKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(KOOPAS_STATE_FALL);
            }
            else if (dynamic_cast<CWingedKoopas*>(heldObject))
            {
                CWingedKoopas* koopas = dynamic_cast<CWingedKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(WINGED_KOOPAS_STATE_FALL);
            }
            else
            {
                DebugOut(L"error");
            }
        }
        else
        {
            if (dynamic_cast<CKoopas*>(heldObject))
            {
                CKoopas* koopas = dynamic_cast<CKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(KOOPAS_STATE_FALL);
            }
            else if (dynamic_cast<CWingedKoopas*>(heldObject))
            {
                CWingedKoopas* koopas = dynamic_cast<CWingedKoopas*>(heldObject);
                SetHolding(false, nullptr);
                koopas->nx = nx;
                koopas->SetState(WINGED_KOOPAS_STATE_FALL);
            }
            if (untouchable == 0)
            {
                if (goomba->GetState() != GOOMBA_STATE_DIE || GOOMBA_STATE_FALL)
                {
                    if (level > MARIO_LEVEL_SMALL)
                    {
                        level = level - 1;
                        StartUntouchable();
                    }
                    else
                    {
                        DebugOut(L">>> Mario DIE >>> \n");
                        SetState(MARIO_STATE_DIE);
                    }
                }
            }
        }
    }
    else if (level == MARIO_LEVEL_MAX && whip_start != 0 && GetTickCount64() - whip_start <= MARIO_WHIP_TIME)
    {

        goomba->SetState(WINGED_GOOMBA_STATE_FALL);
        float x, y;
        goomba->GetPosition(x, y);
        CExplodeAni* exp = new CExplodeAni(x, y);
        LPSCENE s = CGame::GetInstance()->GetCurrentScene();
        LPPLAYSCENE p = dynamic_cast<CPlayScene*>(s);
        p->AddGameObject(exp);
    }
    else
    {
        if (untouchable == 0)
        {
            if (goomba->GetState() != WINGED_GOOMBA_STATE_DIE || WINGED_GOOMBA_STATE_FALL)
            {
                if (level > MARIO_LEVEL_SMALL)
                {
                    level = level - 1;
                    StartUntouchable();
                }
                else
                {
                    DebugOut(L">>> Mario DIE >>> \n");
                    SetState(MARIO_STATE_DIE);
                }
            }
        }
    }
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
    // Debug output to verify collision
    DebugOut(L"[DEBUG] Mario collided with Coin at (%.1f, %.1f)\n", e->obj->x, e->obj->y);

    e->obj->Delete();
    coin++;
    CGameManager::GetInstance()->points += 50;
    CGameManager::GetInstance()->coins += 1;
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
    CPortal* p = (CPortal*)e->obj;
    CGame::GetInstance()->InitiateSwitchScene(2);
}

int CMario::GetAniIdSmall()
{

    int aniId = -1;
    if (isWon)
    {
        aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
        return aniId;
    }
    if (teleport != 0)
    {
        aniId = ID_ANI_MARIO_DIVE_IN;
        return aniId;
    }
    if (isHolding)
    {
        if (vx != 0)
        {
            if (nx > 0)
                aniId = ID_ANI_MARIO_SMALL_HOLD_RIGHT;
            else
                aniId = ID_ANI_MARIO_SMALL_HOLD_LEFT;
        }
        else
        {
            if (nx > 0)
                aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_RIGHT;
            else
                aniId = ID_ANI_MARIO_SMALL_HOLD_IDLE_LEFT;
        }
    }
     else if (isFlying)
    {

        if (isOnPlatform)
        {
            if (nx >= 0)
                aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
            else
                aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
        }
        else
        {
            if (nx >= 0)
                aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
            else
                aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
        }
    }
    else
    {
        if (!isOnPlatform)
        {

            if (abs(ax) == MARIO_ACCEL_RUN_X)
            {
                if (nx >= 0)
                    aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
                else
                    aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
            }
            else
            {
                if (nx >= 0)
                    aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
                else
                    aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
            }
        }
        else
        if (isSitting)
        {
            if (nx > 0)
                aniId = ID_ANI_MARIO_SIT_RIGHT;
            else
                aniId = ID_ANI_MARIO_SIT_LEFT;
        }
        else
        if (vx == 0)
        {
            if (nx > 0)
                if (ax == 0)
                    aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
                else
                    aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
            else
                if (ax == 0)
                    aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
                else
                    aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
        }
        else if (vx > 0)
        {
            if (state != MARIO_STATE_SLIP_RIGHT)
            {
                if (ax < 0)
                    aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
                else if (ax == MARIO_ACCEL_RUN_X )
                    aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
                else if (ax == MARIO_ACCEL_WALK_X)
                    aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
            }
            else
            {
                aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
            }
        }
        else
        {
            if (state != MARIO_STATE_SLIP_LEFT)
            {
                if (ax > 0)
                    aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
                else if (ax == -MARIO_ACCEL_RUN_X)
                    aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
                else if (ax == -MARIO_ACCEL_WALK_X)
                    aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
            }
            else
            {
                aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
            }
        }
    }
    if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
    return aniId;
}

int CMario::GetAniIdBig()
{
    
    int aniId = -1;
    if (isWon)
    {
 		aniId = ID_ANI_MARIO_WALKING_RIGHT;
		return aniId;
    }
    if (teleport != 0)
    {
        aniId = ID_ANI_MARIO_DIVE_IN;
		return aniId;
    }
    if (isHolding)
    {
        if (vx != 0)
        {
            if (nx > 0)
                aniId = ID_ANI_MARIO_HOLD_RIGHT;
            else
                aniId = ID_ANI_MARIO_HOLD_LEFT;
        }
        else
        {
            if (nx > 0)
                aniId = ID_ANI_MARIO_HOLD_IDLE_RIGHT;
            else
                aniId = ID_ANI_MARIO_HOLD_IDLE_LEFT;
        }
    }
    else if (isFlying)
    {

        if (isOnPlatform)
        {
            if (nx >= 0)
                aniId = ID_ANI_MARIO_RUNNING_RIGHT;
            else
                aniId = ID_ANI_MARIO_RUNNING_LEFT;
        }
        else
        {
            if (nx >= 0)
                aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
            else
                aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
        }
    }
    else
    {
        if (!isOnPlatform)
        {
            if (abs(ax) == MARIO_ACCEL_RUN_X)
            {
                if (nx >= 0)
                    aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
                else
                    aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
            }
            else
            {
                if (nx >= 0)
                    aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
                else
                    aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
            }
        }
        else
        if (isSitting)
        {
            if (nx > 0)
                aniId = ID_ANI_MARIO_SIT_RIGHT;
            else
                aniId = ID_ANI_MARIO_SIT_LEFT;
        }
        else
        if (vx == 0)
        {
            
            if (nx > 0)
            {
                if(ax==0)
                aniId = ID_ANI_MARIO_IDLE_RIGHT;
                else
                
                    aniId = ID_ANI_MARIO_WALKING_RIGHT;
                
            }
            else {
                if (ax == 0)
                aniId = ID_ANI_MARIO_IDLE_LEFT;
                else

                    aniId = ID_ANI_MARIO_WALKING_LEFT;
            }
        }
        else if (vx > 0)
        {
            if (state != MARIO_STATE_SLIP_RIGHT)
            {
                if (ax < 0)
                    aniId = ID_ANI_MARIO_BRACE_RIGHT;
                else if (ax == MARIO_ACCEL_RUN_X)
                    aniId = ID_ANI_MARIO_WALKING_RIGHT;
                else if (ax == MARIO_ACCEL_WALK_X)
                    aniId = ID_ANI_MARIO_WALKING_RIGHT;
            }
            else
            {
                aniId = ID_ANI_MARIO_WALKING_RIGHT;
            }
        }
        else
        {
            if (state != MARIO_STATE_SLIP_LEFT)
            {
                if (ax > 0)
                    aniId = ID_ANI_MARIO_BRACE_LEFT;
                else if (ax == -MARIO_ACCEL_RUN_X)
                    aniId = ID_ANI_MARIO_WALKING_LEFT;
                else if (ax == -MARIO_ACCEL_WALK_X)
                    aniId = ID_ANI_MARIO_WALKING_LEFT;
            }
            else
            {
                aniId = ID_ANI_MARIO_WALKING_LEFT;
            }
        }
        if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;
    }
    return aniId;
}

int CMario::GetAniIdMax()
{
    int aniId = -1;

    if (teleport != 0||(teleport_start_out!=-1&& GetTickCount64()- teleport_start_out<= MARIO_TELEPORT_DURATION))
         {
        aniId = ID_ANI_MARIO_DIVE_IN;
        return aniId;
    }

	if (isWon)
	{
		aniId = ID_ANI_MARIO_MAX_WALKING_RIGHT;
		return aniId;
	}
 
   
    if (isSlowFalling)
    {
        if (nx > 0)
        {
            aniId = ID_ANI_MARIO_DEF_GRAVITY_RIGHT;
        }
        else
        {
            aniId = ID_ANI_MARIO_DEF_GRAVITY_LEFT;
        }
    }
    else if (isHolding)
    {
        if (vx != 0)
        {
            if (nx > 0)
                aniId = ID_ANI_MARIO_MAX_HOLD_RIGHT;
            else
                aniId = ID_ANI_MARIO_MAX_HOLD_LEFT;
        }
        else
        {
            if (nx > 0)
                aniId = ID_ANI_MARIO_MAX_HOLD_IDLE_RIGHT;
            else
                aniId = ID_ANI_MARIO_MAX_HOLD_IDLE_LEFT;
        }
    }
    else if (isFlying)
    {
        if (isOnPlatform)
        {
            if (nx >= 0)
                aniId = ID_ANI_MARIO_MAX_FLYING_RUNNING_RIGHT;
            else
                aniId = ID_ANI_MARIO_MAX_FLYING_RUNNING_LEFT;
        }
        else
        {
            if (nx >= 0)
                aniId = ID_ANI_MARIO_MAX_FLYING_RIGHT;
            else
                aniId = ID_ANI_MARIO_MAX_FLYING_LEFT;
        }
    }
    else
    {
        if (!isOnPlatform)
        {
            if (abs(ax) == MARIO_ACCEL_RUN_X)
            {
                if (nx >= 0)
                    aniId = ID_ANI_MARIO_MAX_JUMP_RUN_RIGHT;
                else
                    aniId = ID_ANI_MARIO_MAX_JUMP_RUN_LEFT;
            }
            else
            {
                if (nx >= 0)
                    aniId = ID_ANI_MARIO_MAX_JUMP_WALK_RIGHT;
                else
                    aniId = ID_ANI_MARIO_MAX_JUMP_WALK_LEFT;
            }
            if (nx > 0)
            {
                if (GetTickCount64() - whip_start <= MARIO_WHIP_TIME)
                    aniId = ID_ANI_MARIO_WHIP_RIGHT;
              
            }
            else {
                if (GetTickCount64() - whip_start <= MARIO_WHIP_TIME)
                    aniId = ID_ANI_MARIO_WHIP_LEFT;

            }
        }
        else
        if (isSitting)
        {
            if (nx > 0)

                aniId = ID_ANI_MARIO_MAX_SIT_RIGHT;
            else
                aniId = ID_ANI_MARIO_MAX_SIT_LEFT;
        }
        else
        if (vx == 0)
        {
            if (nx > 0)
            {
                if (GetTickCount64() - whip_start <= MARIO_WHIP_TIME)
                    aniId = ID_ANI_MARIO_WHIP_RIGHT;
                else if (ax != 0)
               
                    aniId = ID_ANI_MARIO_MAX_WALKING_RIGHT;
                
                else
                    aniId = ID_ANI_MARIO_MAX_IDLE_RIGHT;
            }
            else {
                if (GetTickCount64() - whip_start <= MARIO_WHIP_TIME)
                    aniId = ID_ANI_MARIO_WHIP_LEFT;
                else if (ax != 0)

                    aniId = ID_ANI_MARIO_MAX_WALKING_LEFT;
                else
                    aniId = ID_ANI_MARIO_MAX_IDLE_LEFT;
            }
        }
        else if (vx > 0)
        {
            if (state != MARIO_STATE_SLIP_RIGHT)
            {
                if (ax < 0)
                {
                    aniId = ID_ANI_MARIO_MAX_BRACE_RIGHT;
                }
                else if (ax == MARIO_ACCEL_RUN_X)
                {
                    if (GetTickCount64() - whip_start <= MARIO_WHIP_TIME)
                        aniId = ID_ANI_MARIO_WHIP_RIGHT;
                    else
                        aniId = ID_ANI_MARIO_MAX_RUNNING_RIGHT;
                }
                else if (ax == MARIO_ACCEL_WALK_X)
                    aniId = ID_ANI_MARIO_MAX_WALKING_RIGHT;
            }
            else
            {
                aniId = ID_ANI_MARIO_MAX_WALKING_RIGHT;
            }
        }
        else
        {
            if (state != MARIO_STATE_SLIP_LEFT)
            {
                if (ax > 0)
                {
                    aniId = ID_ANI_MARIO_MAX_BRACE_LEFT;
                }
                else if (ax == -MARIO_ACCEL_RUN_X)
                {
                    if (GetTickCount64() - whip_start <= MARIO_WHIP_TIME)
                        aniId = ID_ANI_MARIO_WHIP_LEFT;
                    else
                        aniId = ID_ANI_MARIO_MAX_RUNNING_LEFT;
                }
                else if (ax == -MARIO_ACCEL_WALK_X)
                    aniId = ID_ANI_MARIO_MAX_WALKING_LEFT;
            }
            else
            {
                aniId = ID_ANI_MARIO_MAX_WALKING_LEFT;
            }
        }
    }
    if (aniId == -1) aniId = ID_ANI_MARIO_MAX_IDLE_RIGHT;
    return aniId;
}

void CMario::Render()
{

    if (isVisible == false)
        return;
    CAnimations* animations = CAnimations::GetInstance();
    int aniId = -1;

    if (state == MARIO_STATE_DIE)
        aniId = ID_ANI_MARIO_DIE;
    else if (level == MARIO_LEVEL_BIG)
        aniId = GetAniIdBig();
    else if (level == MARIO_LEVEL_SMALL)
        aniId = GetAniIdSmall();
    else if (level == MARIO_LEVEL_MAX)
        aniId = GetAniIdMax();

    if (untouchable == 1)
    {
        ULONGLONG now = GetTickCount64();
        int blinkPeriod = 100;
        int blinkState = ((now - untouchable_start) % blinkPeriod) < (blinkPeriod / 2);
        if (blinkState)
        {
            animations->Get(aniId)->Render(x, y);
        }
    }
    else
    {
        animations->Get(aniId)->Render(x, y);
    }

    DebugOutTitle(L"Coins: %d", coin);
}

void CMario::SetState(int state)
{
    if (this->state == MARIO_STATE_DIE) return;

    switch (state)
    {
  
        case MARIO_STATE_HOLD:
        {
        if (!isHolding) break;
        break;
        }
        case MARIO_STATE_HOLD_RELEASE:
        {
            hold_start = 0;
            if (isHolding && heldObject != NULL)
            {
                if (dynamic_cast<CKoopas*>(heldObject))
                {
                    CKoopas* koopas = dynamic_cast<CKoopas*>(heldObject);
                    if (koopas)
                    {
                        koopas->SetState(KOOPAS_STATE_SHELL_MOVING);
                        koopas->SetSpeed(nx > 0 ? KOOPAS_SHELL_MOVING_SPEED : -KOOPAS_SHELL_MOVING_SPEED, 0);
                        float kx, ky;
                        koopas->GetPosition(kx, ky);
                        if (level == MARIO_LEVEL_SMALL)
                            ky -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
                        koopas->SetPosition(kx, ky);
                    }
                    SetHolding(false, NULL);
                }
                if (dynamic_cast<CWingedKoopas*>(heldObject))
                {
                    CWingedKoopas* koopas = dynamic_cast<CWingedKoopas*>(heldObject);
                    if (koopas)
                    {
                        koopas->SetState(WINGED_KOOPAS_STATE_SHELL_MOVING);
                        koopas->SetSpeed(nx > 0 ? WINGED_KOOPAS_SHELL_MOVING_SPEED : -WINGED_KOOPAS_SHELL_MOVING_SPEED, 0);
                        float kx, ky;
                        koopas->GetPosition(kx, ky);
                        if (level == MARIO_LEVEL_SMALL)
                            ky -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
                        koopas->SetPosition(kx, ky);
                    }
                    SetHolding(false, NULL);
                }
            }
            break;
        }
        case MARIO_STATE_RUNNING_RIGHT:
        {
            if (isSitting) break;
            maxVx = MARIO_RUNNING_SPEED;
            ax = MARIO_ACCEL_RUN_X;
            nx = 1;
            StartRunning();
            StartWhip();
            break;
        }
        case MARIO_STATE_RUNNING_LEFT:
        {
            if (isSitting) break;
            maxVx = -MARIO_RUNNING_SPEED;
            ax = -MARIO_ACCEL_RUN_X;
            nx = -1;
            StartRunning();
            StartWhip();
            break;
        }
        case MARIO_STATE_WALKING_RIGHT:
        {
            if (isSitting) break;
            maxVx = MARIO_WALKING_SPEED;
            ax = MARIO_ACCEL_WALK_X;
            nx = 1;
            break;
        }
        case MARIO_STATE_WALKING_LEFT:
        {
            if (isSitting) break;
            maxVx = -MARIO_WALKING_SPEED;
            ax = -MARIO_ACCEL_WALK_X;
            nx = -1;
            break;
        }
        case MARIO_STATE_JUMP:
        {
            if (vx == 0)
            {
                vx = 0;
                ax = 0;
            }
            CScene* scene = CGame::GetInstance()->GetCurrentScene();
            CSampleKeyHandler* keyHandler = dynamic_cast<CSampleKeyHandler*>(scene->GetKeyEventHandler());
            if (keyHandler)
            {
                bool holdingS = keyHandler->holdingS;
                if (!holdingS)
                {
                    onMovable = false;
                }
            }
            if (isOnPlatform)
            {
                if (isFlying)
                {
                    vy = MARIO_JUMP_FLY_SPEED_Y;
                    fly_timer = GetTickCount64();
                }
                else if (abs(this->vx) == MARIO_RUNNING_SPEED)
                    vy = -MARIO_JUMP_RUN_SPEED_Y;
                else
                    vy = -MARIO_JUMP_SPEED_Y;
                ay = MARIO_GRAVITY;
            }
            else
            {

                if (isFlying && level == MARIO_LEVEL_MAX)
                {
                    vy = MARIO_JUMP_FLY_SPEED_Y;
                  
                }
            }
           
            break;
        }
        case MARIO_STATE_RELEASE_JUMP:
        {
            
            if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
            if (vy == 0)
            {
                vx = 0;
            }
            break;
        }
        case MARIO_STATE_SIT:
        {
            isFlying = false;
            fly_timer = 0;
            StopRunning();
            StopWhip();
            if (isOnPlatform && level != MARIO_LEVEL_SMALL)
            {
                state = MARIO_STATE_IDLE;
                isSitting = true;
                vx = 0; vy = 0.0f;
                y += MARIO_SIT_HEIGHT_ADJUST;
            }
            break;
        }
        case MARIO_STATE_SIT_RELEASE:
        {
            if (isSitting)
            {
                isSitting = false;
                state = MARIO_STATE_IDLE;
                y -= MARIO_SIT_HEIGHT_ADJUST;
            }
            break;
        }
        case MARIO_STATE_IDLE:
        {
            ax = 0.0f;
            vx = 0.0f;
            break;
        }
        case MARIO_STATE_DIE:
        {
            vy = -MARIO_JUMP_DEFLECT_SPEED;
            vx = 0;
            ax = 0;
            break;
        }
        case MARIO_STATE_SLIP_RIGHT:
        {
            if (isOnPlatform)
            {
              
                ax = -MARIO_SLIP_DECEL;
            }
            break;
        }
        case MARIO_STATE_SLIP_LEFT:
        {
            if (isOnPlatform)
            {
              
                ax = MARIO_SLIP_DECEL;
            }
            break;
        }
    }
    CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
    if (level == MARIO_LEVEL_BIG)
    {
        if (isSitting)
        {
            left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
            top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
            right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
            bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
        }
        else
        {
            left = x - MARIO_BIG_BBOX_WIDTH / 2;
            top = y - MARIO_BIG_BBOX_HEIGHT / 2;
            right = left + MARIO_BIG_BBOX_WIDTH;
            bottom = top + MARIO_BIG_BBOX_HEIGHT;
        }
    }
    else if (level == MARIO_LEVEL_MAX)
    {
        if (isSitting)
        {
            left = x - MARIO_MAX_SITTING_BBOX_WIDTH / 2;
            top = y - MARIO_MAX_SITTING_BBOX_HEIGHT / 2;
            right = left + MARIO_MAX_SITTING_BBOX_WIDTH;
            bottom = top + MARIO_MAX_SITTING_BBOX_HEIGHT;
        }
        else
        {
            left = x - MARIO_MAX_BBOX_WIDTH / 2;
            top = y - MARIO_MAX_BBOX_HEIGHT / 2;
            right = left + MARIO_MAX_BBOX_WIDTH;
            bottom = top + MARIO_MAX_BBOX_HEIGHT;
        }
    }
    else
    {
        left = x - MARIO_SMALL_BBOX_WIDTH / 2;
        top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
        right = left + MARIO_SMALL_BBOX_WIDTH;
        bottom = top + MARIO_SMALL_BBOX_HEIGHT + 1;
    }
}

void CMario::SetLevel(int l)
{
    if (this->level == MARIO_LEVEL_SMALL)
    {
        y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
    }
    level = l;
    CGame* cgame = CGame::GetInstance();
    cgame->marioLevel=l;
}