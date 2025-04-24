#include "game.h"
#include "gameover.h"
#include "obstacle.h"
#include <SDL_image.h>
#include <string>


Game::Game() : food(200, 200, 20), score(0) {
    window = nullptr;
    renderer = nullptr;
    running = true;
    headTexture = nullptr;
    bodyTexture = nullptr;
    foodTexture = nullptr;
    backgroundTexture = nullptr;
    menuTexture = nullptr;
    buttonTexture = nullptr;
    gameOverTexture = nullptr;
    kTexture = iTexture = cTexture = mTexture = nullptr;
    tTexture = hTexture = i2Texture = eTexture = nTexture = aTexture = dashTexture = nullptr;
    for (int i = 0; i < 10; ++i) digitTextures[i] = nullptr;
    backgroundMusic = nullptr;
    eatSound = nullptr;

}


Game::~Game() {
    close();
}

void Game::cleanUpOnError() {
    if (headTexture) SDL_DestroyTexture(headTexture);
    if (bodyTexture) SDL_DestroyTexture(bodyTexture);
    if (foodTexture) SDL_DestroyTexture(foodTexture);
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (menuTexture) SDL_DestroyTexture(menuTexture);
    if (buttonTexture) SDL_DestroyTexture(buttonTexture);
    if (gameOverTexture) SDL_DestroyTexture(gameOverTexture);
    if (kTexture) SDL_DestroyTexture(kTexture);
    if (iTexture) SDL_DestroyTexture(iTexture);
    if (cTexture) SDL_DestroyTexture(cTexture);
    if (mTexture) SDL_DestroyTexture(mTexture);
    if (tTexture) SDL_DestroyTexture(tTexture);
    if (hTexture) SDL_DestroyTexture(hTexture);
    if (i2Texture) SDL_DestroyTexture(i2Texture);
    if (eTexture) SDL_DestroyTexture(eTexture);
    if (nTexture) SDL_DestroyTexture(nTexture);
    if (aTexture) SDL_DestroyTexture(aTexture);
    if (dashTexture) SDL_DestroyTexture(dashTexture);
    for (int i = 0; i < 10; ++i)
        if (digitTextures[i]) SDL_DestroyTexture(digitTextures[i]);
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}

bool Game::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    window = SDL_CreateWindow("Jack&5tr", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) return false;

    headTexture = IMG_LoadTexture(renderer, "assets/images/jack.png");
    if (!headTexture) return false;
    bodyTexture = IMG_LoadTexture(renderer, "assets/images/dom_dom.png");
    if (!bodyTexture) return false;
    foodTexture = IMG_LoadTexture(renderer, "assets/images/nam_trieu.png");
    if (!foodTexture) return false;
    backgroundTexture = IMG_LoadTexture(renderer, "assets/images/background.png");
    if (!backgroundTexture) return false;
    menuTexture = IMG_LoadTexture(renderer, "assets/images/menu.png");
    if (!menuTexture) return false;
    buttonTexture = IMG_LoadTexture(renderer, "assets/images/nut.png");
    if (!buttonTexture) return false;
    gameOverTexture = IMG_LoadTexture(renderer, "assets/images/thua.png");
    if (!gameOverTexture) return false;
    kTexture = IMG_LoadTexture(renderer, "assets/obstacles/K.png");
    if (!kTexture) return false;
    iTexture = IMG_LoadTexture(renderer, "assets/obstacles/I.png");
    if (!iTexture) return false;
    cTexture = IMG_LoadTexture(renderer, "assets/obstacles/C.png");
    if (!cTexture) return false;
    mTexture = IMG_LoadTexture(renderer, "assets/obstacles/M.png");
    if (!mTexture) return false;
    tTexture = IMG_LoadTexture(renderer, "assets/obstacles/T.png");
    if (!tTexture) return false;
    hTexture = IMG_LoadTexture(renderer, "assets/obstacles/H.png");
    if (!hTexture) return false;
    i2Texture = IMG_LoadTexture(renderer, "assets/obstacles/I2.png");
    if (!i2Texture) return false;
    eTexture = IMG_LoadTexture(renderer, "assets/obstacles/E.png");
    if (!eTexture) return false;
    nTexture = IMG_LoadTexture(renderer, "assets/obstacles/N.png");
    if (!nTexture) return false;
    aTexture = IMG_LoadTexture(renderer, "assets/obstacles/A.png");
    if (!aTexture) return false;
    dashTexture = IMG_LoadTexture(renderer, "assets/obstacles/dash.png");
    if (!dashTexture) return false;

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        return false;
    }
    backgroundMusic = Mix_LoadMUS("assets/sounds/ThienLyOi.mp3");
    if (!backgroundMusic) return false;
    Mix_PlayMusic(backgroundMusic, -1);

    eatSound = Mix_LoadWAV("assets/sounds/an.mp3");
    if (!eatSound) return false;

    for (int i = 0; i < 10; ++i) {
        std::string path = "assets/scores/" + std::to_string(i) + ".png";
        digitTextures[i] = IMG_LoadTexture(renderer, path.c_str());
        if (!digitTextures[i]) return false;
    }

    if (!headTexture || !bodyTexture || !foodTexture || !backgroundTexture || !menuTexture) return false;

    snake.setTextures(headTexture, bodyTexture);
    food.setTexture(foodTexture);

    obstacles.emplace_back("K-ICM", 100, 100, 20, false, 5);
    obstacles[0].setTextures({kTexture, dashTexture, iTexture, cTexture, mTexture});
    obstacles.emplace_back("THIÊN-AN", 200, 200, 20, true, 5);
    obstacles[1].setTextures({tTexture, hTexture, i2Texture, eTexture, nTexture, dashTexture, aTexture, nTexture});

    return true;
}

void Game::showMenu() {
    SDL_Event e;
    bool inMenu = true;

    SDL_Rect buttonRect = { 100, 50, 200, 60 };

    while (inMenu) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                inMenu = false;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w &&
                    y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
                    inMenu = false;
                }
            }
            if (e.type == SDL_KEYDOWN) {
                inMenu = false;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, menuTexture, NULL, NULL);
        SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
        SDL_RenderPresent(renderer);
    }
}

void Game::showGameOver() {
    SDL_Event e;
    bool inGameOver = true;

    while (inGameOver) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
                inGameOver = false;
            }
            if (e.type == SDL_KEYDOWN) {
                inGameOver = false;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, gameOverTexture, NULL, NULL);
        renderScore();
        SDL_RenderPresent(renderer);
    }
}

void Game::renderScore() {
    int x = 10, y = 10;
    std::string scoreStr = std::to_string(score);

    for (char c : scoreStr) {
        int digit = c - '0';
        SDL_Rect dest = { x, y, 20, 30 };
        SDL_RenderCopy(renderer, digitTextures[digit], NULL, &dest);
        x += 22;
    }
}

void Game::run() {
    showMenu();

    SDL_Event e;
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
            snake.handleEvent(e);
        }

        snake.move();
        SDL_Rect head = snake.getBody()[0];

        bool collisionWithObstacle = false;
        for (const auto& obstacle : obstacles) {
            for (const auto& rect : obstacle.getRects()) {
                if (SDL_HasIntersection(&head, &rect)) {
                    collisionWithObstacle = true;
                    break;
                }
            }
            if (collisionWithObstacle) break;
        }

        if (GameOver::checkWallCollision(head, 640, 480) ||
            GameOver::checkSelfCollision(snake.getBody()) ||
            collisionWithObstacle) {
            SDL_Log("GAME OVER! Score: %d", score);
            showGameOver();
            snake = Jack();
            snake.setTextures(headTexture, bodyTexture);
            food = NamTrieu(200, 200, 20);
            food.setTexture(foodTexture);
            score = 0;
            obstacles.clear();
            obstacles.emplace_back("K-ICM", 100, 100, 20, false, 5);
            obstacles[0].setTextures({kTexture, dashTexture, iTexture, cTexture, mTexture});
            obstacles.emplace_back("THIÊN-AN", 200, 200, 20, true, 5);
            obstacles[1].setTextures({tTexture, hTexture, i2Texture, eTexture, nTexture, dashTexture, aTexture, nTexture});
            showMenu();
            continue;
        }

        update();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, nullptr);
        snake.render(renderer);
        food.render(renderer);

        for (auto& obstacle : obstacles) {
            obstacle.render(renderer);
        }
        renderScore();
        SDL_RenderPresent(renderer);
        SDL_Delay(150);
    }
}

void Game::update() {
    SDL_Rect foodRect = food.getRect();
    SDL_Rect head = snake.getBody()[0];

    if (SDL_HasIntersection(&head, &foodRect)) {
        food.respawn(snake.getBody());
        score += 5;
        Mix_PlayChannel(-1, eatSound, 0);
        snake.getBody().push_back(snake.getBody().back());
    }

    for (auto& obstacle : obstacles) {
        obstacle.move(640, 480);
    }
}

void Game::close() {
    if (headTexture) SDL_DestroyTexture(headTexture);
    if (bodyTexture) SDL_DestroyTexture(bodyTexture);
    if (foodTexture) SDL_DestroyTexture(foodTexture);
    if (backgroundTexture) SDL_DestroyTexture(backgroundTexture);
    if (menuTexture) SDL_DestroyTexture(menuTexture);
    if (buttonTexture) SDL_DestroyTexture(buttonTexture);
    if (gameOverTexture) SDL_DestroyTexture(gameOverTexture);
    if (kTexture) SDL_DestroyTexture(kTexture);
    if (iTexture) SDL_DestroyTexture(iTexture);
    if (cTexture) SDL_DestroyTexture(cTexture);
    if (mTexture) SDL_DestroyTexture(mTexture);
    if (tTexture) SDL_DestroyTexture(tTexture);
    if (hTexture) SDL_DestroyTexture(hTexture);
    if (i2Texture) SDL_DestroyTexture(i2Texture);
    if (eTexture) SDL_DestroyTexture(eTexture);
    if (nTexture) SDL_DestroyTexture(nTexture);
    if (aTexture) SDL_DestroyTexture(aTexture);
    if (dashTexture) SDL_DestroyTexture(dashTexture);
    for (int i = 0; i < 10; ++i)
        if (digitTextures[i]) SDL_DestroyTexture(digitTextures[i]);
    Mix_FreeMusic(backgroundMusic);
    Mix_FreeChunk(eatSound);
    Mix_CloseAudio();

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
