#ifndef OBSTACLES_HH
#define OBSTACLES_HH

#include "utils.hh"

enum Type {WALL = 0, FLOOR = 1, BOUNCE = 2, COIN = 3, DEATH = 4};

struct levelInfo {
    sf::FloatRect pos;
    Type type;
    Dir dir;
    float vel;
    float distance;
};

class Obstacle : public sf::RectangleShape
{
private:
    Dir _dir;
    Type _type;
    float _vel;
    float _distance;
    float _distanceStart;
    bool _respawn;
    sf::Vector2f _startPoint;

public:

    Obstacle();
    Obstacle(levelInfo info);
    void update(sf::Time deltaTime);
    float getType() const;
    void getMove(Dir &dir, float &vel) const;
};

#endif // OBSTACLES_HH

