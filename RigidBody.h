#pragma once
#include "Vector2d.h"
#include <iostream>
#include "define.h"


class RigidBody {

public:
	float m_Gravity, m_Mass;
	Vector2d m_Force;
	Vector2d m_Friction;
	Vector2d m_Acceleration;
	Vector2d m_Velocity;
	Vector2d m_Position;
	RigidBody() {
		m_Mass = Mass;
		m_Gravity = Gravity;
		m_Acceleration = Vector2d(0, m_Gravity);
	}

	inline Vector2d GetPosition() {
		//m_Position.Log();
		//std:: cout << m_Position.X << "X , " << m_Position.Y << "Calculated position" <<std::endl;
		return m_Position;

	}
	inline Vector2d GetVelocity() { return m_Velocity; }
	inline void ApplyJumpVelocity(Vector2d v) { m_Velocity = v; }
	inline void ApplyVelocity(float F) { m_Velocity.X = F; }

	void Update(float dt) {
		m_Position = m_Velocity * dt + m_Acceleration * dt * dt;
		m_Velocity = m_Velocity + m_Acceleration * dt;
		//m_Position.Log();
		//std::cout << m_Position.X << " , " << m_Position.Y << std::endl << dt << std::endl;
	}
};