#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "RigidBody.h"
#include "define.h"
#include "Collision.h"
#include "Vector2d.h"
class Player
{
public:
	RigidBody* m_rigidbody;
	bool IsGrounded = false;
	Vector2d currVel;
	int dir = 0;
	Player(float x, float y, float w, float h);
public:
	Vector2d m_Transform;
	SDL_Rect PDrect, PSrect;
	void Update(float dt);
	void Render();
	float s_JumpTime;
};