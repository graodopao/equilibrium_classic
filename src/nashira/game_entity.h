#pragma once

#include "math_helper.h"

namespace nashira {
	class GameEntity
	{
	public:

		enum class SPACE
		{
			LOCAL = 0,
			WORLD = 1
		};

		float m_rotation;

	private:

		Vector2 m_pos;
		Vector2 m_scale;

		bool mActive;
		GameEntity* m_parent;

	public:

		GameEntity(float x = 0.0f, float y = 0.0f);

		virtual ~GameEntity();

		void set_position(Vector2 position);
		[[nodiscard]] Vector2 get_position(SPACE space = SPACE::WORLD) const;

		void Rotation(float degree_angle);
		[[nodiscard]] float Rotation(SPACE space = SPACE::WORLD) const;

		void Scale(Vector2 scale);
		Vector2 Scale(SPACE space = SPACE::WORLD);

		void Active(bool active);
		bool Active();

		void parent(GameEntity* parent);
		GameEntity* parent();

		void Translate(Vector2 vec);
		void Rotate(float amount);

		virtual void update();
		virtual void render();
	};
}