//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Animator.h"

//======================================================================================================================================//
// === Classes headers for redefinition === //
#include "Entity.h"

Animator::Animator(std::string texture_filePath, unsigned int nFrames, float switchTime, Entity* pEntity)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_nFrames = nFrames;
	_switchTime = switchTime;

	_currentTime = 0.0f;
	_frameCounter = 0;

	_pEntity = pEntity;

	initializeTexture(texture_filePath);
	initializeSprite();

} // end constr (parameters)
/*
Animator::Animator(std::string texture_filePath, unsigned int nFrames, float switchTime, Enemy* pEnemy)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_nFrames = nFrames;
	_switchTime = switchTime;

	_currentTime = 0.0f;
	_frameCounter = 0;

	_pEnemy = pEnemy;

	initializeTexture(texture_filePath);
	initializeSprite();

} // end constr (parameters)
*/
Animator::Animator()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");

	_nFrames = 0;
	_switchTime = 0;
	_currentTime = 0.0f;
	_frameCounter = 0;
	_pSprite = NULL;
	_pEntity = NULL;
} // end constr (no parameters)

Animator::~Animator()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
} // end destr

void Animator::initializeTexture(std::string texture_filePath)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	//Load texture 
	if( !_texture.loadFromFile(texture_filePath))
	{
		 getchar();
	}
	
	//Set canvas borders
	_canvasRect.width = _texture.getSize().x / _nFrames;
	_canvasRect.height = _texture.getSize().y;
	_canvasRect.top = 0;

} // end initializeTexture

void Animator::initializeSprite()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_pSprite = new sf::Sprite;
	_pSprite->setTexture(_texture);
	_pSprite->setOrigin(sf::Vector2f((float)_canvasRect.width, (float)_canvasRect.height) / 2.0f);
} // end initializeSprite

void Animator::updateSprite(float deltaTime, bool facingRight)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_currentTime += deltaTime;

	updateFrame();
	updateSpriteDirection(facingRight);

	_pSprite->setTexture(_texture);
	_pSprite->setTextureRect(_canvasRect);
	_pSprite->setPosition(_pEntity->getPosition());
} // end updateSprite

void Animator::setFrameCounter(unsigned int frameCounter)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_frameCounter = frameCounter;
}

unsigned int Animator::getSpriteCounter() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _frameCounter;
}

void Animator::setnFrames(unsigned int nFrames)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_nFrames = nFrames;
}

unsigned int Animator::getnFrames() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _nFrames;
}

void Animator::setCurrentTime(float currentTime)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_currentTime = currentTime;
}

float Animator::getCurrentTime() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _currentTime;
}

void Animator::setSwitchTime(float switchTime)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_switchTime = switchTime;
}

float Animator::getSwitchTime() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _switchTime;
}

void Animator::setpSprite(sf::Sprite* pSprite)
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	_pSprite = pSprite;
}

sf::Sprite* Animator::getpSprite() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return _pSprite;
}

sf::Vector2f Animator::getSpriteSize() const
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	return sf::Vector2f( (float)_canvasRect.width, (float)_canvasRect.height );
}

void Animator::updateFrame()
{
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

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
	MyWindow::console_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

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