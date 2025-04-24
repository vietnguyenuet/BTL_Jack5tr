#ifndef NAM_TRIEU_H
#define NAM_TRIEU_H

#include <SDL.h>
#include <vector>

class NamTrieu {
public:
    NamTrieu(int x, int y, int size);
    void setTexture(SDL_Texture* texture);
    void render(SDL_Renderer* renderer);
    void respawn(const std::vector<SDL_Rect>& snakeBody);
    SDL_Rect getRect() const;
private:
    SDL_Texture* foodTexture;
    SDL_Rect rect;
};

#endif
