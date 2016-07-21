#include "level.hh"

sf::Texture Level::_backgroundT;
sf::Image   Level::_preRender;
sf::Texture Level::_text;
sf::Shader  Level::_shader;

Level::Level() : Level(0, 15.0f) {}

Level::Level(int level, float mult)
{
    _level = level;
    std::string file = PATH + std::to_string(level) + FORMAT;
    if (! _preRender.loadFromFile(file)) throw 1;
    if(!_backgroundT.loadFromImage(_preRender)) throw 1;
    _background = sf::Sprite(_backgroundT);
    _background.setScale(W_WIDTH/float(_backgroundT.getSize().x), W_HEIGHT/float(_backgroundT.getSize().y));
    _text.create(W_WIDTH, W_HEIGHT);
    _light.setTexture(_text);
    _shader.loadFromFile("./resources/shader", sf::Shader::Fragment);
    _shader.setParameter("resolution", sf::Vector2f(W_WIDTH, W_HEIGHT));
    _shader.setParameter("mult", mult);
    _pushing = BLANK;
}


Level::Level(int level, float mult, std::list<levelInfo> info) : Level(level, mult)
{
    for (std::list<levelInfo>::iterator itI = info.begin(); itI != info.end(); ++itI) {
        _obstacles.push_front(Obstacle(*itI));
    }
}

Level::~Level() {}

int Level::getLevel() const {return _level;}

void Level::update(sf::Time deltaTime)
{
    for (std::list<Obstacle>::iterator it = _obstacles.begin(); it != _obstacles.end(); ++it)
        it->update(deltaTime);
}

void Level::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(_background);
    for (std::list<Obstacle>::const_iterator it = _obstacles.begin(); it != _obstacles.end(); ++it)
        target.draw(*it);

}

void Level::drawS(sf::RenderTarget &target, sf::RenderStates states) const
{target.draw(_light, &_shader);}

void Level::getDontMove(std::stack<Dir>& preDir) const
{
    std::vector<int> types = {0,0,0,0,0};
    while (not preDir.empty()) {
        ++types[preDir.top() + 2];
        preDir.pop();
    }
    for (int i = 0; i < 5; ++i) {
        if (types[i] >= 2) {
            preDir.push((Dir) (i - 2));
        }
    }
}

sf::Color Level::getDir(std::stack<Dir>& dirPre, sf::FloatRect bounds) const
{
    sf::Color pixel1 = _preRender.getPixel(bounds.left/_background.getScale().x,
                                            bounds.top /_background.getScale().y);
    sf::Color pixel2 = _preRender.getPixel((bounds.left + bounds.width)/_background.getScale().x,
                                        (bounds.top + bounds.height)/_background.getScale().y);
    sf::Color pixel3 = _preRender.getPixel(bounds.left/_background.getScale().x,
                                (bounds.top + bounds.height)/_background.getScale().y);
    sf::Color pixel4 = _preRender.getPixel((bounds.left + bounds.width)/_background.getScale().x,
                                           bounds.top/_background.getScale().y);
    sf::Color pixel = pixel1;
    if (pixel1 != sf::Color::Green) {
        dirPre.push(LEFT);
        dirPre.push(UP);
        pixel = pixel1;
    }
    if (pixel2 != sf::Color::Green) {
        dirPre.push(RIGHT);
        dirPre.push(DOWN);
        pixel = pixel2;
    }
    if (pixel3 != sf::Color::Green) {
        dirPre.push(LEFT);
        dirPre.push(DOWN);
        pixel = pixel3;
    }
    if (pixel4 != sf::Color::Green) {
        dirPre.push(RIGHT);
        dirPre.push(UP);
        pixel = pixel4;
    }
    getDontMove(dirPre);
    return pixel;
}

float Level::getGumminess(sf::FloatRect bounds, Dir &dir, float &vel)
{
    Dir dirHit = NOTHING;  float velHit = 0; float gumminessHit = 1; dir = NOTHING; vel = 0;
    if (bounds.left < 0 or (bounds.left + bounds.width) > W_WIDTH or bounds.top  < 0 or (bounds.top + bounds.height) > W_HEIGHT) return 0;

    //get hitbox info
    std::list<Obstacle>::const_iterator it = _obstacles.begin();
    while (it != _obstacles.end() and not it->getGlobalBounds().intersects(bounds)) ++it;
    if (it != _obstacles.end()) {
        it->getMove(dirHit, velHit);
        gumminessHit = it->getType();
    }

    //get Prerender info
    std::stack<Dir> dirPre;
    sf::Color pixel = getDir(dirPre, bounds);

    float gumminesPre = SUELO;
    if (pixel == sf::Color::Black)  gumminesPre = 0;
    else if (pixel == sf::Color::Blue) return LEVELPASS;
    else if (pixel == sf::Color::Yellow) gumminesPre = 1.1;

    //calc intersect collisions
    if (dirHit == NOTHING and dirPre.empty()) {
        dir = NOTHING;
        vel = 0;
        return gumminesPre;
    }
    else if (dirHit == NOTHING) {
        dir = dirPre.top();
        vel = 0;
        return gumminesPre;
    }
    else if (dirPre.empty()) {
        dir = dirHit;
        vel = velHit;
        return gumminessHit;
    }
    float gumminess;
    while (not dirPre.empty()) {
        if (dirHit + dirPre.top() == 0) {
            dir = dirPre.top();
            gumminess = gumminesPre;
            break;
        }
        else if (dirHit == dirPre.top()) {
            dir = dirHit;
            gumminess = gumminessHit;
            vel = velHit;
            break;
        }
        dirPre.pop();
    }
    return gumminess;
}

void Level::setParameter(sf::Vector2i mousePos)
{
    _shader.setParameter("mouse", sf::Vector2f(mousePos.x, mousePos.y - W_HEIGHT));
}

void Level::setPlayer(sf::Vector2f playerPos)
{
    _shader.setParameter("player", playerPos);
}

