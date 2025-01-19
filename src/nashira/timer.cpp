#include "timer.h";
using namespace nashira;

Timer* Timer::sInstance = std::nullptr_t();

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
	mDeltaTime = 0.0f;
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
	return mDeltaTime;
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
	mDeltaTime = mElapsedTicks * 0.001f;
}