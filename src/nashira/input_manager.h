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

		static InputManager* s_instance;


		Uint8* m_prev_keyboard_state;
		const Uint8* m_keyboard_state;
		int m_key_length;

		Uint32 m_prev_mouse_state;
		Uint32 m_mouse_state;

		int m_mouse_x_pos;
		int m_mouse_y_pos;

	public:

		static InputManager* instance();
		static void release();

		bool key_down(SDL_Scancode scan_code) const;
		bool key_pressed(SDL_Scancode scan_code) const;
		bool key_released(SDL_Scancode scan_code) const;

		bool mouse_button_down(MOUSE_BUTTONS button) const;
		bool mouse_button_pressed(MOUSE_BUTTONS button) const;
		bool mouse_button_released(MOUSE_BUTTONS button) const;

		bool mouse_is_in_area(int x1, int y1, int x2, int y2) const;

		Vector2 mouse_get_pos() const;

		void update_previous_input();

		void update();

	private:

		InputManager();
		~InputManager();
	};
}

