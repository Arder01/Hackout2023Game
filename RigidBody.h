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
	}
	void ApplyForce(Vector2d F) { m_Force = F; }
	void ApplyForceX(float F1){ m_Force.X = F1; }//When to bounce Vertically call ApplyForceX(-Fx) no need to do extra calculations
	void ApplyForceY(float F2) { m_Force.Y = F2; }

	void UnsetForce() { m_Force = Vector2d(0,0); }
	
	inline Vector2d GetPosition() { 
		//m_Position.Log();
		//std:: cout << m_Position.X << "X , " << m_Position.Y << "Calculated position" <<std::endl;
		return m_Position;
		
	}
	inline Vector2d GetVelocity() { return m_Velocity; }
	inline Vector2d GetAcceleration() { return m_Acceleration; }
	inline void SetPosition(Vector2d P) { m_Position = P; }
	inline void SetAcceleration(Vector2d A) { m_Acceleration = A; }
	inline void SetVelocity(Vector2d V) { m_Velocity = V; }

	void Update(float dt) {
		m_Acceleration.X = m_Force.X / m_Mass;
		m_Acceleration.Y = (m_Force.Y) / m_Mass + m_Gravity;
		m_Velocity = m_Acceleration;
		m_Position = m_Velocity;
		//std::cout << m_Position.X << " , " << m_Position.Y << std::endl << dt << std::endl;
	}
};