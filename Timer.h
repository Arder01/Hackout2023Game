#pragma once
#include "SDL.h"
const int Target_Fps = 60;
const float Target_DeltaTime = 1.5f;
class Timer
{
public:
	void Tick();
	inline float GetDeltaTime() { return m_DeltaTime; }
	inline static Timer* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new Timer(); }
private:
	Timer() {}
	static Timer* s_Instance;
	float m_DeltaTime = 0.0f;
	Uint32 m_LastTime = 0;
};