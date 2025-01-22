#include "graphics.h"
#include <SDL_image.h>
using namespace nashira;


Graphics* Graphics::s_instance = nullptr;
bool Graphics::s_initialized = false;

Graphics* Graphics::instance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Graphics;
	}

	return s_instance;
}

void Graphics::release()
{
	delete s_instance;
	s_instance = nullptr;

	s_initialized = false;
}

bool Graphics::initialized()
{
	return s_initialized;
}

Graphics::Graphics()
{
	m_back_buffer = nullptr;
	s_initialized = init();
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(m_window);
	m_window = nullptr;
	
	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL_InitializationError: %s\n", SDL_GetError());
		return false;
	}

	m_window = SDL_CreateWindow("The Balance", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_window == nullptr)
	{
		printf("SDL_WindowCreationError: %s\n", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == nullptr)
	{
		printf("Renderer failed to create: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(mRenderer, 2, 8, 13, 255);

	const int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		printf("IMG Initialization error: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("TTF initialization error: %s\n", TTF_GetError());
		return false;
	}

	m_back_buffer = SDL_GetWindowSurface(m_window);
	return true;
}

SDL_Texture* Graphics::load_texture(const std::string &path) const {
	SDL_Texture* tex = nullptr;

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr)
	{
		printf("Image failed to load: Path: (%s) - Error: %s\n", path.c_str(), IMG_GetError());

		SDL_FreeSurface(surface);
		return tex;
	}

	tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (surface == nullptr)
	{
		printf("Image failed to load from surface: Path: (%s) - Error: %s\n", path.c_str(), IMG_GetError());

		SDL_FreeSurface(surface);
		return tex;
	}
	SDL_FreeSurface(surface);
	
	return tex;
}

SDL_Texture* Graphics::create_text_texture(TTF_Font* font, const std::string &text, const SDL_Color color) const {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

	if (surface == nullptr)
	{
		printf("Text render error: %s\n", TTF_GetError());
		SDL_FreeSurface(surface);
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);

	if (tex == nullptr)
	{
		printf("Text texture creation error: %s\n", SDL_GetError());
		SDL_FreeSurface(surface);
		return nullptr;
	}

	SDL_FreeSurface(surface);
	return tex;
}

void Graphics::clear_back_buffer() const {
	SDL_RenderClear(mRenderer);
}

void Graphics::draw_texture(SDL_Texture* tex, const SDL_Rect* clip, const SDL_Rect* rend, const float angle, const SDL_RendererFlip flip) const {
	SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, nullptr, flip);
}

void Graphics::render() const {
	SDL_RenderPresent(mRenderer);
}
