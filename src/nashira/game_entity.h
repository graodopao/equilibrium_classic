#pragma once

#include "math_helper.h"

namespace nashira {
	class GameEntity
	{
	public:

		enum SPACE
		{
			LOCAL,
			WORLD
		};

		float mRotation;

	private:

		Vector2 m_pos;
		Vector2 m_scale;

		bool mActive;
		GameEntity* m_parent;

	public:

		GameEntity(float x = 0.0f, float y = 0.0f);

		virtual ~GameEntity();

		void set_position(Vector2 position);
		Vector2 get_position(SPACE space = WORLD) const;

		void Rotation(float rotation);
		float Rotation(SPACE space = WORLD);

		void Scale(Vector2 scale);
		Vector2 Scale(SPACE space = WORLD);

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