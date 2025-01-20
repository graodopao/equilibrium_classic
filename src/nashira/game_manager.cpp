#include "game_manager.h"
using namespace nashira;

GameManager* GameManager::sInstance = NULL;

GameManager* GameManager::instance()
{
	if (sInstance == NULL)
	{
		sInstance = new GameManager();
	}

	return sInstance;
}

void GameManager::release()
{
	delete sInstance;
	sInstance = NULL;
}

GameManager::GameManager()
{
	mQuit = false;

	mGraphics = Graphics::instance();

	if (!Graphics::initialized)
	{
		mQuit = true;
	}

	mAssetManager = AssetManager::instance();

	mInputManager = InputManager::instance();

	mAudioManager = AudioManager::instance();

	mTimer = Timer::instance();

	std::string s = std::to_string(completed_objectives);
	s.append("/");
	s.append(std::to_string(current_objective));

	mScore = new Texture(s, "Simplifica.ttf", 50, {255, 255, 255});
	mScore->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.2));

	gameOverText = new Texture("PRESS SPACE TO RETRY", "Simplifica.ttf", 100, {255, 255, 255});
	gameOverText->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));
	gameOverText->set_alpha(0);

	playerScore = new Texture("0", "Simplifica.ttf", 20, {255, 255, 255});
	playerScore->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.1));

	mButtonOne = new Texture("ButtonFlip.png", 0, 0, 204, 463);
	mButtonOne->set_position(Vector2(m_button_one_x_pos, buttonHeight));

	mButtonOnePressed = new Texture("ButtonFlippressed.png", 0, 0, 204, 463);
	mButtonOnePressed->set_position(Vector2(m_button_one_x_pos, buttonHeight));

	mButtonTwo = new Texture("Button.png", 0, 0, 204, 463);
	mButtonTwo->set_position(Vector2(m_button_two_x_pos, buttonHeight));

	mButtonTwoPressed = new Texture("Buttonpressed.png", 0, 0, 204, 463);
	mButtonTwoPressed->set_position(Vector2(m_button_two_x_pos, buttonHeight));

	mMiddlePole = new Texture("Middle pole.png", 0, 0, 25, 360);
	mMiddlePole->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.85f));

	mPlate = new Texture("Plate.png", 0, 0, 600, 25);
	mPlate->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2 + 85));

	mBlack = new Texture("Black.png", 0, 0, 1280, 720);
	mBlack->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	mLights = new Texture("Lights.png", 0, 0, 1280, 720);
	mLights->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	srand(time(NULL));

	for (int i = 0; i < 26; i++)
	{
		Texture* temp = new Texture("Lightdot.png", 0, 0, 5, 5);
		temp->set_position(Vector2(Graphics::SCREEN_WIDTH / 2 + 42 + (10 * i), Graphics::SCREEN_HEIGHT / 2 + 90));
		temp->parent(mPlate);

		lightDotsRight.push_back(temp);
	}

	for (int i = 0; i < 26; i++)
	{
		Texture* temp = new Texture("Lightdot.png", 0, 0, 5, 5);
		temp->set_position(Vector2(Graphics::SCREEN_WIDTH / 2 - 42 - (10 * i), Graphics::SCREEN_HEIGHT / 2 + 90));
		temp->parent(mPlate);

		lightDotsLeft.push_back(temp);
	}

	for (int i = 0; i < 100; i++)
	{
		int _x = rand() % 1280 + 1;
		int _y = rand() % 720 + 1;

		Texture* temp = new Texture("Particle.png", 0, 0, 5, 5);

		temp->set_alpha(100);
		temp->set_position(Vector2(_x, _y));

		particles.push_back(temp);
	}

	new_level();

	mAudioManager->play_music("Background.wav");

}

GameManager::~GameManager()
{
	AssetManager::release();
	mAssetManager = NULL;

	Graphics::release();
	mGraphics = NULL;

	Timer::release();
	mTimer = NULL;

	InputManager::release();
	mInputManager = NULL;

	AudioManager::release();
	mAudioManager = NULL;

	delete mButtonOne;
	mButtonOne = NULL;

	delete mButtonOnePressed;
	mButtonOnePressed = NULL;

	delete mButtonTwo;
	mButtonTwo = NULL;

	delete mButtonTwoPressed;
	mButtonTwoPressed = NULL;

	delete mMiddlePole;
	mMiddlePole = NULL;

	delete mPlate;
	mPlate = NULL;

	delete mScore;
	mScore = NULL;

	delete playerScore;
	playerScore = NULL;

	delete mLights;
	mLights = NULL;

	delete gameOverText;
	gameOverText = NULL;

	delete mBlack;
	mBlack = NULL;

	for (Texture* i : constructions)
	{
		delete i;
		i = NULL;
	}
	constructions.clear();

	for (Texture* i : lightDotsRight)
	{
		delete i;
		i = NULL;
	}
	lightDotsRight.clear();

	for (Texture* i : lightDotsLeft)
	{
		delete i;
		i = NULL;
	}
	lightDotsLeft.clear();

	for (Texture* i : particles)
	{
		delete i;
		i = NULL;
	}
	particles.clear();
}


void GameManager::early_update()
{
	mTimer->reset();
	mInputManager->update();
}


void GameManager::update()
{
	for (Texture* i : particles)
	{
		i->particle_update(mTimer->delta_time());
	}

	button_one_pressed = false;
	button_two_pressed = false;

	if (mInputManager->mouse_button_down(InputManager::left))
	{

		bool isPressed = mInputManager->mouse_button_pressed(InputManager::left);

		if (mInputManager->mouse_is_in_area(m_button_one_x_pos - mButtonOne->get_width() / 2, buttonHeight - mButtonOne->get_height() / 2, m_button_one_x_pos + mButtonOne->get_width() / 2, buttonHeight + mButtonOne->get_height() / 2))
		{
			if (isPressed)
			{
				mAudioManager->play_sfx("Button.wav");
			}

			button_one_pressed = true;
		}

		// Button two
		if (mInputManager->mouse_is_in_area(m_button_two_x_pos - mButtonTwo->get_width() / 2, buttonHeight - mButtonTwo->get_height() / 2, m_button_two_x_pos + mButtonTwo->get_width() / 2, buttonHeight + mButtonTwo->get_height() / 2))
		{
			if (isPressed)
			{
				mAudioManager->play_sfx("Button.wav");
			}

			button_two_pressed = true;
		}

		if (buttonPressTick >= buttonPressTimer)
		{
			buttonPressTick = 0;

			// Button one
			if (mInputManager->mouse_is_in_area(m_button_one_x_pos - mButtonOne->get_width() / 2, buttonHeight - mButtonOne->get_height() / 2, m_button_one_x_pos + mButtonOne->get_width() / 2, buttonHeight + mButtonOne->get_height() / 2))
			{
				platformWeight -= balanceChangeForce;
			}

			// Button two
			if (mInputManager->mouse_is_in_area(m_button_two_x_pos - mButtonTwo->get_width() / 2, buttonHeight - mButtonTwo->get_height() / 2, m_button_two_x_pos + mButtonTwo->get_width() / 2, buttonHeight + mButtonTwo->get_height() / 2))
			{
				platformWeight += balanceChangeForce;
			}
		}
		else
		{
			buttonPressTick += 240 * mTimer->delta_time();
		}
	}

	float _rx = mPlate->rotate_point(mPlate->get_position(), mPlate->get_width() / 2, mPlate->Rotation());
	float _lx = mPlate->rotate_point(mPlate->get_position(), -mPlate->get_width() / 2, mPlate->Rotation());

	m_weight_balance = ZERO;

	if (!finishedRound && !lost)
	{
		for (Texture* i : constructions)
		{
			float resultWeight = i->building_update(mTimer->delta_time(), mPlate->mRotation, _lx, _rx, completed_objectives, objectives_terminated);

			float _x = i->get_position().x;

			if (i->get_position().x > Graphics::SCREEN_WIDTH / 2)
			{
				float result = (_x / _rx - 0.5f) / 6;

				m_weight_balance.y += resultWeight * result;
			}
			else
			{
				float result = (1 - (_x / _lx - 1)) / 6;

				m_weight_balance.x += resultWeight * result;
			}
		}
	}

	if (previous_completed_objectives != completed_objectives)
	{

		if (completed_objectives > previous_completed_objectives)
		{
			delete playerScore;
			playerScore = NULL;

			current_score += 100 * (completed_objectives - previous_completed_objectives);

			std::string s = std::to_string(current_score);

			playerScore = new Texture(s, "Simplifica.ttf", 20, { 255, 255, 255 });
			playerScore->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.1));
		}
		else
		{
			max_chances--;
		}

		previous_completed_objectives = completed_objectives;
		update_score();
	}

	float finalResult = (m_weight_balance.y - m_weight_balance.x) + platformWeight;

	if (!finishedRound && !lost)
	{
		mPlate->Rotate(finalResult * mTimer->delta_time());
	}

	mPlate->mRotation = SDL_clamp(mPlate->mRotation, -60, 60);

	if (objectives_terminated >= current_objective)
	{
		finishedRound = true;
	}

	alpha += (((finishedRound || lost) ? 250 : 0 - alpha) / 1.5) * mTimer->delta_time();
	alpha = SDL_clamp(alpha, 0, 255);

	mBlack->set_alpha(alpha);
	gameOverText->set_alpha(alpha);

	if (alpha >= 250 && finishedRound)
	{
		new_level();
	}

	if (max_chances <= 0)
	{
		lost = true;
	}

	if (lost && mInputManager->key_pressed(SDL_SCANCODE_SPACE))
	{
		level = 0;
		max_chances = 26;
		current_score = 0;
		lost = false;

		new_level();
	}
}

void GameManager::new_level()
{

	level++;

	current_objective = level * 2;

	objectives_terminated = 0;
	completed_objectives = 0;
	previous_completed_objectives = 0;

	update_score();

	finishedRound = 0;
	mPlate->mRotation = 0;

	platformWeight = 0;

	for (Texture* i : constructions)
	{
		delete i;
		i = NULL;
	}
	constructions.clear();

	for (int i = 0; i < current_objective; i++)
	{
		int _x = rand() % 500 + 1;

		int b = rand() % 4 + 1;

		std::string name = "Building";
		name.append(std::to_string(b));

		Texture* frameTemp = new Texture(name + "-frame.png", 0, 0, 50, 5);
		frameTemp->set_position(Vector2(Graphics::SCREEN_WIDTH / 2 + _x - 250, Graphics::SCREEN_HEIGHT / 2 + 70));
		frameTemp->parent(mPlate);

		Texture* temp = new Texture(name + ".png", 0, 0, 50, 0);
		temp->set_position(Vector2(Graphics::SCREEN_WIDTH / 2 + _x - 250, Graphics::SCREEN_HEIGHT / 2 + 70));

		float cooldown = rand() % 500 + 1;
		printf("%f\n", cooldown);

		temp->set_building(frameTemp, 50, false, cooldown);
		temp->parent(mPlate);

		constructions.push_back(temp);
	}
}

void GameManager::update_score()
{
	delete mScore;
	mScore = NULL;

	std::string s = std::to_string(completed_objectives);
	s.append("/");
	s.append(std::to_string(current_objective));

	mScore = new Texture(s, "Simplifica.ttf", 50, { 255, 255, 255 });
	mScore->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.2));
}

void GameManager::late_update()
{
	mInputManager->update_previous_input();
}

void GameManager::render()
{

	mGraphics->clear_back_buffer();


	for (Texture* i : particles)
	{
		i->render();
	}

	if (!button_one_pressed)
	{
		mButtonOne->render();
	}
	else
	{
		mButtonOnePressed->render();
	}

	if (!button_two_pressed)
	{
		mButtonTwo->render();
	}
	else
	{
		mButtonTwoPressed->render();
	}

	mPlate->render();
	mMiddlePole->render();

	int count = 0;

	for (Texture* i : constructions)
	{
		i->render();
	}

	count = 0;
	for (Texture* i : lightDotsRight)
	{
		if (count < max_chances)
		{
			i->render();
			count++;
		}
	}

	count = 0;
	for (Texture* i : lightDotsLeft)
	{
		if (count < max_chances)
		{
			i->render();
			count++;
		}
	}

	mScore->render();
	playerScore->render();

	mLights->update();
	mLights->render();

	mBlack->render();

	if (lost)
	{
		gameOverText->render();
	}

	mGraphics->render();
}

void GameManager::run()
{
	while (!mQuit)
	{
		mTimer->update();

		while (SDL_PollEvent(&mEvents) != 0)
		{
			if (mEvents.type == SDL_QUIT)
			{
				mQuit = true;
			}
		}

		if (mTimer->delta_time() >= 1.0f / FRAME_RATE)
		{
			early_update();
			update();
			late_update();
			render();
		}
	}
}
