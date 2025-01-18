#pragma once
#include "Timer.h";
#include "Texture.h";

namespace nashira {
	class AnimatedTexture : public Texture
	{
	public:
		enum WRAP_MODE
		{
			once,
			loop
		};

		enum ANIM_DIR
		{
			horizontal,
			vertical
		};

	private:

		Timer* mTimer;

		int mStartX;
		int mStartY;

		float mAnimationTimer;
		float mAnimationSpeed;
		float mTimePerFrame;

		int mFrameCount;

		WRAP_MODE mWrapMode;
		ANIM_DIR mAnimationDirection;

		bool mAnimationDone;

	public:

		AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR aniamtionDirection);
		~AnimatedTexture();

		void WrapMode(WRAP_MODE mode);

		void Update();

		void setSpeed(float mAnimationSpeed);
		void setFrame(float frame);

	};
}