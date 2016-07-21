#include "game.hh"

Game::Game() {}
Game::~Game()
{delete _current_screen;}

void Game::start()
{
    _window.create(sf::VideoMode(W_WIDTH, W_HEIGHT), APP_NAME);
    _current_screen = new Screen();
    while (_window.isOpen()) {
        event_();
        update_();
        draw_();
    }
}

void Game::event_()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        switch(event.type) {
        case sf::Event::Closed:
            _window.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Escape)
            {
                _window.close();
            }
            break;
        default:
            break;
        }
    }

    if (_current_screen != NULL) {
        _current_screen->event(event);
    }
}

void Game::update_()
{
    sf::Time deltatime = _clock.restart();
    if (_current_screen != NULL) {
        _current_screen->update(deltatime);
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
        Level::setParameter(mousePos);
    }
}

void Game::draw_()
{
    if (not _window.isOpen()) return;
    _window.clear(sf::Color::Black);

    if (_current_screen != NULL) {
        _window.draw(*_current_screen);
    }

    _window.display();
}
