#pragma once
#include "timer.h"
#include "texture.h"

namespace nashira {
	class AnimatedTexture final : public Texture
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
		Timer* m_timer;

		int m_start_x;
		int m_start_y;

		float m_animation_timer;
		float m_animation_speed;
		float m_time_per_frame;

		int m_frame_count;

		WRAP_MODE m_wrap_mode;
		ANIM_DIR m_animation_direction;

		bool m_animation_done;

	public:

		AnimatedTexture(std::string filename, int x, int y, int w, int h, int frame_count, float animation_speed, ANIM_DIR animation_direction);
		~AnimatedTexture() override;

		void wrap_mode(WRAP_MODE mode);

		void update() override;

		void set_speed(float mAnimationSpeed);
		void set_frame(float frame);

	};
}