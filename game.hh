#ifndef GAME_HH
#define GAME_HH

#include "screen.hh"

class Game
{
private:
    sf::RenderWindow _window;
    sf::Clock _clock;

    Screen* _current_screen;

    void event_();
    void update_();
    void draw_();
public:
    Game();
    ~Game();
    void start();
};

#endif // GAME_HH
