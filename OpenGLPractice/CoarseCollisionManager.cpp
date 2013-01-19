#include "CoarseCollisionManager.h"

CoarseCollisionManager::CoarseCollisionManager(void)
{
}


CoarseCollisionManager::~CoarseCollisionManager(void)
{
}


array<Collidable*, sizeof(Collidable *)> * CoarseCollisionManager::BuildPotentialCollisionsList(Collidable* testObject)
{
	array<int, sizeof(int)> *collidableCategories = testObject->CollidableCategories();
	_Array_iterator<int, sizeof(int)> i;
	if(collidableCategories->empty())
	{
		return NULL;
	}
	for(i = collidableCategories->begin(); i <= collidableCategories->end(); i++)
	{
		CollidablesBinaryTree* collidablesTree = collisionManager->ObtainCollidablesByCategory(collidableCategories[i]);

	}
}

