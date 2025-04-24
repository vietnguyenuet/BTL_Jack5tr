#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <SDL.h>
#include <vector>
#include "jack.h"

class GameOver {
public:
    static bool checkWallCollision(const SDL_Rect& head, int screenWidth, int screenHeight);
    static bool checkSelfCollision(const std::vector<SDL_Rect>& body);
};

#endif

