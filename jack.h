#ifndef JACK_H
#define JACK_H

#include <vector>
#include <SDL.h>

class Jack {
public:
    Jack();
    void setTextures(SDL_Texture* head, SDL_Texture* body);
    void handleEvent(SDL_Event& e);
    void move();
    void render(SDL_Renderer* renderer);
    void checkSelfCollision();
    std::vector<SDL_Rect>& getBody();
    bool isDead() const;

private:
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;
    std::vector<SDL_Rect> body;
    int xVel, yVel;
    bool dead = false;
};

#endif


