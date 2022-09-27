#include <stdio.h>
#include <SDL.h>
#include <stdbool.h>

int main(int argc, char* args[])
{
	//SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Could not init SDL: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_Window* window = SDL_CreateWindow(
		"Balance",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_OPENGL
	);

	SDL_GL_CreateContext(window);

	bool should_quit = false;


	while (!should_quit)
	{
		/*
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{

			switch (event.type)
			{
				case (SDL_QUIT):
					should_quit = true;
					break;
			}
		}
		*/
	}

	return 0;
}