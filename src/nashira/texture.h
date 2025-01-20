#pragma once
#include "game_entity.h"
#include "timer.h"
#include "asset_manager.h"

namespace nashira {
	class Texture : public GameEntity
	{
	protected:
		SDL_Texture* m_tex;
		Texture* second_texture = nullptr;

		Graphics* m_graphics;
		Timer* m_timer = nullptr;

		int m_width;
		int m_height;

		bool m_clipped;
		SDL_Rect m_render_rect;
		SDL_Rect m_clip_rect;

		Uint8 alpha = 1;

		float rise_cooldown = 120.0f;
		float rise_tick = 0.0f;

		int* objective_variable = nullptr;

	public:
		static float rotate_point(Vector2 pos, float dist, float dir);

		explicit Texture(std::string filename);
		Texture(std::string filename, int x, int y, int w, int h);
		Texture(const std::string &text, const std::string &font_path, int size, SDL_Color);

		float building_update(float delta_time, float angle, float leftPoint, float rightPoint, int& objective, int& objective_term);
		void set_alpha(Uint8 alpha) const;

		void particle_update(float deltaTime);

		~Texture() override;

		[[nodiscard]] int get_width() const;
		[[nodiscard]] int get_height() const;

		void render() override;

		void rise(int amount, float cap);
		void decrease(int amount);

		void set_building(Texture* frameTexture, int maximumHeight, bool isFrame, float constructionCooldown);
		void building_demolish();

		[[nodiscard]] bool is_demolished() const;

	private:

		enum BUILDING_STATE
		{
			building,
			built,
			deconstruct,
			demolished,
			falling
		};

		BUILDING_STATE current_building_state = building;


		int max_height = 50;
		bool is_building = false;

		const float gravity = 10.0f;
		float vertical_speed = 0.0f;

		float particle_move_update = 60.0f;
		float particle_tick = 0;

		float horizontal_particle_move_update = 120.0f;
		float horizontal_particle_tick = 0;

		float building_idle_cooldown = 0.0f;
		float building_idle_tick = 0.0f;

	};
}

