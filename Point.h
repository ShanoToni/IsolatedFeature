#pragma once

#include <string>

class Point 
{
public:
	Point();
	Point(float posX, float posY, std::string n);

	//get parameters
	inline float getX() { return x; }
	inline float getY() { return y; }
	inline std::string getName() { return name; }	

	~Point();
private:
	float x;
	float y;
	std::string name;
};