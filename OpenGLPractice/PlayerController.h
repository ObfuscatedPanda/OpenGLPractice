
#include "Controller.h"
#include "InputToControllerAdapter.h"
#include "PlayerEntity.h"

#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

class PlayerController :
	public Controller
{
private:
	PlayerEntity* character;

protected:
	// MOVEMENTS METHODS
	void MoveUp			(float distance);
	void MoveForward	(float distance);
	void MoveDown		(float distance);
	void MoveBackward	(float distance);
	void MoveLeft		(float distance);
	void MoveRight		(float distance);
	void LookUp			(float angle);
	void LookDown		(float angle);
	void LookRight		(float angle);
	void LookLeft		(float angle);

public:
	PlayerController(void);
	~PlayerController(void);
};

#endif