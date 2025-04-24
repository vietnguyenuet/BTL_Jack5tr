#include "jack.h"

Jack::Jack() {
    SDL_Rect head = {100, 100, 20, 20};
    body.push_back(head);
    xVel = 20;
    yVel = 0;
}

void Jack::setTextures(SDL_Texture* head, SDL_Texture* body) {
    headTexture = head;
    bodyTexture = body;
}

void Jack::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                if (yVel != 20) {
                    xVel = 0;
                    yVel = -20;
                }
                break;
            case SDLK_DOWN:
                if (yVel != -20) {
                    xVel = 0;
                    yVel = 20;
                }
                break;
            case SDLK_LEFT:
                if (xVel != 20) {
                    xVel = -20;
                    yVel = 0;
                }
                break;
            case SDLK_RIGHT:
                if (xVel != -20) {
                    xVel = 20;
                    yVel = 0;
                }
                break;
        }
    }
}

void Jack::move() {
    for (int i = body.size() - 1; i > 0; i--) {
        body[i] = body[i - 1];
    }
    body[0].x += xVel;
    body[0].y += yVel;
}

void Jack::render(SDL_Renderer* renderer) {
    for (size_t i = 0; i < body.size(); i++) {
        SDL_Rect destRect = body[i];
        SDL_RenderCopy(renderer, (i == 0 ? headTexture : bodyTexture), NULL, &destRect);
    }
}

std::vector<SDL_Rect>& Jack::getBody() {
    return body;
}

void Jack::checkSelfCollision() {
    for (size_t i = 1; i < body.size(); i++) {
        if (SDL_HasIntersection(&body[0], &body[i])) {
            SDL_Log("Jack danh domdom");
            dead = true;
        }
    }
}

bool Jack::isDead() const {
    return dead;
}

