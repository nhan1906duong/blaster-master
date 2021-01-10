#include "GridManager.h"

#include "Game.h"
#include "Map.h"
#include "Camera.h"

#include "Enemy.h"

#include <algorithm>

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

int GridManager::round(int num, int other)
{
	return (num % other == 0) ? num / other : (int) ceil(num / other) + 1;
}

void GridManager::Clear()
{
	for (size_t i = 0; i < grids.size(); i++)
	{
		grids[i].clear();
	}
	grids.clear();
	for (size_t i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
	objects.clear();
}

void GridManager::Reset()
{
	int screen_width = CGame::GetInstance()->GetScreenWidth();
	int screen_height = CGame::GetInstance()->GetScreenHeight();

	int map_width, map_height;
	Map::GetInstance()->GetBouncing(map_height, map_width);

	int numColumn = this->round(2 * map_width, screen_width);
	int numRow = this->round(2 * map_height, screen_height);

	for (int row = 0; row < numRow; row++)
	{
		vector<Grid*> rowGrid;
		for (int column = 0; column < numColumn; column++)
		{
			Grid* grid = new Grid();
			rowGrid.push_back(grid);
		}
		grids.push_back(rowGrid);
	}
}

void GridManager::AddObject(LPGAMEOBJECT object)
{
	objects.push_back(object);
	_AddToGrid(object);
}

void GridManager::_AddToGrid(LPGAMEOBJECT object)
{
	float left, top, right, bottom;
	object->GetBoundingBox(left, top, right, bottom);

	float ceil_width = CGame::GetInstance()->GetScreenWidth() / 2.0f;
	float ceil_height = CGame::GetInstance()->GetScreenHeight() / 2.0f;

	size_t fromRow = (size_t) (bottom / ceil_height);
	size_t toRow = (size_t) (top / ceil_height);

	size_t fromColumn = (size_t) (left / ceil_width);
	size_t toColumn = (size_t) (right / ceil_width);

	if (fromRow < 0 || fromColumn < 0 || toRow > grids.size() - 1 || toColumn > grids[0].size() - 1) return;

	for (size_t row = fromRow; row <= toRow; ++row)
	{
		for (size_t column = fromColumn; column <= toColumn; ++column)
		{
			grids.at(row).at(column)->AddObject(object);
		}
	}
}



vector<LPGAMEOBJECT> GridManager::GetObjectsToUpdate()
{
	for (size_t row = 0; row < grids.size(); ++row)
	{
		vector<Grid*> rowGrid = grids[row];
		for (size_t column = 0; column < rowGrid.size(); ++column)
		{
			Grid* grid = rowGrid[column];
			grid->ClearObjects();
		}
	}


	objects.erase(remove_if(objects.begin(), objects.end(), [](const LPGAMEOBJECT obj) {
		return obj->shouldRemove == true;
	}), objects.end());

	/*collisions.erase(remove_if(collisions.begin(), collisions.end(), [](const CollisionExplosion* obj) {
		return obj->shouldRemove == true;
	}), collisions.end());*/

	for (size_t i = 0; i < objects.size(); ++i)
	{
		_AddToGrid(objects[i]);
	}

	vector<LPGAMEOBJECT> result;
	float ceil_width = CGame::GetInstance()->GetScreenWidth() / 2.0f;
	float ceil_height = CGame::GetInstance()->GetScreenHeight() / 2.0f;

	float x, y;
	Camera::GetInstance()->GetPosition(x, y);

	int fromColumn = (int)  (x / ceil_width);
	int toRow = (int) (y / ceil_height);

	int toColumn = fromColumn + 2 >= grids.at(0).size() - 1 ? grids.at(0).size() - 1 : fromColumn + 2;

	for (int row = toRow; row >= toRow - 2; --row)
	{
		for (int column = fromColumn; column <= toColumn; ++column)
		{
			Grid* currentGrid = grids.at(row).at(column);
			vector<LPGAMEOBJECT> objects = currentGrid->GetObjects();
			for (size_t i = 0; i < objects.size(); ++i)
			{
				LPGAMEOBJECT obj = objects[i];
				if (dynamic_cast<Enemy*>(obj))
				{
					Enemy* enemy = dynamic_cast<Enemy*>(obj);
					if (!enemy->IsAppear())
					{
						float left, top, right, bottom;
						enemy->GetBoundingBox(left, top, right, bottom);
						if (!Camera::GetInstance()->IsInCamera(left, top, right, bottom))
						{
							continue;
						}
						else
						{
							enemy->SetAppear();
						}
					}
				}
				bool isExist = false;
				for (size_t index = 0; index < result.size(); ++index)
				{
					if (obj == result[index])
					{
						isExist = true;
						break;
					}
				}
				if (!isExist)
				{
				result.push_back(obj);
				}
			}
		}
	}
	return result;
}