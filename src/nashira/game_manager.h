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
		static GameManager* sInstance;

		const int FRAME_RATE = 120;

		bool mQuit;
		Graphics* mGraphics;
		AssetManager* mAssetManager;
		InputManager* mInputManager;
		AudioManager* mAudioManager;

		Timer* mTimer;

		SDL_Event mEvents;

		Texture* mButtonOne;
		Texture* mButtonOnePressed;
		Texture* mButtonTwo;
		Texture* mButtonTwoPressed;
		Texture* mMiddlePole;
		Texture* mPlate;
		Texture* mBlack;
		Texture* gameOverText;

		std::vector<Texture*> lightDotsRight;
		std::vector<Texture*> lightDotsLeft;
		std::vector<Texture*> particles;


		Texture* mScore;
		Texture* playerScore;

		Texture* mLights;

		std::vector<Texture*> constructions;

		float buttonHeight = Graphics::SCREEN_HEIGHT * 0.95f;
		float platformAngle = 0.0f;

		float platformWeight = 0.0f;
		float balanceChangeForce = 8.0f;

		float buttonPressTimer = 30.0f;
		float buttonPressTick = 0.0f;

		int max_chances = 26;
		int current_score = 0;

		int objectives_terminated = 0;

		bool finishedRound = false;
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