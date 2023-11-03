#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Transform.h"
#include "RigidBody.h"
#include "define.h"
#include "Collision.h"
class Player
{
public:
	RigidBody* m_rigidbody;
	bool IsMoving;
	Player(float x, float y, float w, float h);
public:
	SDL_Rect PDrect,PSrect;
	void Update(float dt);
	void Render();
};

