#pragma once
#define SDL_RENDER_DRIVER software
#include<SDL2/SDL.h>
#include"Vector.hpp"


// c++ wrapper class for SDL_Window and SDL_Renderer
class Window{
private:
    bool open = false;
    SDL_Window* windowHandle = nullptr;
    SDL_Renderer* renderer = nullptr;
public:
    Window(const std::string& title, const ldc::Vector2<int>& windowSize);
    ~Window();
    bool isOpen();
    int pollEvent(SDL_Event& event);
    void close();
    void clear();
    void display();
    void drawTexture(SDL_Texture& texture, SDL_Rect bounding);
    SDL_Renderer* getRenderer();

    ldc::Vector2<int> getViewportSize();
};