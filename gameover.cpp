#include "gameover.h"

bool GameOver::checkWallCollision(const SDL_Rect& head, int screenWidth, int screenHeight) {
    if (head.x < 0 || head.x >= screenWidth || head.y < 0 || head.y >= screenHeight) {
        return true;
    }
    return false;
}

bool GameOver::checkSelfCollision(const std::vector<SDL_Rect>& body) {
    for (size_t i = 1; i < body.size(); i++) {
        if (SDL_HasIntersection(&body[0], &body[i])) {
            return true;
        }
    }
    return false;
}

