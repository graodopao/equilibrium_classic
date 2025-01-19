#pragma once

#include "math_helper.h"

namespace nashira {
	class GameEntity
	{
	public:

		enum SPACE
		{
			local = 0,
			world = 1
		};

		float mRotation;

	private:

		Vector2 mPos;
		Vector2 mScale;

		bool mActive;
		GameEntity* mParent;

	public:

		GameEntity(float x = 0.0f, float y = 0.0f);
		~GameEntity();

		void Pos(Vector2 pos);
		Vector2 Pos(SPACE space = world);

		void Rotation(float rotation);
		float Rotation(SPACE space = world);

		void Scale(Vector2 scale);
		Vector2 Scale(SPACE space = world);

		void Active(bool active);
		bool Active();

		void Parent(GameEntity* parent);
		GameEntity* Parent();

		void Translate(Vector2 vec);
		void Rotate(float amount);

		virtual void Update();
		virtual void Render();
	};
}