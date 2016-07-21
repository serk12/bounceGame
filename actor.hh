#ifndef ACTOR_HH
#define ACTOR_HH

#include "gameobject.hh"
template <class T>
class Actor : public GameObject
{
protected:
    T _object;
public:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const final
    {
        target.draw(_object);
    }
};

#endif // ACTOR_HH
