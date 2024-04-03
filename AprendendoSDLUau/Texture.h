#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameEntity.h"
#include "Timer.h"
#include "AssetManager.h"

class Texture : public GameEntity
{
protected:
	SDL_Texture* mTex;
	Texture* secondTexture = NULL;

	Graphics* mGraphics;
	Timer* mTimer;

	int mWidth;
	int mHeight;

	bool mClipped;
	SDL_Rect mRenderRect;
	SDL_Rect mClipRect;

	Uint8 alpha = 1;

	float riseCooldown = 120.0f;
	float riseTick = 0.0f;

	int* objective_variable = nullptr;

public:
	
	float RotatePoint(Vector2 pos, float dist, float dir);
		
	Texture(std::string filename);
	Texture(std::string filename, int x, int y, int w, int h);
	Texture(std::string text, std::string fontpath, int size, SDL_Color);
	
	float buildingUpdate(float deltaTime, float angle, float leftPoint, float rightPoint, int& objective, int& objectice_term);
	void SetAlpha(Uint8 alpha);
	
	void particleUpdate(float deltaTime);

	~Texture();

	float GetWidth();
	float GetHeight();

	virtual void Render();

	void Rise(float amount, float cap);
	void Unrise(float amount);

	void setBuilding(Texture* frameTexture, int maximumHeight, bool isFrame, float constructionCooldown);
	void buildingDemolish();

	bool isDemolished();

private:
	
	enum buildingState
	{
		building,
		built,
		deconstruct,
		demolished,
		falling
	};

	buildingState currentBuildingState = building;


	int maxHeight = 50;
	bool isBuilding = false;

	const float gravity = 10.0f;
	float vspd = 0.0f;

	float particleMoveUpdate = 60.0f;
	float particleTick = 0;

	float horizontalParticleMoveUpdate = 120.0f;
	float horizontalParticleTick = 0;

	float buildingIdleCooldown = 0.0f;
	float buildingIdleTick = 0.0f;

};

#endif // !_TEXTURE_H
