#ifndef COARSE_COLLISION_MANAGER_H
#define COARSE_COLLISION_MANAGER_H
#include "entity.h"
#include <array>
#include "Collidable.h"

class CoarseCollisionManager :
	public Entity
{
public:
	CoarseCollisionManager(void);
	~CoarseCollisionManager(void);

	array<Collidable*, sizeof(Collidable *)> * BuildPotentialCollisionsList(Collidable* testObject);
};
#endif