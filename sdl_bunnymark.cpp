#include<iostream>
#include<thread>
#include<vector>
#include<string>
#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>

#include"Window.hpp"
#include"Bunny.hpp"
#include"RandomGen.hpp"

#define AMOUNT_OF_BUNNIES 100000

int main(int argc, char** args){
    argc++; args++;
    Window w("SDL Bunnymark", ldc::Vector2<int>{1280, 720});
    TTF_Init();
    TTF_Font* robotoFont = TTF_OpenFont("../Roboto-Regular.ttf", 30);
    SDL_Color textColor = {255, 0, 0, SDL_ALPHA_OPAQUE};
    Bunny::setTexture("../rabbitv3.png", w.getRenderer());
    
    std::vector<Bunny*> bunnies(AMOUNT_OF_BUNNIES);
    for(int i = 0; i < AMOUNT_OF_BUNNIES; i++){
        bunnies[i] = new Bunny(ldc::Vector2<float>{
            ldc::RandomGen::generate(0, w.getViewportSize().x),
            ldc::RandomGen::generate(100, 200)
        });
    }
    
    SDL_Rect fpsTextRect = {.x = 0, .y = 0, .w = 30, .h = 30};
    SDL_Rect countTextRect = {.x = 0, .y = 30, .w = 200, .h = 30};

    SDL_Event event;
    uint64_t current = 0;
    uint64_t last = 0;
    while(w.isOpen()){
        while(w.pollEvent(event)){
            if(event.type == SDL_EventType::SDL_QUIT){
                w.close();
            }
        }
        current = SDL_GetPerformanceCounter();
        SDL_Surface* fpsTextSurface = TTF_RenderText_Solid(
            robotoFont, 
            std::to_string(1000/(((current - last)*1000)/SDL_GetPerformanceFrequency())).c_str(),
            textColor);
        last = current;
        
        SDL_Texture* fpsTextTexture = SDL_CreateTextureFromSurface(w.getRenderer(), fpsTextSurface);
        SDL_Surface* countTextSurface = TTF_RenderText_Solid(robotoFont, std::to_string(bunnies.size()).c_str(), textColor);
        SDL_Texture* countTextTexture = SDL_CreateTextureFromSurface(w.getRenderer(), countTextSurface);
        
        w.clear();
        for(Bunny* b : bunnies){
            b->update(w.getViewportSize());
            b->draw(w);
        }
        w.drawTexture(*fpsTextTexture, fpsTextRect);
        w.drawTexture(*countTextTexture, countTextRect);
        w.display();

        SDL_DestroyTexture(fpsTextTexture);
        SDL_FreeSurface(fpsTextSurface);
        SDL_DestroyTexture(countTextTexture);
        SDL_FreeSurface(countTextSurface);
    }
    for(Bunny* b: bunnies){
        delete[] b;
    }
    TTF_CloseFont(robotoFont);
    return 0;
}

/*
int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *surface;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 3;
    }

    if (SDL_CreateWindowAndRenderer(320, 240, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window and renderer: %s", SDL_GetError());
        return 3;
    }

    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT) {
            break;
        }
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
*/