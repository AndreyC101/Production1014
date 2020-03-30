#include "GameObject.h"

GameObject::GameObject() {
	SetPosition(vec2(0.0f, 0.0f));
	SetVelocity(vec2(0.0f, 0.0f));
	SetRotation(vec2(0.0f, 0.0f));
	SetScale(vec2(1.0f, 1.0f));
	SetObjectType(ObjectType::UNDEFINED);
}