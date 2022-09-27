#include "InputManager.h"

InputManager* InputManager::sInstance = NULL;

InputManager* InputManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new InputManager();
	}

	return sInstance;
}

void InputManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

bool InputManager::KeyDown(SDL_Scancode scanCode)
{
	return mKeyboardState[scanCode];
}

bool InputManager::KeyPressed(SDL_Scancode scanCode)
{
	return !mPrevKeyboardState[scanCode] && mKeyboardState[scanCode];
}

bool InputManager::KeyReleased(SDL_Scancode scanCode)
{
	return mPrevKeyboardState[scanCode] && !mKeyboardState[scanCode];
}

Vector2 InputManager::MouseGetPos()
{
	return Vector2((float)mMouseXPos, (float)mMouseYPos);
}

bool InputManager::MouseButtonDown(MOUSE_BUTTONS button)
{
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

	return (mMouseState & mask);
}


bool InputManager::MouseButtonPressed(MOUSE_BUTTONS button)
{
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

	return !(mPrevMouseState & mask) && (mMouseState & mask);
}


bool InputManager::MouseButtonReleased(MOUSE_BUTTONS button)
{
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

	return (mPrevMouseState & mask) && !(mMouseState & mask);
}

bool InputManager::MouseIsInArea(int x1, int y1, int x2, int y2)
{
	Vector2 pos = MouseGetPos();

	return (pos.x >= x1 && pos.y >= y1 && pos.x <= x2 && pos.y <= y2);
}

void InputManager::Update()
{
	mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
}

void InputManager::UpdatePreviousInput()
{
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
	mPrevMouseState = mMouseState;
}

InputManager::InputManager()
{
	mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
	mPrevKeyboardState = new Uint8[mKeyLength];
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
}

InputManager::~InputManager()
{
	delete[] mPrevKeyboardState;
	mPrevKeyboardState = NULL;
}