﻿#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "Brick.h"
#include "Background.h"
#include "PiranhaPlant.h"
#include "Koopas.h" 
#include "WingedGoomba.h"
#include "HiddenButton.h"

#include "SampleKeyEventHandler.h"
#include "ColorBox.h"
#include "Chimney.h"
#include "GiftBox.h"
#include "EffectGiftBoxCoin.h"
#include "Effect.h"
#include "EffectPoint.h"
#include "Mushroom.h"
#include "Flower.h"
#include "Leaf.h"
#include "DarkBackground.h"
#include "Transcript.h"
#include "WIngedKoopas.h"
#include "BreakableBrick.h"
#include "GrassPlatform.h"
#include "MovablePlatform.h"
#include "BomerangBro.h"
#include "CoinBrick.h"
#include "WingedRedKoopa.h"
#include "BreakableBrickChain.h"
#include "BlackGiftBox.h"
using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	transcript = NULL;
	key_handler = new CSampleKeyHandler(this);
	alreadyFly = false;
	alreadyTeleport = false;
	curentCX = 10;
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024
#define CAMERA_POSITION_HIDDEN_MAP_Y 192
#define RIGH_MAP_LIMIT 2540
#define SCENE_2_PAUSE_DURATION 1000 // 2 giây dừng camera

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;
	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_BOMERANGBRO: {
		obj = new CBomerangBro(x, y);
		if (player != nullptr && dynamic_cast<CMario*>(player)) {
			((CBomerangBro*)obj)->SetMario((CMario*)player);
		}
		break;
	}
	case OBJECT_TYPE_WINGED_GOOMBA: {
		obj = new CWingedGoomba(x, y);
		break;

	}
	case OBJECT_TYPE_BRICK: {
		float spriteId = (float)atof(tokens[3].c_str());
		obj = new CBrick(x, y, spriteId); break;
	}
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
	case OBJECT_TYPE_TRANSCRIPT:
	{
		int width = atoi(tokens[3].c_str());
		int height = atoi(tokens[4].c_str());
		int spriteId = atoi(tokens[5].c_str());
		obj = new CTranscript(x, y, width, height, spriteId);
		transcript = (CTranscript*)obj;
		DebugOut(L"[DEBUG] Transcript object created at (%.1f, %.1f)\n", x, y);

		objects.push_back(obj);
	}
	break;
	case OBJECT_TYPE_GIFTBOX: {
		float animationId = (float)atof(tokens[3].c_str());
		int type = atoi(tokens[4].c_str());
		obj = new CGiftBox(x, y, animationId, type); break;
	}
	case OBJECT_TYPE_COIN_BRICK: {
		int quantity = (int)atof(tokens[3].c_str());
		obj = new CCoinBrick(x, y, quantity); break;
	}
	case OBJECT_TYPE_KOOPAS:
	{
		try {
			float color = (float)atof(tokens[3].c_str());
			obj = new CKoopas(x, y,color);
			break;
		}
		catch (const std::exception& error) // Correct exception declaration
		{
			obj = new CKoopas(x, y);
			break;
		}
		
		
	}
	case OBJECT_TYPE_BACKGROUND: {
		float width = (float)atof(tokens[3].c_str());
		float height = (float)atof(tokens[4].c_str());
		float spriteId = (float)atof(tokens[5].c_str());
		obj = new CBackground(x, y, width, height, spriteId); break;
	}
	case OBJECT_TYPE_COLORBOX: {
		int widthCells = atoi(tokens[3].c_str());
		int heightCells = atoi(tokens[4].c_str());
		int color = atoi(tokens[5].c_str());
		int isPlatform = atoi(tokens[6].c_str());

		obj = new CColorBox(
			x, y,
			widthCells, heightCells,
			color, isPlatform
		);

		break;
	}
	case OBJECT_TYPE_GRASSPLATFORM: {
		int widthCells = atoi(tokens[3].c_str());
		int heightCells = atoi(tokens[4].c_str());
		int isPlatform = atoi(tokens[5].c_str());

		obj = new CGrassPlatform(
			x, y,
			widthCells, heightCells,
			isPlatform
		);

		break;
	}
	case BLACK_GIFT_BOX:
	{
		int type = atoi(tokens[3].c_str());
		obj = new CBlackGiftBox(x, y, type);
		objects.push_back(obj);
	}
	break;
	case OBJECT_TYPE_BREAKABLE_BRICK_CHAIN:
	{
		if (tokens.size() < 5) return; // Need type, x, y, length, chainType
		int length = atoi(tokens[3].c_str());
		int chainType = atoi(tokens[4].c_str());
		obj = new CBreakableBrickChain(x, y, length, chainType);
		break;
	}
	case OBJECT_TYPE_DARK_BACKGROUND: {
		int widthCells = atoi(tokens[3].c_str());
		int heightCells = atoi(tokens[4].c_str());
		obj = new CDarkBackground(
			x, y,
			widthCells, heightCells

		);

		break;
	}
	case OBJECT_TYPE_CHIMNEY: {
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		int isVertical = atoi(tokens[9].c_str());
		int type = (int)atoi(tokens[10].c_str());

		obj = new CChimney(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end,
			isVertical, type
		);

		break;
	}
	case OBJECT_TYPE_FLOWER: {
		int flowerType = atoi(tokens[3].c_str());
		obj = new CFlower(x, y, flowerType);
		if (flowerType == 1) {
			obj->SetState(FLOWER_STATE_RIGHT_POP_UP);
		}
		else if (flowerType == 2) {
			obj->SetState(FLOWER_STATE_LEFT_POP_UP);
		}
		else if (flowerType == 3) {
			obj->SetState(FLOWER_STATE_LEFT_POP_UP);
		}
 		break;
	}
	case OBJECT_TYPE_LEAF: obj = new CLeaf(x, y); break;
	case OBJECT_TYPE_MOVABLEPLATFORM: obj = new CMovablePlatform(x, y); break;
	case WINGED_RED_KOOPA: obj = new CWingedRedKoopa(x, y); break;
	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());
		int isVertical = atoi(tokens[9].c_str());
		int animationId = atoi(tokens[10].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end, isVertical, animationId
		);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
		break;
	}
	case OBJECT_TYPE_PIRANHA_PLANT:

	{
		float max_y = (float)atof(tokens[3].c_str());
		obj = new CPiranhaPlant(x, y, max_y);
		break;
	}
	case OBJECT_TYPE_BREAKABLE_BRICK: obj = new CBreakableBrick(x, y); break;
	case OBJECT_TYPE_HIDDEN_BUTTON:
	{
		int type = atoi(tokens[3].c_str());

		obj = new CHiddenButton(x, y, type);

		break;
	}
	case OBJECT_TYPE_WINGED_KOOPAS:
	{
		try {
			int canFlyint = (float)atof(tokens[3].c_str());
			if(canFlyint)
			obj = new CWingedKoopas(x, y,true);
			else
				obj = new CWingedKoopas(x, y, false);
			break;
		}
		catch (const std::exception& error) // Correct exception declaration
		{
			obj = new CWingedKoopas(x, y);
			break;
		}
		obj = new CWingedKoopas(x, y); break;
	}

	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);

	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	// Sau khi load xong toàn bộ object, gán Mario cho các Flower nếu có
	if (player != nullptr) {
		for (size_t i = 0; i < objects.size(); ++i) {
			CFlower* flower = dynamic_cast<CFlower*>(objects[i]);
			if (flower) {
				flower->SetMario((CMario*)player);
			}
		}
	}

	// Đánh dấu nếu vừa chuyển sang scene 2
	if (id == 2)
	{
		justSwitchedToScene2 = true;
		isSwitchedToScene2 = true;
	}

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}
#define MAX_CY -170
#define ALR_FLY_CY -160
#define NOT_ALR_FLY_CY   0
#define SECENE_2_CAMERA_MOVE_CX 0.7
#define SECENE_2_CAMERA_MAX_CX 2310
#define SECENE_2_CAMERA_BEFORE_TELEPORT_CX 1791
#define SECENE_2_TELEPORT_CX 290
void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}
	CGameManager::GetInstance()->Update(dt, nullptr);

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx = 0, cy;
	CScene* currentScene = CGame::GetInstance()->GetCurrentScene();
	if (currentScene->GetId() == 1) {
		player->GetPosition(cx, cy);

		CGame* game = CGame::GetInstance();
		cx -= game->GetBackBufferWidth() / 2;
		cy -= game->GetBackBufferHeight() / 2;

		CMario* mario = dynamic_cast<CMario*>(player);
		if (cy < MAX_CY)
		{
			cy = MAX_CY;
		}
		else if (cy < ALR_FLY_CY&&mario->isFlying)
		{
			alreadyFly = true;
		}
		else if (cy > 0||mario->isOnPlatform)
		{
			cy = 0.0f;
			alreadyFly = false;
		}
		else if (mario->vy > 0 && alreadyFly == true)
		{
		}
		
		
		else
		{
			// Khi không bay, giữ camera ở vị trí mặc định theo trục Y
			cy = 0.0f;
		}
		if (mario->teleportState == MARIO_TELEPORT_IN)
			cy = CAMERA_POSITION_HIDDEN_MAP_Y;

		if (cx < 0) cx = 0;
		if (cx > RIGH_MAP_LIMIT) cx = RIGH_MAP_LIMIT;
	}
	else { // Scene ID = 2 (map 1-4)
		CMario* mario = dynamic_cast<CMario*>(player);
		cy = 0;

		// Kiểm tra nếu vừa chuyển sang scene 2
		if (justSwitchedToScene2 && !scene2PauseDone)
		{
			if (scene2PauseStart == 0)
			{
				scene2PauseStart = GetTickCount64(); // Bắt đầu khoảng dừng
			}

			ULONGLONG now = GetTickCount64();
			if (now - scene2PauseStart >= SCENE_2_PAUSE_DURATION)
			{
				scene2PauseDone = true; // Kết thúc khoảng dừng
				justSwitchedToScene2 = false;
			}

			// Giữ camera cố định trong thời gian dừng
			cx = curentCX;
		}
		else
		{
			// Logic camera bình thường sau khi dừng
			if (mario->teleport == MARIO_TELEPORT_IN && GetTickCount64() - mario->teleport_start <= MARIO_TELEPORT_DURATION && mario->teleport_start != -1)
			{
				alreadyTeleport = true;
				curentCX = SECENE_2_CAMERA_BEFORE_TELEPORT_CX;
				cx = curentCX;
			}
			else
			{
				if (alreadyTeleport == true)
				{
					alreadyTeleport = false;
					curentCX += SECENE_2_TELEPORT_CX;
					cx = curentCX + SECENE_2_TELEPORT_CX;
				}
				else
				{
					if (curentCX+1  >= SECENE_2_CAMERA_BEFORE_TELEPORT_CX && curentCX < SECENE_2_CAMERA_BEFORE_TELEPORT_CX+200)
					{
						cx = curentCX;

						
					}
					else if(mario->teleport_start_out != -1 && GetTickCount64() - mario->teleport_start_out <= MARIO_TELEPORT_DURATION)
					{
						cx = curentCX;


					}
					else
					{
						curentCX += CAM_SPEED_1_4;
						cx = curentCX + CAM_SPEED_1_4;
					}

 					float mario_x, mario_y;
					mario->GetPosition(mario_x, mario_y);
					if (mario_x <= cx+10)
					{
 						mario->vx = MARIO_AUTO_SPEED;
 						mario->SetState(MARIO_STATE_WALKING_RIGHT); 
						DebugOut(L"[INFO] Mario touched left edge of camera at cx = %.1f\n", cx );

					}
				}
			}
			if (curentCX > SECENE_2_CAMERA_MAX_CX)
			{
				curentCX = SECENE_2_CAMERA_MAX_CX;
				cx = SECENE_2_CAMERA_MAX_CX;
			}
		}
	}
	if (transcript != NULL)
	{
		//DebugOut(L"[DEBUG] About to call transcript->SetPosition\n");
		transcript->SetPosition(cx + TRANSCRIPT_POSITION_X, cy + TRANSCRIPT_POSITION_Y);
	}

	// Đặt vị trí camera
	CGame::GetInstance()->SetCamPos(cx, cy);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well
*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}

void CPlayScene::AddGameObject(LPGAMEOBJECT obj)
{
	if (400 <= objects.size()) {
		objects.insert(objects.begin() + 300, obj);
	}
	else {
		objects.insert(objects.begin() + 20, obj);
	}
}

void CPlayScene::PushBackGameObject(LPGAMEOBJECT obj)
{
	objects.push_back(obj);
}