#pragma once

#include "AnimatedTexture.h"
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

		void updateScore();

		int level = 0;
		int current_objective = 5;

		int completed_objectives = 0;
		int previous_completed_objectives = 0;

		float alpha = 0.0f;

		bool buttonOnePressed = false;
		bool buttonTwoPressed = false;


		float mButtonOneXPos = Graphics::SCREEN_WIDTH * 0.15f;
		float mButtonTwoXPos = Graphics::SCREEN_WIDTH * 0.85f;

		Vector2 mWeightBalance = VEC2_ZERO;

		static GameManager* Instance();
		static void Release();

		void Run();

	private:
		GameManager();
		~GameManager();

		void newLevel();

		void EarlyUpdate();
		void Update();
		void LateUpdate();

		void Render();
	};

}