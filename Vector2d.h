#pragma once
#include <string>
#include <iostream>
class Vector2d
{
public:
	float X, Y;
public:

	Vector2d(float x = 0, float y = 0)
	{
		//std :: cout << "came in constructor" << std::endl;
		X = x;
		Y = y;
	}

public:
	//addition
	inline Vector2d operator+ (const Vector2d& v2) const
	{
		return  Vector2d(X + v2.X, Y + v2.Y);
	}
	//substracction 
	inline Vector2d operator- (const Vector2d& v2) const
	{
		return Vector2d(X - v2.X, Y - v2.Y);
	}

	//multiplication

	inline Vector2d operator* (const float scaler) const
	{
		return Vector2d(X * scaler, Y * scaler);
	}

	void Log(std::string msg = "") {
		std::cout << msg << "(X Y) - (" << X << " " << Y << ")" << std::endl;
	}
};