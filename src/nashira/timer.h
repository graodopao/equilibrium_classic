#pragma once
#include <SDL.h>

namespace nashira {
	class Timer
	{

	private:
		static Timer* s_instance;

		unsigned int m_start_ticks{};
		unsigned int m_elapsed_ticks;
		float m_delta_time;
		float m_time_scale;

	public:

		static Timer* instance();
		static void release();

		void reset();
		[[nodiscard]] float delta_time() const;

		void time_scale(float scale);
		[[nodiscard]] float time_scale() const;

		void update();

	private:

		Timer();
		~Timer();
	};
}