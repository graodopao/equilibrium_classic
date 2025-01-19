#pragma once
#include <SDL.h>
#include <string.h>
#include "math_helper.h"

namespace nashira {
	class InputManager
	{

	public:

		enum MOUSE_BUTTONS
		{
			left,
			right,
			middle,
			back,
			forward
		};

	private:

		static InputManager* sInstance;


		Uint8* mPrevKeyboardState;
		const Uint8* mKeyboardState;
		int mKeyLength;

		Uint32 mPrevMouseState;
		Uint32 mMouseState;

		int mMouseXPos;
		int mMouseYPos;

	public:

		static InputManager* Instance();
		static void Release();

		bool KeyDown(SDL_Scancode scanCode);
		bool KeyPressed(SDL_Scancode scanCode);
		bool KeyReleased(SDL_Scancode scanCode);

		bool MouseButtonDown(MOUSE_BUTTONS button);
		bool MouseButtonPressed(MOUSE_BUTTONS button);
		bool MouseButtonReleased(MOUSE_BUTTONS button);

		bool MouseIsInArea(int x1, int y1, int x2, int y2);

		Vector2 MouseGetPos();

		void UpdatePreviousInput();

		void Update();

	private:

		InputManager();
		~InputManager();
	};
}

