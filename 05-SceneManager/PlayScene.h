#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
//#include "Koopas.h"


class CPlayScene: public CScene
{
protected: 

	// A play scene has to have player, right? 
	LPGAMEOBJECT player;					

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);

	void LoadAssets(LPCWSTR assetFile);
	
public: 
	bool alreadyFly;
	CPlayScene(int id, LPCWSTR filePath);
	float curentCX;

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

	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

