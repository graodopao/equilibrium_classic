#define WEB_EXPORT
#ifdef WEB_EXPORT
#include <emscripten.h>
#endif
#include "nashira/game_manager.h"
using namespace nashira;

int main(int argc, char* args[])
{
	GameManager* game = GameManager::instance();

#ifndef WEB_EXPORT
	game->run();
#else
	emscripten_set_main_loop([]()
	{
		GameManager::instance()->run();
	}, 0, 1);
#endif

	GameManager::release();
	game = nullptr;

	return 0;
}