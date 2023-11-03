#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Engine.h"
#include "Timer.h"

int main(int argc, char** argv) {
	Engine::GetInstance()->Init();
	while (Engine::GetInstance()->IsRunning())
	{
        Timer::GetInstance()->Tick();
        Engine::GetInstance()->Events();
		Engine::GetInstance()->Update();
		Engine::GetInstance()->Render(); 
	}
	return 0;
}

/*enum CollisionDirection {
    NoCollision,
    CollisionLeft,
    CollisionRight,
    CollisionTop,
    CollisionBottom
};*/

/*int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
        return -1;
    }

    // Create a window and renderer
    SDL_Window* window = SDL_CreateWindow("SDL Line and Rect Collision", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,1280,720, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Define the rectangle
    SDL_Rect rect = { 0, 0, 200, 100 };

    // define the endpoints of the line
    int x1 = 100, y1 = 300;
    int x2 = 400, y2 = 300;

    // Main loop
    bool quit = false;
    SDL_Event e;

    while (true) {
        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw the rect
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawRect(renderer, &rect);//draws a outline of rect, to draw filled rect, use SDL_RenderFillRect;
        // Present the renderer
        SDL_RenderPresent(renderer);
    }

    // Cleanup and quit SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}*/