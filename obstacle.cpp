#include "obstacle.h"

Obstacle::Obstacle(const std::string& text, int startX, int startY, int size, bool moveHorizontal, int speed) {
    this->moveHorizontal = moveHorizontal;
    this->speed = speed;

    for (size_t i = 0; i < text.length(); ++i) {
        SDL_Rect rect;
        rect.w = rect.h = size;
        if (moveHorizontal) {
            rect.x = startX + i * size;
            rect.y = startY;
        } else {
            rect.x = startX;
            rect.y = startY + i * size;
        }
        characterRects.push_back(rect);
    }
}

void Obstacle::setTextures(const std::vector<SDL_Texture*>& textures) {
    characterTextures = textures;
}

void Obstacle::move(int screenWidth, int screenHeight) {
    bool reverse = false;

    for (const auto& rect : characterRects) {
        if (moveHorizontal) {
            if (rect.x <= 0 || rect.x + rect.w >= screenWidth) {
                reverse = true;
                break;
            }
        } else {
            if (rect.y <= 0 || rect.y + rect.h >= screenHeight) {
                reverse = true;
                break;
            }
        }
    }

    if (reverse) {
        speed = -speed;
    }

    for (auto& rect : characterRects) {
        if (moveHorizontal) {
            rect.x += speed;
        } else {
            rect.y += speed;
        }
    }
}

void Obstacle::render(SDL_Renderer* renderer) {
    for (size_t i = 0; i < characterRects.size(); ++i) {
        SDL_RenderCopy(renderer, characterTextures[i], NULL, &characterRects[i]);
    }
}

std::vector<SDL_Rect> Obstacle::getRects() const {
    return characterRects;
}
