#include "Timer.h"
#include "SDL.h"
#include <iostream>
Timer* Timer::s_Instance = nullptr;
void Timer::Tick() {
    Uint32 currentTime = SDL_GetTicks();
    m_DeltaTime = (currentTime - m_LastTime) / 1000.0f; // Convert milliseconds to seconds
    m_LastTime = currentTime;
}