#include "obstacle.hh"


Obstacle::Obstacle()
{
    this->setFillColor(sf::Color::Black);
}

Obstacle::Obstacle(levelInfo info)
{
    switch (info.type) {
    case WALL:      this->setFillColor(sf::Color::Black);  break;
    case FLOOR:   this->setFillColor(sf::Color::Green);  break;
    case BOUNCE:   this->setFillColor(sf::Color::Cyan);   break;
    case COIN:      this->setFillColor(sf::Color::Yellow); break;
    case DEATH:     this->setFillColor(sf::Color::Red);    break;
    }
    this->setPosition(info.pos.left, info.pos.top);
    this->setSize(sf::Vector2f(info.pos.height, info.pos.width));
    _respawn = ((info.dir == LEFT or info.dir == RIGHT) and _distance > W_WIDTH) or
               ((info.dir == UP   or info.dir == DOWN)  and _distance > W_HEIGHT);
    _distanceStart = _distance = info.distance;
    _startPoint = sf::Vector2f(info.pos.left, info.pos.top);
    _type = info.type;
    _dir  = info.dir;
    _vel  = info.vel;
}

void Obstacle::update(sf::Time deltaTime)
{
    float desp = _vel*deltaTime.asMilliseconds();
    if (_distance <= 0) {
        _dir = (Dir)-_dir;
        if (_respawn) this->setPosition(_startPoint);
        _distance = _distanceStart;
    }
    switch (_dir) {
    case UP:
        this->move(0, desp); break;
    case DOWN:
        this->move(0, -desp); break;
    case LEFT:
        this->move(-desp, 0); break;
    case RIGHT:
        this->move(desp, 0); break;
    default:
        break;
    }
    _distance -= desp;
}

float Obstacle::getType() const {return _type;}
void  Obstacle::getMove(Dir &dir, float &vel) const
{
    dir = _dir;
    vel = _vel;
}
