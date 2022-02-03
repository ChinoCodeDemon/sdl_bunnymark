#include<iostream>
#include"Window.hpp"

bool isSDLInitialised = false;

Window::Window(const std::string& title, const ldc::Vector2<int>& windowSize){
    if(SDL_Init((SDL_INIT_VIDEO) & (SDL_INIT_VIDEO | SDL_INIT_TIMER)) != false){
        std::cerr << "Couldn't initialize SDL" << std::endl;
        return;
    }
    std::cout << "SDL Initialized." << std::endl;
    this->windowHandle = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSize.x, windowSize.y, SDL_WINDOW_SHOWN);
    if(this->windowHandle == nullptr){
        std::cerr << "Couldn't create window" << std::endl;
        return;
    }
    std::cout << "Window created." << std::endl;
    this->renderer = SDL_CreateRenderer(this->windowHandle, -1, SDL_RENDERER_ACCELERATED);
    if(this->renderer == nullptr){
        std::cerr << "Couldn't create renderer" << std::endl;
        return;
    }
    std::cout << "Renderer created." << std::endl;

    this->open = true;
}

Window::~Window(){
    this->close();
    SDL_DestroyRenderer(this->renderer);
    this->renderer = nullptr;

    SDL_DestroyWindow(this->windowHandle);
    this->windowHandle = nullptr;
}

bool Window::isOpen(){
    return this->open;
}

int Window::pollEvent(SDL_Event& event){
    return SDL_PollEvent(&event);
}

void Window::close(){
    this->open = false;
}

void Window::clear(){
    if(this->renderer == nullptr) return;

    SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(this->renderer);
    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
}

void Window::display(){
    if(this->renderer == nullptr) return;
    
    SDL_RenderPresent(this->renderer);
}

void Window::drawTexture(SDL_Texture& texture, SDL_Rect destination){
    if(this->renderer == nullptr) return;
    
    SDL_RenderCopy(this->renderer, &texture, NULL, &destination);
}

SDL_Renderer* Window::getRenderer(){
    return this->renderer;
}

ldc::Vector2<int> Window::getViewportSize(){
    ldc::Vector2<int> size;
    SDL_GetWindowSize(this->windowHandle, &size.x, &size.y);
    return size;
}