#include "SpriteAnimation.h"
#include "TextureManager.h"
#include "Animation.h"

SpriteAnimation::SpriteAnimation(bool repeat) :Animation(repeat) {}

void SpriteAnimation::Draw(float x, float y, int width, int height, float xScale, float yScale) {
	TextureManager::GetInstance()->DrawFrame(m_TextureId, x, y, width, height, m_SpriteRow, GetCurrentFrame(), m_flip);
}

void SpriteAnimation::Update(float dt) {
	SetCurrentFrame((SDL_GetTicks() / m_Speed) % m_FrameCount);
}

void SpriteAnimation::SetProps(std::string textureID, int spriteRow, int frameCount, int speed, SDL_RendererFlip  flip) {
	m_Speed = speed;
	m_TextureId = textureID;
	m_SpriteRow = spriteRow;
	m_FrameCount = frameCount;
	m_flip = flip;
}