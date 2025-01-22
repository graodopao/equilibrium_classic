#include "input_manager.h"
using namespace nashira;

InputManager* InputManager::s_instance = nullptr;

InputManager* InputManager::instance()
{
	if (s_instance == nullptr)
	{
		s_instance = new InputManager();
	}

	return s_instance;
}

void InputManager::release()
{
	delete s_instance;
	s_instance = nullptr;
}

bool InputManager::key_down(const SDL_Scancode scan_code) const {
	return m_keyboard_state[scan_code];
}

bool InputManager::key_pressed(const SDL_Scancode scan_code) const {
	return !m_prev_keyboard_state[scan_code] && m_keyboard_state[scan_code];
}

bool InputManager::key_released(const SDL_Scancode scan_code) const {
	return m_prev_keyboard_state[scan_code] && !m_keyboard_state[scan_code];
}

Vector2 InputManager::mouse_get_pos() const {
	return {static_cast<float>(m_mouse_x_pos), static_cast<float>(m_mouse_y_pos)};
}

bool InputManager::mouse_button_down(const MOUSE_BUTTONS button) const {
	Uint32 mask = 0;

	switch (button)
	{
	case (left):
		mask = SDL_BUTTON_LMASK;
		break;
	case (middle):
		mask = SDL_BUTTON_MMASK;
		break;
	case(right):
		mask = SDL_BUTTON_RMASK;
		break;
	case (back):
		mask = SDL_BUTTON_X1MASK;
		break;
	case (forward):
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (m_mouse_state & mask);
}


bool InputManager::mouse_button_pressed(const MOUSE_BUTTONS button) const {
	Uint32 mask = 0;

	switch (button)
	{

	case (left):
		mask = SDL_BUTTON_LMASK;
		break;

	case(right):
		mask = SDL_BUTTON_RMASK;
		break;

	case (middle):
		mask = SDL_BUTTON_MMASK;
		break;

	case (back):
		mask = SDL_BUTTON_X1MASK;
		break;

	case (forward):
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return !(m_prev_mouse_state & mask) && (m_mouse_state & mask);
}


bool InputManager::mouse_button_released(const MOUSE_BUTTONS button) const {
	Uint32 mask = 0;

	switch (button)
	{

	case (left):
		mask = SDL_BUTTON_LMASK;
		break;

	case(right):
		mask = SDL_BUTTON_RMASK;
		break;

	case (middle):
		mask = SDL_BUTTON_MMASK;
		break;

	case (back):
		mask = SDL_BUTTON_X1MASK;
		break;

	case (forward):
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (m_prev_mouse_state & mask) && !(m_mouse_state & mask);
}

bool InputManager::mouse_is_in_area(const int x1, const int y1, const int x2, const int y2) const {
	Vector2 pos = mouse_get_pos();

	return (pos.x >= x1 && pos.y >= y1 && pos.x <= x2 && pos.y <= y2);
}

void InputManager::update()
{
	m_mouse_state = SDL_GetMouseState(&m_mouse_x_pos, &m_mouse_y_pos);
}

void InputManager::update_previous_input()
{
	memcpy(m_prev_keyboard_state, m_keyboard_state, m_key_length);
	m_prev_mouse_state = m_mouse_state;
}

InputManager::InputManager(): m_prev_mouse_state(0), m_mouse_state(0), m_mouse_x_pos(0), m_mouse_y_pos(0) {
	m_keyboard_state = SDL_GetKeyboardState(&m_key_length);
	m_prev_keyboard_state = new Uint8[m_key_length];
	memcpy(m_prev_keyboard_state, m_keyboard_state, m_key_length);
}

InputManager::~InputManager()
{
	delete[] m_prev_keyboard_state;
	m_prev_keyboard_state = nullptr;
}
