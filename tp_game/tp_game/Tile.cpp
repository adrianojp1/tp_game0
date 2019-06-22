//======================================================================================================================================//
// === Pre-Compiled Header === //
#include "stdafx.h"

//======================================================================================================================================//
// === This Class Header === //
#include "Tile.h"

//======================================================================================================================================//
// === Static initializations === //
const sf::Vector2f Tile::OriginalSize = sf::Vector2f{ 16.0f, 16.0f };
sf::Vector2f Tile::_realSize = OriginalSize;

//======================================================================================================================================//
// === Tile methods === //

Tile::Tile(const sf::Vector2f initPosition, const int id) :
	Entity(initPosition, true, id)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	initialize_animator();
	initialize_Collider(_collider, (*_animator)[0]->getCanvasSize());
	
	_current_collider = _collider;
	_current_collider->setPosition(_position);
}

Tile::Tile() : Entity()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 1 | ");
	_collider = NULL;
}

Tile::~Tile()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
	if (_collider)
		delete _collider;
	if (_animator)
		delete _animator;
}

void Tile::initialize_animator()
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");

	_animator = new Animator(static_cast<Entity*>(this));

	Animation* pAnime = new Animation(gMng::tileset_texture, 1, 0.0f);

	sf::Vector2i TileRectPosition = sf::Vector2i{_id % 24, _id / 24 } * OriginalSize;
	pAnime->setCanvasRect(sf::IntRect(TileRectPosition, sf::Vector2i{ OriginalSize }));
	pAnime->initializeSprite();

	(*_animator) << pAnime;
	(*_animator).setCurrentAnime(0);
	_animator->getCurrentAnime()->getpSprite()->setPosition(_position);
}

void Tile::execute(float deltaTime)
{
	Graphical_Manager::printConsole_log(__FUNCTION__ + (std::string)" | -ov: 0 | ");
}

void Tile::setRealSize(const sf::Vector2f realSize)
{
	_realSize = realSize;
}

const sf::Vector2f Tile::getRealSize()
{
	return _realSize;
}