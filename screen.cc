#include "screen.hh"

Screen::Screen()
{
    _level = NULL;
    _font.loadFromFile(PATHF);
    _text = sf::Text("LEVEL: 0", _font);
    _text.setPosition(W_WIDTH/3, W_HEIGHT/2);
    _player = Player();
}

Screen::~Screen() {delete _level;}

//PlayerX       PlayerY     mult
//top   left    width   heght   vel     dist    dir     type
static std::list<levelInfo> readInfo(const std::string dir, sf::Vector2f& playerPos, float& mult)
{
    std::ifstream mapFile(dir);
    if (mapFile.is_open()) {
        std::string line;
        std::list<levelInfo> info;
        getline(mapFile,line);
        std::istringstream pre(line);
        std::string s;
        pre >> s;
        float x = atof(s.c_str());
        pre >> s;
        float y = atof(s.c_str());
        playerPos = sf::Vector2f(x, y);
        pre >> s;
        mult = atof(s.c_str());
        while (getline(mapFile,line)) {
            std::istringstream aux(line);
            levelInfo subInfo;
            aux >> s;
            subInfo.pos.top     = atof(s.c_str());
            aux >> s;
            subInfo.pos.left    = atof(s.c_str());
            aux >> s;
            subInfo.pos.width   = atof(s.c_str());
            aux >> s;
            subInfo.pos.height  = atof(s.c_str());
            aux >> s;
            subInfo.vel         = atof(s.c_str());
            aux >> s;
            subInfo.distance    = atof(s.c_str());
            aux >> s;
            subInfo.dir         = (Dir) atoi(s.c_str());
            aux >> s;
            subInfo.type        = (Type) atoi(s.c_str());
            info.push_back(subInfo);
        }
        return info;
    }
    else {
        std::cout << "Can't Open the file" << dir << std::endl;
        return std::list<levelInfo>();
    }
}

void Screen::loadLevel(int level) {
    sf::Vector2f playerPos;
    float mult;
    std::list<levelInfo> infoLevel = readInfo(std::string(PATHI + std::to_string(level)), playerPos, mult);
    _level = new Level(level, mult, infoLevel);
    _player.setPos(playerPos);
}

void Screen::event(sf::Event event)
{
    if  (!_level) {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Space:
            case sf::Keyboard::Insert:
            case sf::Keyboard::Up:
                if (_selectLevel == -1) std::cout << "HELLO" << std::endl;//Generator();
                else loadLevel(_selectLevel);
                break;
            case sf::Keyboard::Left:
                if (_selectLevel >= 0) --_selectLevel;
                break;
            case sf::Keyboard::Right:
                ++_selectLevel;
                break;
            default:
                break;
            }
        }
    }
    else {
        _player.event(event);
    }
}

void Screen::update(sf::Time deltatime)
{
    if (_level) {
        _player.update(deltatime);
        _level->update(deltatime);
        Dir dir;    float vel;
        sf::FloatRect bounds = _player.getGloablBounds();
        float gumminess = _level->getGumminess(bounds, dir, vel);
        Level::setPlayer(sf::Vector2f(bounds.left + 10.0f, abs(bounds.top - W_HEIGHT)));
        if (gumminess == LEVELPASS) {
            int level = 1 + _level->getLevel();
            delete _level;
            try {
                loadLevel(level);
            }
            catch (int e) {
                _level = NULL;
            }
        }
        _player.reboundForce(gumminess, dir, vel);
    }
    else _text.setString("LEVEL: " + std::to_string(_selectLevel));
}

void Screen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (_level) {
        _level->draw (target, states);
        _player.draw (target, states);
        _level->drawS(target, states);
    }
    else target.draw(_text);
}

