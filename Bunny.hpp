#include"Vector.hpp"
#include<SDL2/SDL.h>
#include<string>

class Window;

class Bunny{
private:
    ldc::Vector2<float> position;
    SDL_Rect spriteRect;
    ldc::Vector2<float> speed;
    float gravity = .75;
    static SDL_Texture* spriteTexture;

public:
    Bunny(const ldc::Vector2<float>& pos);
    ~Bunny();

    static void setTexture(const std::string& path, SDL_Renderer* renderer);
    
    void update(const ldc::Vector2<int>& viewSize);
    void draw(Window& rw);
};