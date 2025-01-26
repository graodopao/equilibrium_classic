#include "nashira/src/game_manager.h"
using namespace nashira;

int main(int argc, char* args[])
{
	GameManager* game = GameManager::instance();

	game->run();

	GameManager::release();
	game = nullptr;

	return 0;
}