#include "GameManager.h";

GameManager* GameManager::sInstance = NULL;

GameManager* GameManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new GameManager();
	}

	return sInstance;
}

void GameManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

GameManager::GameManager()
{
	mQuit = false;
	
	mGraphics = Graphics::Instance();
	
	if (!Graphics::Initialized)
	{
		mQuit = true;
	}

	mAssetManager = AssetManager::Instance();

	mInputManager = InputManager::Instance();

	mAudioManager = AudioManager::Instance();

	mTimer = Timer::Instance();
	
	std::string s = std::to_string(completed_objectives);
	s.append("/");
	s.append(std::to_string(current_objective));
	
	mScore = new Texture(s, "Simplifica.ttf", 50, {255, 255, 255});
	mScore->Pos(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.2));

	gameOverText = new Texture("PRESS SPACE TO RETRY", "Simplifica.ttf", 100, {255, 255, 255});
	gameOverText->Pos(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));
	gameOverText->SetAlpha(0);

	playerScore = new Texture("0", "Simplifica.ttf", 20, {255, 255, 255});
	playerScore->Pos(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.1));
	
	mButtonOne = new Texture("ButtonFlip.png", 0, 0, 204, 463);
	mButtonOne->Pos(Vector2(mButtonOneXPos, buttonHeight));

	mButtonOnePressed = new Texture("ButtonFlippressed.png", 0, 0, 204, 463);
	mButtonOnePressed->Pos(Vector2(mButtonOneXPos, buttonHeight));

	mButtonTwo = new Texture("Button.png", 0, 0, 204, 463);
	mButtonTwo->Pos(Vector2(mButtonTwoXPos, buttonHeight));

	mButtonTwoPressed = new Texture("Buttonpressed.png", 0, 0, 204, 463);
	mButtonTwoPressed->Pos(Vector2(mButtonTwoXPos, buttonHeight));

	mMiddlePole = new Texture("Middle pole.png", 0, 0, 25, 360);
	mMiddlePole->Pos(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.85f));

	mPlate = new Texture("Plate.png", 0, 0, 600, 25);
	mPlate->Pos(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2 + 85));

	mBlack = new Texture("Black.png", 0, 0, 1280, 720);
	mBlack->Pos(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	mLights = new Texture("Lights.png", 0, 0, 1280, 720);
	mLights->Pos(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));
	
	srand(time(NULL));

	for (int i = 0; i < 26; i++)
	{
		Texture* temp = new Texture("Lightdot.png", 0, 0, 5, 5);
		temp->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + 42 + (10 * i), Graphics::SCREEN_HEIGHT / 2 + 90));
		temp->Parent(mPlate);

		lightDotsRight.push_back(temp);
	}

	for (int i = 0; i < 26; i++)
	{
		Texture* temp = new Texture("Lightdot.png", 0, 0, 5, 5);
		temp->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 - 42 - (10 * i), Graphics::SCREEN_HEIGHT / 2 + 90));
		temp->Parent(mPlate);

		lightDotsLeft.push_back(temp);
	}

	for (int i = 0; i < 100; i++)
	{
		int _x = rand() % 1280 + 1;
		int _y = rand() % 720 + 1;

		Texture* temp = new Texture("Particle.png", 0, 0, 5, 5);

		temp->SetAlpha(100);
		temp->Pos(Vector2(_x, _y));

		particles.push_back(temp);
	}

	newLevel();

	//mAudioManager->PlayMusic("Background.wav");

}

GameManager::~GameManager()
{
	AssetManager::Release();
	mAssetManager = NULL;

	Graphics::Release();
	mGraphics = NULL;

	Timer::Release();
	mTimer = NULL;

	InputManager::Release();
	mInputManager = NULL;

	AudioManager::Release();
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


void GameManager::EarlyUpdate()
{
	mTimer->Reset();
	mInputManager->Update();
}


void GameManager::Update()
{	
	for (Texture* i : particles)
	{
		i->particleUpdate(mTimer->DeltaTime());
	}

	buttonOnePressed = false;
	buttonTwoPressed = false;

	if (mInputManager->MouseButtonDown(InputManager::left))
	{

		bool isPressed = mInputManager->MouseButtonPressed(InputManager::left);

		if (mInputManager->MouseIsInArea(mButtonOneXPos - mButtonOne->GetWidth() / 2, buttonHeight - mButtonOne->GetHeight() / 2, mButtonOneXPos + mButtonOne->GetWidth() / 2, buttonHeight + mButtonOne->GetHeight() / 2))
		{
			if (isPressed)
			{
				//mAudioManager->PlaySFX("Button.wav");
			}

			buttonOnePressed = true;
		}

		// Button two
		if (mInputManager->MouseIsInArea(mButtonTwoXPos - mButtonTwo->GetWidth() / 2, buttonHeight - mButtonTwo->GetHeight() / 2, mButtonTwoXPos + mButtonTwo->GetWidth() / 2, buttonHeight + mButtonTwo->GetHeight() / 2))
		{
			if (isPressed)
			{
				//mAudioManager->PlaySFX("Button.wav");
			}

			buttonTwoPressed = true;
		}

		if (buttonPressTick >= buttonPressTimer)
		{
			buttonPressTick = 0;

			// Button one
			if (mInputManager->MouseIsInArea(mButtonOneXPos - mButtonOne->GetWidth() / 2, buttonHeight - mButtonOne->GetHeight() / 2, mButtonOneXPos + mButtonOne->GetWidth() / 2, buttonHeight + mButtonOne->GetHeight() / 2))
			{
				platformWeight -= balanceChangeForce;
			}

			// Button two
			if (mInputManager->MouseIsInArea(mButtonTwoXPos - mButtonTwo->GetWidth() / 2, buttonHeight - mButtonTwo->GetHeight() / 2, mButtonTwoXPos + mButtonTwo->GetWidth() / 2, buttonHeight + mButtonTwo->GetHeight() / 2))
			{
				platformWeight += balanceChangeForce;
			}
		}
		else
		{
			buttonPressTick += 240 * mTimer->DeltaTime();
		}
	}

	float _rx = mPlate->RotatePoint(mPlate->Pos(), mPlate->GetWidth() / 2, mPlate->Rotation());
	float _lx = mPlate->RotatePoint(mPlate->Pos(), -mPlate->GetWidth() / 2, mPlate->Rotation());

	mWeightBalance = VEC2_ZERO;

	if (!finishedRound && !lost)
	{
		for (Texture* i : constructions)
		{
			float resultWeight = i->buildingUpdate(mTimer->DeltaTime(), mPlate->mRotation, _lx, _rx, completed_objectives, objectives_terminated);

			float _x = i->Pos().x;

			if (i->Pos().x > Graphics::SCREEN_WIDTH / 2)
			{
				float result = (_x / _rx - 0.5f) / 6;

				mWeightBalance.y += resultWeight * result;
			}
			else
			{
				float result = (1 - (_x / _lx - 1)) / 6;

				mWeightBalance.x += resultWeight * result;
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
			playerScore->Pos(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.1));
		}
		else
		{
			max_chances--;
		}

		previous_completed_objectives = completed_objectives;
		updateScore();	
	}

	float finalResult = (mWeightBalance.y - mWeightBalance.x) + platformWeight;

	if (!finishedRound && !lost)
	{
		mPlate->Rotate(finalResult * mTimer->DeltaTime());
	}

	mPlate->mRotation = SDL_clamp(mPlate->mRotation, -60, 60);

	if (objectives_terminated >= current_objective)
	{
		finishedRound = true;
	}
	
	alpha += (((finishedRound || lost) ? 250 : 0 - alpha) / 1.5) * mTimer->DeltaTime();
	alpha = SDL_clamp(alpha, 0, 255);

	mBlack->SetAlpha(alpha);
	gameOverText->SetAlpha(alpha);

	if (alpha >= 250 && finishedRound)
	{
		newLevel();
	}

	if (max_chances <= 0)
	{
		lost = true;
	}

	if (lost && mInputManager->KeyPressed(SDL_SCANCODE_SPACE))
	{
		level = 0;
		max_chances = 26;
		current_score = 0;
		lost = false;

		newLevel();
	}
}

void GameManager::newLevel()
{

	level++;

	current_objective = level * 2;

	objectives_terminated = 0;
	completed_objectives = 0;
	previous_completed_objectives = 0;

	updateScore();

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
		frameTemp->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + _x - 250, Graphics::SCREEN_HEIGHT / 2 + 70));
		frameTemp->Parent(mPlate);

		Texture* temp = new Texture(name + ".png", 0, 0, 50, 0);
		temp->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + _x - 250, Graphics::SCREEN_HEIGHT / 2 + 70));

		float cooldown = rand() % 500 + 1;
		printf("%f\n", cooldown);

		temp->setBuilding(frameTemp, 50, false, cooldown);
		temp->Parent(mPlate);

		constructions.push_back(temp);
	}
}

void GameManager::updateScore()
{
	delete mScore;
	mScore = NULL;

	std::string s = std::to_string(completed_objectives);
	s.append("/");
	s.append(std::to_string(current_objective));

	mScore = new Texture(s, "Simplifica.ttf", 50, { 255, 255, 255 });
	mScore->Pos(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT * 0.2));
}

void GameManager::LateUpdate()
{
	mInputManager->UpdatePreviousInput();
}

void GameManager::Render()
{

	mGraphics->ClearBackBuffer();


	for (Texture* i : particles)
	{
		i->Render();
	}

	if (!buttonOnePressed)
	{
		mButtonOne->Render();
	}
	else
	{
		mButtonOnePressed->Render();
	}

	if (!buttonTwoPressed)
	{
		mButtonTwo->Render();
	}
	else
	{
		mButtonTwoPressed->Render();
	}

	mPlate->Render();
	mMiddlePole->Render();

	int count = 0;

	for (Texture* i : constructions)
	{
		i->Render();
	}

	count = 0;
	for (Texture* i : lightDotsRight)
	{
		if (count < max_chances)
		{
			i->Render();
			count++;
		}
	}

	count = 0;
	for (Texture* i : lightDotsLeft)
	{
		if (count < max_chances)
		{
			i->Render();
			count++;
		}
	}

	mScore->Render();
	playerScore->Render();

	mLights->Update();
	mLights->Render();

	mBlack->Render();

	if (lost)
	{
		gameOverText->Render();
	}

	mGraphics->Render();
}

void GameManager::Run()
{
	while (!mQuit)
	{
		mTimer->Update();

		while (SDL_PollEvent(&mEvents) != 0)
		{
			if (mEvents.type == SDL_QUIT)
			{
				mQuit = true;
			}
		}

		if (mTimer->DeltaTime() >= 1.0f / FRAME_RATE)
		{
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}