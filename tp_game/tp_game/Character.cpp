//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Character.h"

//======================================================================================================================================//
// === Character methods === //

Character::Character()
{
}

Character::~Character()
{
}

void Character::initialize_Collider(sf::RectangleShape*& pCollider, const sf::Vector2f size)
{
	pCollider = new sf::RectangleShape(size);
	pCollider->setOrigin(size / 2.0f);
}

void Character::move(const float dx, const float dy)
{
	_position += sf::Vector2f(dx, dy);
}

void Character::move(const sf::Vector2f offset)
{
	_position += offset;
}

void Character::onCollision(const sf::Vector2f collisionDirection)
{
	//X axe
	if (collisionDirection.x < 0.0f)
	{ //Collision on left
		_velocity.x = 0.0f;
	}
	else if (collisionDirection.x > 0.0f)
	{ //Collisiton on right
		_velocity.x = 0.0f;
	}

	//Y axe
	if (collisionDirection.y > 0.0f)
	{ //Collisition on bottom
		_velocity.y = 0.0f;
		_canJump = true;
	}
	else if (collisionDirection.y < 0.0f)
	{ //Collision on top
		_velocity.y = 0.0f;
	}
}

void Character::setWalkSpeed(const float walkSpeed)
{
	_walkSpeed = walkSpeed;
}

float Character::getWalkSpeed() const
{
	return _walkSpeed;
}

void Character::setJumpHeight(const float jumpHeight)
{
	_jumpHeight = jumpHeight;
}

float Character::getJumpHeight() const
{
	return _jumpHeight;
}

void Character::setPosition(const sf::Vector2f position)
{
	_position = position;
}

sf::Vector2f Character::getPosition() const
{
	return _position;
}

sf::RectangleShape* Character::getCollider() const
{
	return _current_collider;
}

bool Character::isWalking(const float HorizontalMovement) const
{
	if (HorizontalMovement == 0.0f)
	{
		return false;
	}
	return true;
}
