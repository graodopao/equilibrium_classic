#pragma once
#include <SDL.h>

namespace nashira {
	class Timer
	{

	private:
		static Timer* sInstance;

		unsigned int mStartTicks;
		unsigned int mElapsedTicks;
		float mDelataTime;
		float mTimeScale;

	public:

		static Timer* Instance();
		static void Release();

		void Reset();
		float DeltaTime();

		void TimeScale(float t);
		float TimeScale();

		void Update();

	private:

		Timer();
		~Timer();
	};
}