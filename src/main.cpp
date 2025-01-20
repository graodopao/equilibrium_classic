#include "nashira/game_manager.h"
using namespace nashira;

int main(int argc, char* args[])
{
	GameManager* game = GameManager::instance();

	game->run();

	GameManager::release();
	game = NULL;

	return 0;
}