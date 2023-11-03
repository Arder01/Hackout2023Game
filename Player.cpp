#include "Player.h"
#include "Vector2d.h"
#include "Transform.h"
#include "Engine.h"
#include "Input.h"


Player::Player(float x, float y,float w = PWidth,float h = PHeight) {
	PDrect.x = x;
	PDrect.y = y;
	PDrect.w = w;
	PDrect.h = h;
	m_rigidbody = new RigidBody();
}

void Player::Update(float dt) {
	m_rigidbody->UnsetForce();
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_D)) {
		m_rigidbody->ApplyForceX(Fx * Backward);
		IsMoving = true;
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_A)) {
		m_rigidbody->ApplyForceX(Fx*Forward);
		IsMoving = true;
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_W)) {
		m_rigidbody->ApplyForceY(Fy * UP);
	}
	if (Input::GetInstance()->GetKeyDown(SDL_SCANCODE_S)) {
		m_rigidbody->ApplyForceY(Fy * DOWN);
	}
	m_rigidbody->Update(dt);
	SDL_Rect temp = PDrect;
	temp.x = PDrect.x + m_rigidbody->GetPosition().X;
	if (Collision::GetInstance()->CheckCollision(temp)) {
		//float temp2 = 0-m_rigidbody->GetPosition().X;
		m_rigidbody->SetPosition({0,m_rigidbody->GetPosition().Y});
	}
	temp = PDrect;
	temp.y = PDrect.y + m_rigidbody->GetPosition().Y;
	if (Collision::GetInstance()->CheckCollision(temp)) {
		float temp2 = 0;
		if (m_rigidbody->GetPosition().Y < 0) {
			//temp2 = 0 - m_rigidbody->GetPosition().Y;
		}
		m_rigidbody->SetPosition({ m_rigidbody->GetPosition().X,temp2});
	}
	PDrect.x += m_rigidbody->GetPosition().X;
	//std::cout << "PDrect x after addition"<<PDrect.x<< std::endl;
	//std::cout << m_rigidbody->GetPosition().X << " , " << m_rigidbody->GetPosition().Y << std::endl;
	//std::cout << PDrect.x << " " << PDrect.y << std::endl;
	if (PDrect.x <= 0) 
		PDrect.x = 0;
	if (PDrect.x > (SWidth - PDrect.w)) 
		PDrect.x = SWidth - PDrect.w;
	PDrect.y += m_rigidbody->GetPosition().Y;
	if (PDrect.y <= 0) 
		PDrect.y = 0;
	if (PDrect.y > SHeight - PDrect.h) 
		PDrect.y = SHeight - PDrect.h;
}
void Player::Render() {
	SDL_Surface* pimg = IMG_Load("Assets/Player/Player.png");
	if (pimg == NULL) {
		SDL_Log("Error rendereing Player.png :%s", SDL_GetError());
	}
	SDL_Texture* playerTex = SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), pimg);
	if (playerTex == NULL) SDL_Log("Error Converting png to texture :%s", SDL_GetError());
	PSrect = {0,0,PHeight,PWidth};
	SDL_RenderDrawRect(Engine::GetInstance()->GetRender(), &PDrect);
	SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), playerTex, &PSrect, &PDrect, 0, nullptr, SDL_FLIP_NONE);
}