#pragma once

#include "animated_texture.h"
#include "input_manager.h"
#include "audio_manager.h"
#include <vector>
#include <time.h>

namespace nashira {
	class GameManager
	{
	private:
		static GameManager* s_instance;

		const int FRAME_RATE = 120;

		bool m_quit;
		Graphics* m_graphics;
		AssetManager* m_asset_manager;
		InputManager* m_input_manager;
		AudioManager* m_audio_manager;

		Timer* m_timer;

		SDL_Event m_events{};

		Texture* m_button_one;
		Texture* m_button_one_pressed;
		Texture* m_button_two;
		Texture* m_button_two_pressed;
		Texture* m_middle_pole;
		Texture* m_plate;
		Texture* m_black;
		Texture* game_over_text;

		std::vector<Texture*> light_dots_right;
		std::vector<Texture*> light_dots_left;
		std::vector<Texture*> particles;


		Texture* m_score;
		Texture* player_score;

		Texture* m_lights;

		std::vector<Texture*> constructions;

		float button_height = Graphics::SCREEN_HEIGHT * 0.95f;
		float platform_angle = 0.0f;

		float platform_weight = 0.0f;
		float balance_change_force = 8.0f;

		float button_press_timer = 30.0f;
		float button_press_tick = 0.0f;

		int max_chances = 26;
		int current_score = 0;

		int objectives_terminated = 0;

		bool finished_round = false;
		bool lost = false;

	public:

		void update_score();

		int level = 0;
		int current_objective = 5;

		int completed_objectives = 0;
		int previous_completed_objectives = 0;

		float alpha = 0.0f;

		bool button_one_pressed = false;
		bool button_two_pressed = false;


		float m_button_one_x_pos = Graphics::SCREEN_WIDTH * 0.15f;
		float m_button_two_x_pos = Graphics::SCREEN_WIDTH * 0.85f;

		Vector2 m_weight_balance = ZERO;

		static GameManager* instance();
		static void release();

		void run();

	private:
		GameManager();
		~GameManager();

		void new_level();

		void early_update();
		void update();
		void late_update();

		void render();
	};

}