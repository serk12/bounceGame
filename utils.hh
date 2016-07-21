#ifndef UTILS_HH
#define UTILS_HH

#include <iostream>
#include <list>
#include <fstream>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>

#define W_WIDTH 512
#define W_HEIGHT 512
#define APP_NAME "ZERO GRAVITY"

static const float SUELO        = 999.0f;
enum Dir {NOTHING = 0, UP = 1, DOWN = -1, LEFT = -2, RIGHT = 2, UL, UR, DL, DR};


#endif // UTILS_HH
