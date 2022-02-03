#include<SDL2/SDL_image.h>
#include"Bunny.hpp"
#include"Window.hpp"
#include"RandomGen.hpp"


SDL_Texture* Bunny::spriteTexture = nullptr;

Bunny::Bunny(const ldc::Vector2<float>& pos){
    this->position = pos;
    this->spriteRect.x = this->position.x;
    this->spriteRect.y = this->position.y;

    SDL_QueryTexture(Bunny::spriteTexture, NULL, NULL, &this->spriteRect.w, &this->spriteRect.h);

    this->speed.x = ldc::RandomGen::generate(0, 10) - 5;
    this->speed.y = ldc::RandomGen::generate(0, 20);
}
Bunny::~Bunny(){
}

void Bunny::setTexture(const std::string& path, SDL_Renderer* renderer){
    IMG_Init(IMG_INIT_PNG);
    SDL_Surface* surface = IMG_Load(path.c_str());

    Bunny::spriteTexture = SDL_CreateTextureFromSurface(renderer, surface);
}

void Bunny::update(const ldc::Vector2<int>& viewSize){
    //this->position.x += this->speed.x;
    this->position.y += this->speed.y;
    this->speed.y += this->gravity;

    if(this->position.y < 0){
        this->position.y = 0;
        this->speed.y = 0;
    }
    if(this->position.y > viewSize.y){
        this->position.y = viewSize.y;
        this->speed.y *= -0.95;
    }
    this->spriteRect.x = this->position.x;
    this->spriteRect.y = this->position.y;
}
void Bunny::draw(Window& rw){
    rw.drawTexture(*this->spriteTexture, this->spriteRect);    
}