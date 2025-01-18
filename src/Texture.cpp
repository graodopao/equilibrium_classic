#include "Texture.h"
using namespace nashira;

Texture::Texture(std::string filename)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(filename);

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::Texture(std::string filename, int x, int y, int w, int h)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(filename);

	mClipped = true;

	mWidth = w;
	mHeight = h;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mClipRect.x = x;
	mClipRect.y = y;
	mClipRect.w = mWidth;
	mClipRect.h = mHeight;
}

float Texture::GetWidth()
{
	return mWidth;
}

float Texture::GetHeight()
{
	return mHeight;
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

					if (mHeight < maxHeight)
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

				if (mHeight > 0)
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
		return mWidth * mHeight / 50;
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
	mClipRect.h += amount;
	mHeight += amount;

	mClipRect.h = SDL_clamp(mClipRect.h, 0, cap);
	mHeight = SDL_clamp(mHeight, 0, cap);
}

void Texture::Unrise(float amount)
{
	mClipRect.h -= amount;
	mHeight -= amount;

	mClipRect.h = SDL_clamp(mClipRect.h, 0, 1000);
	mHeight = SDL_clamp(mHeight, 0, 1000);

	if (mHeight <= 0)
	{
		currentBuildingState = demolished;
	}
}

Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetText(text, fontPath, size, color);

	mClipped = false;

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
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
	mRenderRect.x = (int)(pos.x - mWidth*scale.x * 0.5f);
	mRenderRect.y = (int)(pos.y - mHeight*scale.y * 0.5f);
	mRenderRect.w = (int)(mWidth * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);

	mGraphics->DrawTexture(mTex, mClipped ? &mClipRect : NULL, &mRenderRect, Rotation(world));

	if (secondTexture != NULL)
	{
		secondTexture->Render();
	}
}
