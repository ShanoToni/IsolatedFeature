#pragma once
#include <vector>
#include <iostream>

#include "Point.h"

class AABB 
{
public:
	AABB() {};
	AABB(float xPos, float yPos, float halfWidth, float HalfHeight);
	
	bool doesContain(Point *p);

	//getters
	float getX() { return x; }
	float getY() { return y; }
	float getHalfW(){ return halfW; }
	float getHalfH(){ return halfH; }

	~AABB() {};

private:
	float x;
	float y;

	float halfW;
	float halfH;

};


class Quadtree
{
public:
	Quadtree();

	Quadtree(float x, float y, float w, float h, int cap);

	bool addPoint(Point * p);
	
	void subDivide();

	float NNDistance(Point * p);

	std::vector<Point *> query(Point * origin, float r);

	float minimumDistance(Point * p,  float d);


	~Quadtree() {};
private:
	AABB bound;
	int capacity;
	bool divided;
	std::vector<Point*> points;

	bool intersectWithSphere(Point * origin, float r);
	bool pointInSphere(Point * p, Point * origin, float r);

	Quadtree * topRight;
	Quadtree * topLeft;
	Quadtree * bottomRight;
	Quadtree * bottomLeft;

};