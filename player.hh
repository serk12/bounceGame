#ifndef PLAYER_HH
#define PLAYER_HH

#include "utils.hh"

static const float SIZECERCLE   = 7.5f;
static const float VELOCITYMAX  = 0.25f;
static const float VELOCITYMAX2 = 0.30f;
static const float MARGE        = 1;
#define PI 3.14159265359

class Player : public sf::Drawable
{
private:
    sf::CircleShape _cercle;
    sf::Vector2f _mousePos;
    sf::Vector2f _move;
    float _velocity;
    float _angle;
    float _lastAngle;
    bool _moving;
    bool _canMove;
    Dir _dirH;

    void calcAngle(Dir dir);

public:

    Player();
    Player(sf::Vector2f level);
    ~Player();

    void setPos(sf::Vector2f pos);
    void reboundForce(float gumminess, Dir dir, float vel);
    sf::FloatRect getGloablBounds() const;

    void event(sf::Event event);
    void update(sf::Time deltatime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};

#endif // PLAYER_HH
