#include "game_manager.h"
using namespace nashira;

GameManager* GameManager::s_instance = nullptr;

GameManager* GameManager::instance()
{
	if (s_instance == nullptr)
	{
		s_instance = new GameManager();
	}

	return s_instance;
}

void GameManager::release()
{
	delete s_instance;
	s_instance = nullptr;
}

GameManager::GameManager()
{
	m_quit = false;

	m_graphics = Graphics::instance();

	if (!Graphics::initialized)
	{
		m_quit = true;
	}

	m_asset_manager = AssetManager::instance();

	m_input_manager = InputManager::instance();

	m_audio_manager = AudioManager::instance();

	m_timer = Timer::instance();

	std::string s = std::to_string(completed_objectives);
	s.append("/");
	s.append(std::to_string(current_objective));

	m_score = new Texture(s, "Simplifica.ttf", 50, {255, 255, 255});
	m_score->set_position(Vector2(Graphics::SCREEN_WIDTH / 2.0, Graphics::SCREEN_HEIGHT * 0.2));

	game_over_text = new Texture("PRESS SPACE TO RETRY", "Simplifica.ttf", 100, {255, 255, 255});
	game_over_text->set_position(Vector2(Graphics::SCREEN_WIDTH / 2.0, Graphics::SCREEN_HEIGHT / 2.0));
	game_over_text->set_alpha(0);

	player_score = new Texture("0", "Simplifica.ttf", 20, {255, 255, 255});
	player_score->set_position(Vector2(Graphics::SCREEN_WIDTH / 2.0, Graphics::SCREEN_HEIGHT * 0.1));

	m_button_one = new Texture("ButtonFlip.png", 0, 0, 204, 463);
	m_button_one->set_position(Vector2(m_button_one_x_pos, button_height));

	m_button_one_pressed = new Texture("ButtonFlippressed.png", 0, 0, 204, 463);
	m_button_one_pressed->set_position(Vector2(m_button_one_x_pos, button_height));

	m_button_two = new Texture("Button.png", 0, 0, 204, 463);
	m_button_two->set_position(Vector2(m_button_two_x_pos, button_height));

	m_button_two_pressed = new Texture("Buttonpressed.png", 0, 0, 204, 463);
	m_button_two_pressed->set_position(Vector2(m_button_two_x_pos, button_height));

	m_middle_pole = new Texture("Middle pole.png", 0, 0, 25, 360);
	m_middle_pole->set_position(Vector2(Graphics::SCREEN_WIDTH / 2.0, Graphics::SCREEN_HEIGHT * 0.85f));

	m_plate = new Texture("Plate.png", 0, 0, 600, 25);
	m_plate->set_position(Vector2(Graphics::SCREEN_WIDTH / 2.0, Graphics::SCREEN_HEIGHT / 2 + 85));

	m_black = new Texture("Black.png", 0, 0, 1280, 720);
	m_black->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	m_lights = new Texture("Lights.png", 0, 0, 1280, 720);
	m_lights->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	srand(time(NULL));

	for (int i = 0; i < 26; i++)
	{
		Texture* temp = new Texture("Lightdot.png", 0, 0, 5, 5);
		temp->set_position(Vector2(Graphics::SCREEN_WIDTH / 2 + 42 + (10 * i), Graphics::SCREEN_HEIGHT / 2 + 90));
		temp->parent(m_plate);

		light_dots_right.push_back(temp);
	}

	for (int i = 0; i < 26; i++)
	{
		Texture* temp = new Texture("Lightdot.png", 0, 0, 5, 5);
		temp->set_position(Vector2(Graphics::SCREEN_WIDTH / 2 - 42 - (10 * i), Graphics::SCREEN_HEIGHT / 2 + 90));
		temp->parent(m_plate);

		light_dots_left.push_back(temp);
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

	m_audio_manager->play_music("Background.wav");

}

GameManager::~GameManager()
{
	AssetManager::release();
	m_asset_manager = nullptr;

	Graphics::release();
	m_graphics = nullptr;

	Timer::release();
	m_timer = nullptr;

	InputManager::release();
	m_input_manager = nullptr;

	AudioManager::release();
	m_audio_manager = nullptr;

	delete m_button_one;
	m_button_one = nullptr;

	delete m_button_one_pressed;
	m_button_one_pressed = nullptr;

	delete m_button_two;
	m_button_two = nullptr;

	delete m_button_two_pressed;
	m_button_two_pressed = nullptr;

	delete m_middle_pole;
	m_middle_pole = nullptr;

	delete m_plate;
	m_plate = nullptr;

	delete m_score;
	m_score = nullptr;

	delete player_score;
	player_score = nullptr;

	delete m_lights;
	m_lights = nullptr;

	delete game_over_text;
	game_over_text = nullptr;

	delete m_black;
	m_black = nullptr;

	for (Texture* i : constructions)
	{
		delete i;
		i = nullptr;
	}
	constructions.clear();

	for (Texture* i : light_dots_right)
	{
		delete i;
		i = nullptr;
	}
	light_dots_right.clear();

	for (const Texture* i : light_dots_left)
	{
		delete i;
		i = nullptr;
	}
	light_dots_left.clear();

	for (const Texture* i : particles)
	{
		delete i;
		i = nullptr;
	}
	particles.clear();
}


void GameManager::early_update()
{
	m_timer->reset();
	m_input_manager->update();
}


void GameManager::update()
{
	for (Texture* i : particles)
	{
		i->particle_update(m_timer->delta_time());
	}

	button_one_pressed = false;
	button_two_pressed = false;

	if (m_input_manager->mouse_button_down(InputManager::left))
	{

		bool isPressed = m_input_manager->mouse_button_pressed(InputManager::left);

		if (m_input_manager->mouse_is_in_area(m_button_one_x_pos - m_button_one->get_width() / 2, button_height - m_button_one->get_height() / 2, m_button_one_x_pos + m_button_one->get_width() / 2, button_height + m_button_one->get_height() / 2))
		{
			if (isPressed)
			{
				m_audio_manager->play_sfx("Button.wav");
			}

			button_one_pressed = true;
		}

		// Button two
		if (m_input_manager->mouse_is_in_area(m_button_two_x_pos - m_button_two->get_width() / 2, button_height - m_button_two->get_height() / 2, m_button_two_x_pos + m_button_two->get_width() / 2, button_height + m_button_two->get_height() / 2))
		{
			if (isPressed)
			{
				m_audio_manager->play_sfx("Button.wav");
			}

			button_two_pressed = true;
		}

		if (button_press_tick >= button_press_timer)
		{
			button_press_tick = 0;

			// Button one
			if (m_input_manager->mouse_is_in_area(m_button_one_x_pos - m_button_one->get_width() / 2, button_height - m_button_one->get_height() / 2, m_button_one_x_pos + m_button_one->get_width() / 2, button_height + m_button_one->get_height() / 2))
			{
				platform_weight -= balance_change_force;
			}

			// Button two
			if (m_input_manager->mouse_is_in_area(m_button_two_x_pos - m_button_two->get_width() / 2, button_height - m_button_two->get_height() / 2, m_button_two_x_pos + m_button_two->get_width() / 2, button_height + m_button_two->get_height() / 2))
			{
				platform_weight += balance_change_force;
			}
		}
		else
		{
			button_press_tick += 240 * m_timer->delta_time();
		}
	}

	float _rx = m_plate->rotate_point(m_plate->get_position(), m_plate->get_width() / 2, m_plate->Rotation());
	float _lx = m_plate->rotate_point(m_plate->get_position(), -m_plate->get_width() / 2, m_plate->Rotation());

	m_weight_balance = ZERO;

	if (!finished_round && !lost)
	{
		for (Texture* i : constructions)
		{
			float resultWeight = i->building_update(m_timer->delta_time(), m_plate->m_rotation, _lx, _rx, completed_objectives, objectives_terminated);

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
			delete player_score;
			player_score = NULL;

			current_score += 100 * (completed_objectives - previous_completed_objectives);

			std::string s = std::to_string(current_score);

			player_score = new Texture(s, "Simplifica.ttf", 20, { 255, 255, 255 });
			player_score->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.1));
		}
		else
		{
			max_chances--;
		}

		previous_completed_objectives = completed_objectives;
		update_score();
	}

	float finalResult = (m_weight_balance.y - m_weight_balance.x) + platform_weight;

	if (!finished_round && !lost)
	{
		m_plate->Rotate(finalResult * m_timer->delta_time());
	}

	m_plate->m_rotation = SDL_clamp(m_plate->m_rotation, -60, 60);

	if (objectives_terminated >= current_objective)
	{
		finished_round = true;
	}

	alpha += (((finished_round || lost) ? 250 : 0 - alpha) / 1.5) * m_timer->delta_time();
	alpha = SDL_clamp(alpha, 0, 255);

	m_black->set_alpha(alpha);
	game_over_text->set_alpha(alpha);

	if (alpha >= 250 && finished_round)
	{
		new_level();
	}

	if (max_chances <= 0)
	{
		lost = true;
	}

	if (lost && m_input_manager->key_pressed(SDL_SCANCODE_SPACE))
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

	finished_round = 0;
	m_plate->m_rotation = 0;

	platform_weight = 0;

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
		frameTemp->parent(m_plate);

		Texture* temp = new Texture(name + ".png", 0, 0, 50, 0);
		temp->set_position(Vector2(Graphics::SCREEN_WIDTH / 2 + _x - 250, Graphics::SCREEN_HEIGHT / 2 + 70));

		float cooldown = rand() % 500 + 1;
		printf("%f\n", cooldown);

		temp->set_building(frameTemp, 50, false, cooldown);
		temp->parent(m_plate);

		constructions.push_back(temp);
	}
}

void GameManager::update_score()
{
	delete m_score;
	m_score = NULL;

	std::string s = std::to_string(completed_objectives);
	s.append("/");
	s.append(std::to_string(current_objective));

	m_score = new Texture(s, "Simplifica.ttf", 50, { 255, 255, 255 });
	m_score->set_position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.2));
}

void GameManager::late_update()
{
	m_input_manager->update_previous_input();
}

void GameManager::render()
{

	m_graphics->clear_back_buffer();


	for (Texture* i : particles)
	{
		i->render();
	}

	if (!button_one_pressed)
	{
		m_button_one->render();
	}
	else
	{
		m_button_one_pressed->render();
	}

	if (!button_two_pressed)
	{
		m_button_two->render();
	}
	else
	{
		m_button_two_pressed->render();
	}

	m_plate->render();
	m_middle_pole->render();

	int count = 0;

	for (Texture* i : constructions)
	{
		i->render();
	}

	count = 0;
	for (Texture* i : light_dots_right)
	{
		if (count < max_chances)
		{
			i->render();
			count++;
		}
	}

	count = 0;
	for (Texture* i : light_dots_left)
	{
		if (count < max_chances)
		{
			i->render();
			count++;
		}
	}

	m_score->render();
	player_score->render();

	m_lights->update();
	m_lights->render();

	m_black->render();

	if (lost)
	{
		game_over_text->render();
	}

	m_graphics->render();
}

void GameManager::run()
{
	while (!m_quit)
	{
		m_timer->update();

		while (SDL_PollEvent(&m_events) != 0)
		{
			if (m_events.type == SDL_QUIT)
			{
				m_quit = true;
			}
		}

		if (m_timer->delta_time() >= 1.0f / FRAME_RATE)
		{
			early_update();
			update();
			late_update();
			render();
		}
	}
}
