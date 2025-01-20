#include "asset_manager.h"
using namespace nashira;

AssetManager* AssetManager::s_instance = nullptr;

AssetManager* AssetManager::instance()
{
	if (s_instance == nullptr)
	{
		s_instance = new AssetManager();
	}

	return s_instance;
}

void AssetManager::release()
{
	delete s_instance;
	s_instance = nullptr;
}

AssetManager::AssetManager() = default;

AssetManager::~AssetManager()
{
	for (const auto &[fst, snd] : m_textures)
	{
		if (snd != nullptr)
		{
			SDL_DestroyTexture(snd);
		}
	}
	m_textures.clear();

	for (const auto &[fst, snd] : m_text)
	{
		if (snd != nullptr)
		{
			SDL_DestroyTexture(snd);
		}
	}

	m_text.clear();

	for (const auto &[fst, snd] : m_fonts)
	{
		if (snd != nullptr)
		{
			TTF_CloseFont(snd);
		}
	}

	m_fonts.clear();

	for (const auto &[fst, snd] : m_music)
	{
		if (snd != nullptr)
		{
			Mix_FreeMusic(snd);
		}
	}

	m_music.clear();

	for (const auto &[fst, snd] : m_sfx)
	{
		if (snd != nullptr)
		{
			Mix_FreeChunk(snd);
		}
	}

	m_sfx.clear();
}

SDL_Texture* AssetManager::get_texture(const std::string &filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	if (m_textures[fullPath] == nullptr)
	{
		m_textures[fullPath] = Graphics::instance()->load_texture(fullPath);
	}

	return m_textures[fullPath];
}

TTF_Font* AssetManager::get_font(const std::string &filename, const int size)
{
	std::string full_path = SDL_GetBasePath();
	full_path.append("Assets/" + filename);
	const std::string key = full_path + static_cast<char>(size);

	if (m_fonts[key] == nullptr)
	{
		m_fonts[key] = TTF_OpenFont(full_path.c_str(), size);

		if (m_fonts[key] == nullptr)
		{
			printf("Font loading error: Font-%s Error-%s\n", filename.c_str(), TTF_GetError());
		}
	}

	return m_fonts[key];
}

SDL_Texture* AssetManager::get_text(const std::string &text, const std::string &filename, const int size, const SDL_Color color)
{
	TTF_Font* font = get_font(filename, size);

	const std::string key = text + filename + static_cast<char>(size) + static_cast<char>(color.r) + static_cast<char>(color.g) + static_cast<char>(color.b);
	
	if (m_text[key] == nullptr)
	{
		m_text[key] = Graphics::instance()->create_text_texture(font, text, color);
	}

	return m_text[key];
}

Mix_Music* AssetManager::get_music(const std::string &filename)
{
	std::string fullPath = SDL_GetBasePath();

	fullPath.append("Assets/" + filename);

	if (m_music[fullPath] == nullptr)
	{
		m_music[fullPath] = Mix_LoadMUS(fullPath.c_str());
		if (m_music[fullPath] == nullptr)
		{
			printf("Music loading error: Path:%s - Error:%s\n", fullPath.c_str(), Mix_GetError());
		}
	}

	return m_music[fullPath];
}

Mix_Chunk* AssetManager::get_sfx(const std::string &filename)
{
	std::string fullPath = SDL_GetBasePath();

	fullPath.append("Assets/" + filename);

	if (m_sfx[fullPath] == nullptr)
	{
		m_sfx[fullPath] = Mix_LoadWAV(fullPath.c_str());

		if (m_sfx[fullPath] == nullptr)
		{
			printf("Failed on load sound effect at path %s, error %s\n", fullPath.c_str(), Mix_GetError());
		}
	}

	return m_sfx[fullPath];
}