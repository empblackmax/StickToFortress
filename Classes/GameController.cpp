#include "GameController.h"

GameController* GameController::instance;

GameController* GameController::getInstance()
{
	if (instance == NULL)
		instance = new GameController();
	return instance;
}

void GameController::clear()
{
	enemyVector.clear();
	bulletVector.clear();

}
