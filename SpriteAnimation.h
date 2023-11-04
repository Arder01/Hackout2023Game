#pragma once
#include <iostream>
#include <string>
#include "SDL.h"
#include "Animation.h"
class SpriteAnimation :public Animation
{
public:
	SpriteAnimation(bool repeat = true);
	virtual void Update(float dt);
	void Draw(float x, float y, int spriteWidth, int spriteHeight, float xScale = 1, float yScale = 1);
	void SetProps(std::string textureId, int spriteRow, int frameCount, int speed, SDL_RendererFlip  flip = SDL_FLIP_NONE);

	/*int GetCurrSpriteRow() { return m_SpriteRow; }
	void SetSpriteRow(int row) { m_SpriteRow = row; }
	void IncrSpriteRow() { m_SpriteRow++; }
	void DecrSpriteRow() { m_SpriteRow--; }
	*/
private:
	int m_Speed;
	int m_SpriteRow;
	int m_FrameCount;
	SDL_RendererFlip m_flip;
	std::string m_TextureId;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
};

