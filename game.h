#ifndef GAME_H
#define GAME_H

#include "jack.h"
#include "nam_trieu.h"
#include "obstacle.h"

#include <SDL_mixer.h>
#include <SDL.h>
#include <vector>

class Game {
public:
    Game();
    ~Game();
    bool init();
    void run();
    void close();

private:
    Mix_Music* backgroundMusic;
    Mix_Chunk* eatSound;

    SDL_Texture* backgroundTexture;
    SDL_Texture* menuTexture;
    SDL_Texture* headTexture;
    SDL_Texture* bodyTexture;
    SDL_Texture* foodTexture;
    SDL_Texture* buttonTexture;
    SDL_Texture* gameOverTexture;
    SDL_Texture* digitTextures[10];
    SDL_Texture* kTexture;
    SDL_Texture* iTexture;
    SDL_Texture* cTexture;
    SDL_Texture* mTexture;
    SDL_Texture* tTexture;
    SDL_Texture* hTexture;
    SDL_Texture* i2Texture;
    SDL_Texture* eTexture;
    SDL_Texture* nTexture;
    SDL_Texture* aTexture;
    SDL_Texture* dashTexture;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    Jack snake;
    NamTrieu food;
    std::vector<Obstacle> obstacles;
    void cleanup();
    void cleanUpOnError();
    void update();
    void renderScore();
    void showMenu();
    void showGameOver();
    int score;
};

#endif
