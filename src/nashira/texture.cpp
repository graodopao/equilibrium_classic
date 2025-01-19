#include "texture.h"
using namespace nashira;

Texture::Texture(std::string filename)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(filename);

	SDL_QueryTexture(mTex, NULL, NULL, &m_width, &m_height);

	mClipped = false;

	mRenderRect.w = m_width;
	mRenderRect.h = m_height;
}

Texture::Texture(std::string filename, int x, int y, int w, int h)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(filename);

	mClipped = true;

	m_width = w;
	m_height = h;

	mRenderRect.w = m_width;
	mRenderRect.h = m_height;

	m_clip_rect.x = x;
	m_clip_rect.y = y;
	m_clip_rect.w = m_width;
	m_clip_rect.h = m_height;
}

float Texture::GetWidth()
{
	return m_width;
}

float Texture::GetHeight()
{
	return m_height;
}

void Texture::SetAlpha(Uint8 alpha)
{
	SDL_SetTextureAlphaMod(mTex, alpha);
}

float Texture::RotatePoint(Vector2 pos, float dist, float dir)
{
	GameEntity* temp = new GameEntity(pos.x, pos.y);
	temp->Rotate(dir);
	temp->Translate(Vector2(dist, 0.0f));

	float result = temp->Pos().x;

	delete temp;
	temp = NULL;

	return result;
}

void Texture::particleUpdate(float deltaTime)
{
	particleTick += 1000 * deltaTime;
	horizontalParticleTick += 750 * deltaTime;

	if (particleTick >= particleMoveUpdate)
	{
		particleTick = 0;

		Translate(Vector2(0, 2.5));

		if (Pos().y > 720)
		{
			Pos(Vector2(Pos().x, 0));
		}
	}

	if (horizontalParticleTick >= horizontalParticleMoveUpdate)
	{
		horizontalParticleTick = 0;

		int _x = rand() % 5 + 0;
		Translate(Vector2(_x - 2.5, 0));

		if (Pos().x > 1280)
		{
			Pos(Vector2(0, Pos().y));
		}
		else if (Pos().x < 0)
		{
			Pos(Vector2(1280, Pos().y));
		}
	}
}

float Texture::buildingUpdate(float deltaTime, float angle, float leftPoint, float rightPoint, int& objective, int& objective_term)
{
	buildingIdleTick += 20 * deltaTime;

	if (secondTexture != NULL)
	{
		secondTexture->buildingUpdate(deltaTime, angle, leftPoint, rightPoint, objective, objective_term);
	}

	if (abs(Rotation()) > 10 && currentBuildingState != falling && buildingIdleTick > buildingIdleCooldown)
	{
		float pos = angle > 0 ? 130 : -130;

		Translate((VEC2_RIGHT * (pos * (abs(angle - 10) / 50))) * deltaTime);

		if (Pos().x > rightPoint || Pos().x < leftPoint)
		{

			if (currentBuildingState != falling)
			{
				if (secondTexture != NULL)
				{
					objective -= currentBuildingState == built ? 2 : 1;
					objective_term++;
				}
				currentBuildingState = falling;

				Vector2 lastpos = Pos(world);

				Parent(NULL);
				Pos(lastpos);
			}
		}
	}

	riseTick += 120.0f * deltaTime;

	if (riseTick >= riseCooldown)
	{
		riseTick = 0.0f;

		switch (currentBuildingState)
		{

			case (building):

				if (buildingIdleTick > buildingIdleCooldown)
				{
					Rise(5.0f, maxHeight);

					if (m_height < maxHeight)
					{
						Translate(VEC2_UP * -2.5f);
					}
					else
					{
						if (secondTexture != NULL)
						{
							objective++;
						}

						currentBuildingState = built;
					}
				}

			break;

			case(built):

				if (secondTexture != NULL)
				{

					if (secondTexture->isDemolished())
					{
						printf("Terminated\n");
						objective_term++;
						secondTexture = NULL;
					}
					else
					{
						secondTexture->buildingDemolish();
					}
				}

			break;

			case (deconstruct):

				if (m_height > 0)
				{
					Translate(VEC2_UP * 5.0f);
				}
				else
				{
					currentBuildingState = built;
				}

			Unrise(10.0f);

			break;

		}
	}

	if (currentBuildingState != falling)
	{
		return m_width * m_height / 50;
	}
	else
	{
		Rotate(((Pos().x > Graphics::SCREEN_WIDTH / 2) ? (90.0f * deltaTime) : (-90.0f * deltaTime)));
		Translate(Vector2(Pos().x > Graphics::SCREEN_WIDTH / 2 ? 30.0f * deltaTime : -30.0f * deltaTime, vspd * deltaTime));

		vspd += gravity;

		return 0;
	}
}

bool Texture::isDemolished()
{
	return (currentBuildingState == demolished);
}

void Texture::setBuilding(Texture* frameTexture, int maximumHeight, bool isFrame, float constructionCooldown)
{
	maxHeight = maximumHeight;

	if (!isFrame)
	{
		secondTexture = frameTexture;
		secondTexture->setBuilding(NULL, maximumHeight, true, constructionCooldown);
	}

	buildingIdleCooldown = constructionCooldown;
}

void Texture::buildingDemolish()
{
	currentBuildingState = deconstruct;
}

void Texture::Rise(float amount, float cap)
{
	m_clip_rect.h += amount;
	m_height += amount;

	m_clip_rect.h = SDL_clamp(m_clip_rect.h, 0, cap);
	m_height = SDL_clamp(m_height, 0, cap);
}

void Texture::Unrise(float amount)
{
	m_clip_rect.h -= amount;
	m_height -= amount;

	m_clip_rect.h = SDL_clamp(m_clip_rect.h, 0, 1000);
	m_height = SDL_clamp(m_height, 0, 1000);

	if (m_height <= 0)
	{
		currentBuildingState = demolished;
	}
}

Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetText(text, fontPath, size, color);

	mClipped = false;

	SDL_QueryTexture(mTex, NULL, NULL, &m_width, &m_height);

	mRenderRect.w = m_width;
	mRenderRect.h = m_height;
}

Texture::~Texture()
{
	mTex = NULL;
	mGraphics = NULL;
}

void Texture::Render()
{
	Vector2 pos = Pos(world);
	Vector2 scale = Scale(world);
	mRenderRect.x = (int)(pos.x - m_width*scale.x * 0.5f);
	mRenderRect.y = (int)(pos.y - m_height*scale.y * 0.5f);
	mRenderRect.w = (int)(m_width * scale.x);
	mRenderRect.h = (int)(m_height * scale.y);

	mGraphics->DrawTexture(mTex, mClipped ? &m_clip_rect : NULL, &mRenderRect, Rotation(world));

	if (secondTexture != NULL)
	{
		secondTexture->Render();
	}
}
