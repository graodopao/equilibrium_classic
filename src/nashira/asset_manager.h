#pragma once
#include "graphics.h"
#include <SDL_mixer.h>
#include "map"

namespace nashira {
	class AssetManager
	{
	private:
		static AssetManager* s_instance;

		std::map<std::string, SDL_Texture*> m_textures;
		std::map<std::string, SDL_Texture*> m_text;
		std::map<std::string, TTF_Font*> m_fonts;
		std::map<std::string, Mix_Music*> m_music;
		std::map<std::string, Mix_Chunk*> m_sfx;

	public:

		static AssetManager* instance();
		static void release();

		SDL_Texture* get_texture(const std::string &filename);
		SDL_Texture* get_text(const std::string &text, const std::string &filename, int size, SDL_Color color);

		Mix_Music* get_music(const std::string &filename);
		Mix_Chunk* get_sfx(const std::string &filename);

	private:

		AssetManager();
		~AssetManager();

		TTF_Font* get_font(const std::string &filename, int size);
	};
}