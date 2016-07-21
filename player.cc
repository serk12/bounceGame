#include "player.hh"

Player::Player()
{
    _cercle = sf::CircleShape(SIZECERCLE);
    _cercle.setFillColor(sf::Color::Magenta);
    _cercle.setOrigin(SIZECERCLE/2, SIZECERCLE/2);
    _moving  = false;
    _canMove = true;
    _dirH = NOTHING;
    _move = sf::Vector2f(0,0);
    _velocity = 0;
}

Player::Player(sf::Vector2f level) : Player() {_cercle.setPosition(level);}

Player::~Player() {}

void Player::event(sf::Event event)
{
    if (event.mouseButton.button == sf::Mouse::Left) {
        if (event.type == sf::Event::MouseButtonPressed)
            _mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
        else if (event.type == sf::Event::MouseButtonReleased and _canMove) {
            sf::Vector2f diffMouse = _mousePos - sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
            _velocity = sqrt(diffMouse.x*diffMouse.x+diffMouse.y*diffMouse.y);
            if (_velocity > VELOCITYMAX) _velocity = VELOCITYMAX;
            _angle = atan2(diffMouse.y, diffMouse.x);
            if (!_moving) _moving = true;
            _canMove = false;
        }
    }
}

void Player::update(sf::Time deltaTime)
{
    if (_moving) {
        float delta = deltaTime.asMilliseconds();
        float moveX = delta*_velocity*cos(_angle);
        float moveY = delta*_velocity*sin(_angle);
        _move = sf::Vector2f(moveX, moveY);
    }
}

void Player::calcAngle(Dir dir)
{
    switch (dir) {
    case RIGHT:
    case LEFT:  _angle = PI - _angle; break;
    case UP:
    case DOWN:  _angle = -_angle; break;
    default:    break;
    }
}

void Player::reboundForce(float gumminess, Dir dir, float vel)
{
    if (gumminess != SUELO) {
        _canMove = true;
        _dirH = dir;
        if (dir != NOTHING) {
            _moving = true;
            if (gumminess == 0) {
                _velocity = vel;
                switch (dir) {
                case UP:    _angle = PI/2.0f;  break;
                case DOWN:  _angle = -PI/2.0f; break;
                case LEFT:  _angle = 0;     break;
                case RIGHT: _angle = PI;    break;
                }
            }
            else {
                _velocity *= gumminess;
                if (_velocity > VELOCITYMAX2) _velocity = VELOCITYMAX2;
                calcAngle(dir);
                _canMove = false;
            }
        }
        else _moving = false;
    }
    else {
        _dirH = NOTHING;
        _cercle.move(_move);
    }
}

sf::FloatRect Player::getGloablBounds() const
{
    sf::FloatRect info = _cercle.getGlobalBounds();
    info.top += _move.y;
    info.left += _move.x;
    return info;
}

void Player::setPos(sf::Vector2f pos)
{
    _cercle.setPosition(pos);
    _move = sf::Vector2f(0,0);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {target.draw(_cercle);}

