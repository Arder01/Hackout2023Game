#pragma once
#include "SDL.h"
#include <string>
class Animation
{
public:
	Animation(bool repeat = true) : m_Repeat(repeat) { m_IsEnded = false; }
	virtual void  Update(float dt) = 0;
	inline int GetCurrentFrame() { return m_CurrentFrame; }
	inline void SetCurrentFrame(int x) { m_CurrentFrame = x; }
	inline bool IsEnded() { return m_IsEnded; }
	inline void SetIsEnded(bool x) { m_IsEnded = x; }

private:
	//friend class SpriteAnimation;
	//friend class SeqAnimation;
	bool m_Repeat;
	bool m_IsEnded;
	int m_CurrentFrame;
};

