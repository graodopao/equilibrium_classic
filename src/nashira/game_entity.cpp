#include "game_entity.h"
using namespace nashira;

GameEntity::GameEntity(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;

	mRotation = 0;

	mActive = true;

	m_parent = nullptr;

	m_scale = ONE;
}

GameEntity::~GameEntity()
{
	m_parent = nullptr;
}

void GameEntity::set_position(Vector2 position)
{
	m_pos = position;
}

Vector2 GameEntity::get_position(const SPACE space) const {
	if (space == LOCAL || m_parent == nullptr)
	{
		return m_pos;
	}
	else
	{
		Vector2 parentScale = m_parent->Scale(WORLD);

		const float _x = m_pos.x * parentScale.x;
		const float _y = m_pos.y * parentScale.y;

		Vector2 tempVec = Vector2(_x, _y);
		Vector2 rotPos = RotateVector(tempVec, m_parent->Rotation(LOCAL));

		return m_parent->get_position(SPACE::WORLD) + rotPos;
	}
}

void GameEntity::Rotation(float r)
{
	mRotation = r;

	if (mRotation > 360.0f)
	{
		mRotation -= 360.0f;
	}

	if (mRotation < 0.0f)
	{
		mRotation += 360.0f;
	}
}

float GameEntity::Rotation(SPACE space)
{
	if (space == LOCAL || m_parent == nullptr)
	{
		return mRotation;
	}
	else
	{
		return m_parent->Rotation(WORLD) + mRotation;
	}
}

void GameEntity::Scale(Vector2 scale)
{
	m_scale = scale;
}

Vector2 GameEntity::Scale(SPACE space)
{
	if (space == LOCAL || m_parent == NULL)
	{
		return m_scale;
	}
	else
	{
		Vector2 scale = m_parent->Scale(WORLD);
		scale.x *= m_scale.x;
		scale.y *= m_scale.y;

		return scale;
	}
}

void GameEntity::Active(bool active)
{
	mActive = active;
}

bool GameEntity::Active()
{
	return mActive;
}

void GameEntity::parent(GameEntity* with)
{
	if (with == NULL)
	{
		m_pos = get_position(WORLD);
		mRotation = Rotation(WORLD);
		m_scale = Scale(WORLD);
	}
	else
	{
		if (m_parent != NULL)
			parent(NULL);

		Vector2 parentScale = with->Scale(WORLD);

		Vector2 calc = get_position(WORLD) - with->get_position(WORLD);

		m_pos = RotateVector(calc, -with->Rotation(WORLD));
		m_pos.x /= parentScale.x;
		m_pos.y /= parentScale.y;

		mRotation -= with->Rotation(WORLD);

		m_scale = Vector2(m_scale.x / parentScale.x, m_scale.y / parentScale.y);
	}

	m_parent = with;
}

GameEntity* GameEntity::parent()
{
	return m_parent;
}

void GameEntity::Translate(Vector2 vec)
{
	m_pos += vec;
}

void GameEntity::Rotate(float amount)
{
	mRotation += amount;
}

void GameEntity::update()
{

}

void GameEntity::render()
{

}
