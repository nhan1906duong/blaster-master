#include "Grid.h"

#include <algorithm>

Grid::Grid()
{

}

void Grid::RemoveObject(LPGAMEOBJECT object)
{
	objects.erase(remove(objects.begin(), objects.end(), object), objects.end());
}

void Grid::AddObject(LPGAMEOBJECT object)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (object == objects[i]) return;
	}
	objects.push_back(object);
}