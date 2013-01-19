#pragma once
#include "entity.h"
#include <array>
#include "CollisionManager.h"

class Collidable :
	public Entity
{
public:
	Collidable(void);
	~Collidable(void);
	virtual void BuildBoundingBoxesTree(void)=0;	// For every object, we have to run this to build a tree before 
	inline array<int, sizeof(int)> *CollidableCategories(void) { return collidableCategories; }

private:
	int category;
	array<int, sizeof(int)> *collidableCategories;
	CollisionManager*        collisionManager;
};

