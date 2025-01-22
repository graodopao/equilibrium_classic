#include "game_entity.h"
using namespace nashira;

GameEntity::GameEntity(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;

	m_rotation = 0;

	mActive = true;

	m_parent = nullptr;

	m_scale = ONE;
}

GameEntity::~GameEntity()
{
	m_parent = nullptr;
}

void GameEntity::set_position(const Vector2 position)
{
	m_pos = position;
}

Vector2 GameEntity::get_position(const SPACE space) const
{
	if (space == SPACE::LOCAL || m_parent == nullptr)
	{
		return m_pos;
	}
	else
	{
		const Vector2 parent_scale{m_parent->Scale(SPACE::WORLD)};

		const float _x{m_pos.x * parent_scale.x};
		const float _y{m_pos.y * parent_scale.y};

		const auto temp_vec{Vector2{_x, _y}};
		const Vector2 rotPos{RotateVector(temp_vec, m_parent->Rotation(SPACE::LOCAL))};

		return m_parent->get_position(SPACE::WORLD) + rotPos;
	}
}

void GameEntity::Rotation(const float degree_angle)
{
	m_rotation = degree_angle;

	if (m_rotation > 360.0f)
	{
		m_rotation -= 360.0f;
	}

	if (m_rotation < 0.0f)
	{
		m_rotation += 360.0f;
	}
}

float GameEntity::Rotation(SPACE space) const
{
	if (space == SPACE::LOCAL || m_parent == nullptr)
	{
		return m_rotation;
	}
	else
	{
		return m_parent->Rotation(SPACE::WORLD) + m_rotation;
	}
}

void GameEntity::Scale(Vector2 scale)
{
	m_scale = scale;
}

Vector2 GameEntity::Scale(SPACE space)
{
	if (space == SPACE::LOCAL || m_parent == NULL)
	{
		return m_scale;
	}
	else
	{
		Vector2 scale = m_parent->Scale(SPACE::WORLD);
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
		m_pos = get_position(SPACE::WORLD);
		m_rotation = Rotation(SPACE::WORLD);
		m_scale = Scale(SPACE::WORLD);
	}
	else
	{
		if (m_parent != NULL)
			parent(NULL);

		Vector2 parentScale = with->Scale(SPACE::WORLD);

		Vector2 calc = get_position(SPACE::WORLD) - with->get_position(SPACE::WORLD);

		m_pos = RotateVector(calc, -with->Rotation(SPACE::WORLD));
		m_pos.x /= parentScale.x;
		m_pos.y /= parentScale.y;

		m_rotation -= with->Rotation(SPACE::WORLD);

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
	m_rotation += amount;
}

void GameEntity::update()
{

}

void GameEntity::render()
{

}
