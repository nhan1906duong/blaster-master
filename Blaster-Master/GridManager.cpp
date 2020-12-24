#include "GridManager.h"

GridManager* GridManager::__instance = NULL;

GridManager* GridManager::GetInstance()
{
	if (__instance == NULL)
	{
		__instance = new GridManager();
	}

	return __instance;
}

GridManager::GridManager()
{

}
