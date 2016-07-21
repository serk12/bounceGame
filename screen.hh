#ifndef SCREEN_HH
#define SCREEN_HH

#include "player.hh"
#include "level.hh"
//#include "generator.hh"

static const std::string PATHF  = "./resources/font.ttf";
static const std::string PATHI  = "./resources/info";

class Screen : public sf::Drawable
{
private:
    Player _player;
    Level* _level;

    sf::Font _font;
    sf::Text _text;

    int _selectLevel = 0;
    void loadLevel(int level);
public:
    Screen();
    ~Screen();

    void event(sf::Event event);
    void update(sf::Time deltatime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const final;
};


#endif // SCREEN_HH
