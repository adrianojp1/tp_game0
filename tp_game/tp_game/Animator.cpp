//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Animator.h"

//======================================================================================================================================//
// === Classes headers for redefinition === //
#include "Player.h"

Animator::Animator(std::string texture_filePath, unsigned int nFrames, float switchTime, Player* pPlayer)
{
	_nFrames = nFrames;
	_switchTime = switchTime;

	_currentTime = 0.0f;
	_frameCounter = 0;

	_pPlayer = pPlayer;

	initializeTexture(texture_filePath);
	initializeSprite();

} // end constr (parameters)

Animator::Animator()
{
	_nFrames = 0;
	_switchTime = 0;
	_currentTime = 0.0f;
	_frameCounter = 0;
	_pSprite = NULL;
	_pPlayer = NULL;
} // end constr (no parameters)

Animator::~Animator()
{
} // end destr

void Animator::initializeTexture(std::string texture_filePath)
{
	//Load texture 
	if( !_texture.loadFromFile(texture_filePath))
		{ std::cerr << "Failed loading texture: " << texture_filePath << std::endl; }
	
	//Set canvas borders
	_canvasRect.width = _texture.getSize().x / _nFrames;
	_canvasRect.height = _texture.getSize().y;
	_canvasRect.top = 0;

} // end initializeTexture

void Animator::initializeSprite()
{
	_pSprite = new sf::Sprite;
	_pSprite->setTexture(_texture);
	_pSprite->setOrigin(sf::Vector2f((float)_canvasRect.width, (float)_canvasRect.height) / 2.0f);
} // end initializeSprite

void Animator::updateSprite(float deltaTime, bool facingRight)
{
	_currentTime += deltaTime;

	updateFrame();
	updateSpriteDirection(facingRight);

	_pSprite->setTexture(_texture);
	_pSprite->setTextureRect(_canvasRect);
	_pSprite->setPosition(_pPlayer->getPosition());
} // end updateSprite

void Animator::setFrameCounter(unsigned int frameCounter)
{
	_frameCounter = frameCounter;
}

unsigned int Animator::getSpriteCounter() const
{
	return _frameCounter;
}

void Animator::setnFrames(unsigned int nFrames)
{
	_nFrames = nFrames;
}

unsigned int Animator::getnFrames() const
{
	return _nFrames;
}

void Animator::setCurrentTime(float currentTime)
{
	_currentTime = currentTime;
}

float Animator::getCurrentTime() const
{
	return _currentTime;
}

void Animator::setSwitchTime(float switchTime)
{
	_switchTime = switchTime;
}

float Animator::getSwitchTime() const
{
	return _switchTime;
}

void Animator::setpSprite(sf::Sprite* pSprite)
{
	_pSprite = pSprite;
}

sf::Sprite* Animator::getpSprite() const
{
	return _pSprite;
}

sf::Vector2f Animator::getSpriteSize() const
{
	return sf::Vector2f( (float)_canvasRect.width, (float)_canvasRect.height );
}

void Animator::updateFrame()
{
	//Enough time to change the frame
	if (_currentTime >= _switchTime)
	{
		_currentTime -= _switchTime; //Discount the time
		_frameCounter++;

		//The animation is over
		if (_frameCounter >= _nFrames)
		{
			_frameCounter = 0;
		}
	}
} // end updateFrame

void Animator::updateSpriteDirection(bool facingRight)
{
	if (facingRight)
	{
		_canvasRect.left = _frameCounter * _canvasRect.width;
		_canvasRect.width = abs(_canvasRect.width);
	}
	else
	{
		_canvasRect.left = (_frameCounter + 1) * abs(_canvasRect.width);
		_canvasRect.width = -abs(_canvasRect.width);
	}
} // end updateSpriteDirection