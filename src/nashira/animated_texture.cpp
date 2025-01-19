#include "animated_texture.h"

#include <utility>
using namespace nashira;

AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frame_count, float animation_speed, ANIM_DIR animationDir)
	: Texture(std::move(filename), x, y, w, h)
{
	m_timer = Timer::Instance();

	m_start_x = x;
	m_start_y = y;

	m_frame_count = frame_count;
	m_animation_speed = animation_speed;
	m_time_per_frame = m_animation_speed / static_cast<float>(m_frame_count);
	m_animation_timer = 0.0f;

	m_animation_direction = animationDir;

	m_animation_done = false;

	m_wrap_mode = loop;
}

AnimatedTexture::~AnimatedTexture()= default;

void AnimatedTexture::WrapMode(WRAP_MODE mode)
{
	m_wrap_mode = mode;
}

void AnimatedTexture::setSpeed(float animationSpeed)
{
	m_animation_speed = animationSpeed;
}

void AnimatedTexture::setFrame(float timer)
{
	m_animation_timer = timer;
	m_animation_done = false;
}

void AnimatedTexture::Update()
{
	if (!m_animation_done)
	{
		m_animation_timer += m_timer->DeltaTime();

		if (m_animation_timer >= m_animation_speed)
		{
			if (m_wrap_mode == loop)
			{
				m_animation_timer -= m_animation_speed;
			}
			else
			{
				m_animation_done = true;
				m_animation_timer = m_animation_speed - m_time_per_frame;
			}
		}

		if (m_animation_direction == horizontal)
		{
			m_clip_rect.x = m_start_x + static_cast<int>(m_animation_timer / m_time_per_frame) * m_width;
		}
		else
		{
			m_clip_rect.y = m_start_y + static_cast<int>(m_animation_timer / m_time_per_frame) * m_height;
		}
	}
}
