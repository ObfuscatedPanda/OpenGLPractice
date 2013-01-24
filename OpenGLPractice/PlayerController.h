
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
	void MoveUp			(SCALAR distance);
	void MoveForward	(SCALAR distance);
	void MoveDown		(SCALAR distance);
	void MoveBackward	(SCALAR distance);
	void MoveLeft		(SCALAR distance);
	void MoveRight		(SCALAR distance);
	void LookUp			(SCALAR angle);
	void LookDown		(SCALAR angle);
	void LookRight		(SCALAR angle);
	void LookLeft		(SCALAR angle);

public:
	PlayerController(void);
	~PlayerController(void);
};

#endif