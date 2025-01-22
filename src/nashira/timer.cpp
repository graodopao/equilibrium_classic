#include "timer.h"
using namespace nashira;

Timer* Timer::s_instance = std::nullptr_t();

Timer* Timer::instance()
{
	if (s_instance == nullptr)
	{
		s_instance = new Timer();
	}

	return s_instance;
}

void Timer::release()
{
	delete s_instance;
	s_instance = nullptr;
}


Timer::Timer()
{
	reset();
	m_elapsed_ticks = 0;
	m_delta_time = 0.0f;
	m_time_scale = 1.0f;
}

Timer::~Timer() = default;

void Timer::reset()
{
	m_start_ticks = SDL_GetTicks();
}

float Timer::delta_time() const {
	return m_delta_time;
}

void Timer::time_scale(const float scale)
{
	m_time_scale = scale;
}

float Timer::time_scale() const {
	return m_time_scale;
}

void Timer::update()
{
	m_elapsed_ticks = SDL_GetTicks() - m_start_ticks;
	m_delta_time = static_cast<float>(m_elapsed_ticks) * 0.001f;
}