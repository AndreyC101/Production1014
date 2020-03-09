#include "GameObject.h"

GameObject::GameObject() {
	m_position = vec2(0.0f, 0.0f);
	m_velocity = vec2(0.0f, 0.0f);
	m_rotation = vec2(0.0f, 0.0f);
	m_scale = vec2(1.0f, 1.0f);
	m_type = ObjectType::DEFAULT;
}