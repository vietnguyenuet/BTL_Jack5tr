#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>
#include <vector>
#include <string>

class Obstacle {
public:
    Obstacle(const std::string& text, int startX, int startY, int size, bool moveHorizontal, int speed);
    void setTextures(const std::vector<SDL_Texture*>& textures);
    void move(int screenWidth, int screenHeight);
    void render(SDL_Renderer* renderer);
    std::vector<SDL_Rect> getRects() const;

private:
    std::vector<SDL_Texture*> characterTextures;
    std::vector<SDL_Rect> characterRects;
    int speed;
    bool moveHorizontal;
};

#endif
