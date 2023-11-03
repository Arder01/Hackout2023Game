#pragma once
#include "Input.h"
#include "Engine.h"
#include <iostream>
Input* Input::s_Instance = nullptr;

Input::Input() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}

void Input::Listen() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			Engine::GetInstance()->Quit(); 
			break;
		}
		else if (event.type == SDL_KEYUP) {
			KeyUp(); 
			break;
		}
		else if (event.type == SDL_KEYDOWN) {
			KeyDown();
			break;
		}
	}
}

bool Input::GetKeyDown(SDL_Scancode key) {
	if (m_KeyStates[key] == 1) return true;
	else return false;
}

void Input::KeyUp() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}
void Input::KeyDown() {
	m_KeyStates = SDL_GetKeyboardState(nullptr);
}