#include "Player.h"
#include "Vector2d.h"
#include "Engine.h"
#include "Input.h"


Player::Player(float x, float y, float w = PWidth, float h = PHeight) {
	PDrect.x = x;
	PDrect.y = y;
	PDrect.w = w;
	PDrect.h = h;
	m_Transform.X = x;
	m_Transform.Y = y;
	m_rigidbody = new RigidBody();
	m_Animation = new SpriteAnimation();
}

void Player::Update(float dt) {
	m_Transform.Log();
	static bool spacePressed = false;
	static Uint32 SpaceUp = 0;
	static Uint32 SpaceTime = 0;
	if (IsGrounded) 
	{
		m_rigidbody->ApplyJumpVelocity(Vector2d(0, 0));
		m_Animation->SetProps("Player", 1, 4, 8, SDL_FLIP_NONE);
	}
	else {
		m_Animation->SetProps("Player_Fly", 1, 15, 60, SDL_FLIP_NONE);
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && IsGrounded) {
		if (!spacePressed) {
			spacePressed = true;
			SpaceUp = SDL_GetTicks();
		}
		if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) dir = 1;
		else dir = 0;
	}
	else {
		if (spacePressed and IsGrounded) {
			spacePressed = false;
			SpaceTime = SDL_GetTicks() - SpaceUp;
			//SDL_Log("Space key was held down for %d miliseconds", SpaceTime);
			if (SpaceTime > 2000) SpaceTime = 2000;
			if (IsGrounded && SpaceTime > 0) {
				if (SpaceTime < 1000) {
					m_rigidbody->ApplyJumpVelocity(Vector2d(J4 * dir, J1 * UP));
				}
				else if (SpaceTime < 2000) {
					m_rigidbody->ApplyJumpVelocity(Vector2d(J4 * dir, J2 * UP));
				}
				else {
					m_rigidbody->ApplyJumpVelocity(Vector2d(J4 * dir, J3 * UP));
				}

			}
			IsGrounded = false;
		}
		else if (!spacePressed and !IsGrounded) {
			m_rigidbody->Update(dt);
			SDL_Rect temp = PDrect;
			temp.x = temp.x + m_rigidbody->GetPosition().X;
			if (Collision::GetInstance()->CheckCollision(temp)) {
				m_Transform.X = m_Transform.X - m_rigidbody->GetPosition().X;
				Vector2d vel = m_rigidbody->GetVelocity();
				m_rigidbody->ApplyJumpVelocity(Vector2d(vel.X * (-1), vel.Y));
			}
			else m_Transform.X += m_rigidbody->GetPosition().X;
			temp = PDrect;
			temp.y = temp.y + m_rigidbody->GetPosition().Y;
			if (Collision::GetInstance()->CheckCollision(temp)) {
				if (m_rigidbody->GetPosition().Y > 0) {
					IsGrounded = true;
					m_rigidbody->ApplyJumpVelocity(Vector2d(0, 0));
				}
				else {
					m_Transform.Y -= m_rigidbody->GetPosition().Y;
					Vector2d vel = m_rigidbody->GetVelocity();
					m_rigidbody->ApplyJumpVelocity(Vector2d(vel.X, vel.Y * (-1)));
				}
			}
			else m_Transform.Y += m_rigidbody->GetPosition().Y;
			PDrect.x = m_Transform.X;
			PDrect.y = m_Transform.Y;
			if (PDrect.x <= 0)PDrect.x = 0;
			if (PDrect.x > (SWidth - PDrect.w))	PDrect.x = SWidth - PDrect.w;
			PDrect.y += m_rigidbody->GetPosition().Y;
			if (PDrect.y <= 0)
			{
				PDrect.y = 0;
				Vector2d vel = m_rigidbody->GetVelocity();
				m_rigidbody->ApplyJumpVelocity(Vector2d(vel.X, vel.Y * (-1)));
			}

			if (PDrect.y > SHeight - PDrect.h)
			{
				PDrect.y = SHeight - PDrect.h;
				IsGrounded = true;
			}
		}
		else if (!spacePressed and IsGrounded) {
			if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
				m_rigidbody->ApplyVelocity(Fx * (-1));
				m_rigidbody->Update(dt);
				SDL_Rect temp = PDrect;
				temp.x += m_rigidbody->GetPosition().X;
				if (!Collision::GetInstance()->CheckCollision(temp)) {
					m_Transform.X += m_rigidbody->GetPosition().X;
				}
			}
			else if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
				m_rigidbody->ApplyVelocity(Fx);
				m_rigidbody->Update(dt);
				SDL_Rect temp = PDrect;
				temp.x += m_rigidbody->GetPosition().X;
				if (!Collision::GetInstance()->CheckCollision(temp)) {
					m_Transform.X += m_rigidbody->GetPosition().X;
				}
			}
			else {
				m_rigidbody->ApplyVelocity(0);
				m_rigidbody->Update(dt);
			}
			PDrect.x = m_Transform.X;
			PDrect.y = m_Transform.Y;
			if (PDrect.x <= 0)
			{
				PDrect.x = 0;
				m_Transform.X = 0;
			}
			if (PDrect.x > (SWidth - PDrect.w))
			{
				PDrect.x = SWidth - PDrect.w;
				m_Transform.X = PDrect.x;
			}
			//PDrect.y += m_rigidbody->GetPosition().Y;
			if (PDrect.y <= 0)
			{
				PDrect.y = 0;
				Vector2d vel = m_rigidbody->GetVelocity();
				m_rigidbody->ApplyJumpVelocity(Vector2d(vel.X, vel.Y * (-1)));
			}

			if (PDrect.y > SHeight - PDrect.h)
			{
				PDrect.y = SHeight - PDrect.h;
				IsGrounded = true;
			}
			m_rigidbody->Update(dt);
		}
	}
}
void Player::Render() {
	m_Animation->Draw(m_Transform.X, m_Transform.Y, PWidth, PHeight);
	PSrect = { 0,0,PHeight,PWidth };
	SDL_RenderDrawRect(Engine::GetInstance()->GetRender(), &PDrect);
	/*SDL_Surface* pimg = IMG_Load("Assets/Player/Player.png");
	if (pimg == NULL) {
		SDL_Log("Error rendereing Player.png :%s", SDL_GetError());
	}
	SDL_Texture* playerTex = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), pimg);
	if (playerTex == NULL) SDL_Log("Error Converting png to texture :%s", SDL_GetError());
	SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), playerTex, &PSrect, &PDrect, 0, nullptr, SDL_FLIP_NONE);*/
}