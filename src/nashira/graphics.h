#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

namespace nashira {
	class Graphics
	{
	public:
		static constexpr int SCREEN_WIDTH = 1280;
		static constexpr int SCREEN_HEIGHT = 720;

	private:

		static Graphics* s_instance;
		static bool s_initialized;

		SDL_Window* m_window;
		SDL_Surface* m_back_buffer;

		SDL_Renderer* mRenderer;


	public:
		static Graphics* instance();
		static void release();
		static bool initialized();

		SDL_Texture* load_texture(std::string path);
		SDL_Texture* create_text_texture(TTF_Font* font, std::string text, SDL_Color color);

		void clear_back_buffer();

		void draw_texture(SDL_Texture* tex, SDL_Rect* clip = nullptr, SDL_Rect* rend = nullptr, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

		void render();

	private:

		Graphics();
		~Graphics();

		bool init();
	};
}
