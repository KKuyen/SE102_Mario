#include "GameManager.h"

CGameManager* CGameManager::__instance = NULL;

CGameManager* CGameManager::GetInstance()
{
	if (__instance == NULL) __instance = new CGameManager(0, 0);
	return __instance;
}