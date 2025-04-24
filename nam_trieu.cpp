#include "nam_trieu.h"
#include <cstdlib>

NamTrieu::NamTrieu(int x, int y, int size) {
    rect.x = x;
    rect.y = y;
    rect.w = rect.h = size;
}

void NamTrieu::setTexture(SDL_Texture* texture) {
    foodTexture = texture;
}

SDL_Rect NamTrieu::getRect() const {
    return rect;
}

void NamTrieu::render(SDL_Renderer* renderer) {
    SDL_Rect destRect = rect;
    destRect.w = 20;
    destRect.h = 20;
    if (foodTexture) {
        SDL_RenderCopy(renderer, foodTexture, NULL, &destRect);
    }
}

void NamTrieu::respawn(const std::vector<SDL_Rect>& snakeBody) {
    std::vector<SDL_Point> freePositions;
    for (int x = 0; x < 640; x += 20) {
        for (int y = 0; y < 480; y += 20) {
            bool isFree = true;
            SDL_Rect temp = {x, y, 20, 20};
            for (const auto& segment : snakeBody) {
                if (SDL_HasIntersection(&temp, &segment)) {
                    isFree = false;
                    break;
                }
            }
            if (isFree) freePositions.push_back({x, y});
        }
    }
    if (!freePositions.empty()) {
        int idx = rand() % freePositions.size();
        rect.x = freePositions[idx].x;
        rect.y = freePositions[idx].y;
    }
}

