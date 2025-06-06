#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#define CAM_SPEED_1_4	0.7
#define MARIO_AUTO_SPEED	0.1f
#define TRANSCRIPT_POSITION_X 125
#define TRANSCRIPT_POSITION_Y 216



class CPlayScene: public CScene
{
protected: 

	// A play scene has to have player, right? 
					
	LPGAMEOBJECT transcript;
	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);

	// Add these variables to track scene 2 transition and pause
	bool justSwitchedToScene2 = false;
	ULONGLONG scene2PauseStart = 0;
	bool scene2PauseDone = false;
	ULONGLONG scene2CameraDelayStart = 0; // Delay timer for curentCX logic after scene switch
	
public: 
	LPGAMEOBJECT player;
	bool alreadyTeleport;
	bool alreadyFly;
	CPlayScene(int id, LPCWSTR filePath);
	float curentCX;
	bool isSwitchedToScene2 = false;

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void AddGameObject(LPGAMEOBJECT obj);
	void PushBackGameObject(LPGAMEOBJECT obj);

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	vector<LPGAMEOBJECT>& GetObjects() { return objects; }
	void PurgeDeletedObjects();
	int GetIdScene() { return this->id; }

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);

	void StartScene2CameraPause(); // Add this function declaration
};

typedef CPlayScene* LPPLAYSCENE;

