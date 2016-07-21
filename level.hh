#ifndef LEVEL_HH
#define LEVEL_HH

#include <stack>
#include "utils.hh"
#include "obstacle.hh"

static const std::string PATH   = "./resources/level";
static const std::string FORMAT = ".png";
static const float LEVELPASS = 666;
enum Push {BLANK, PRERENDER, HITBOX};

class Level
{
protected:
    int _level;
    Push _pushing;
    std::list<Obstacle> _obstacles;
    sf::Sprite _background;
    sf::Sprite _light;
    static sf::Shader _shader;

    static sf::Texture _text;
    static sf::Texture _backgroundT;
    static sf::Image   _preRender;

    sf::Color getDir(std::stack<Dir>& dirPre, sf::FloatRect bounds) const;
    void getDontMove(std::stack<Dir>& preDir) const;

public:
    static void setParameter(sf::Vector2i mousePos);
    static void setPlayer(sf::Vector2f playerPos);
    Level();
    Level(int level, float mult);
    Level(int level, float mult, std::list<levelInfo> info);
    ~Level();

    int getLevel() const;
    float getGumminess(sf::FloatRect bounds, Dir &dir, float &vel);

    void update(sf::Time deltatime);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void drawS(sf::RenderTarget &target, sf::RenderStates states) const;
};

#endif // LEVEL_H

