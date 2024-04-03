#include "Timer.h";

Timer* Timer::sInstance = NULL;

Timer* Timer::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new Timer();
	}

	return sInstance;
}

void Timer::Release()
{
	delete sInstance;
	sInstance = NULL;
}


Timer::Timer()
{
	Reset();
	mElapsedTicks = 0;
	mDelataTime = 0.0f;
	mTimeScale = 1.0f;
}

Timer::~Timer()
{

}

void Timer::Reset()
{
	mStartTicks = SDL_GetTicks();
}

float Timer::DeltaTime()
{
	return mDelataTime;
}

void Timer::TimeScale(float t)
{
	mTimeScale = t;
}

float Timer::TimeScale()
{
	return mTimeScale;
}

void Timer::Update()
{
	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	mDelataTime = mElapsedTicks * 0.001f;
}