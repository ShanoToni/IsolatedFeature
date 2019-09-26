#include "Quadtree.h"

AABB::AABB(float xPos, float yPos, float halfWidth, float HalfHeight)
{
	x = xPos;
	y = yPos;
	halfW = halfWidth;
	halfH = HalfHeight;
}

bool AABB::doesContain(Point * p)
{
	//check if point is inside the AABB
	return (p->getX() < x + halfW && p->getX() > x - halfW &&
		p->getY() < y + halfH && p->getY() > y - halfH);
}

Quadtree::Quadtree()
{
	bound = AABB(0, 0, 0, 0);
	capacity = 0;
	divided = false;

}

Quadtree::Quadtree(float x, float y, float w, float h, int cap)
{
	bound = AABB(x, y, w, h);
	capacity = cap;
	divided = false;

	topLeft = new Quadtree();
	topRight = new Quadtree();
	bottomLeft = new Quadtree();
	bottomRight = new Quadtree();
}

bool Quadtree::addPoint(Point * p)
{
	if (!bound.doesContain(p))
	{
		return false;
	}
	
	if (capacity > points.size() )
	{
		points.push_back(p);
		return true;
	}
	else
	{
		if (!divided)
		{
			subDivide();
		}
		
		if (topLeft->addPoint(p))
		{
			return true;
		}
		else if (topRight->addPoint(p))
		{
			return true;
		}
		else if (bottomLeft->addPoint(p))
		{
			return true;
		}
		else if (bottomRight->addPoint(p))
		{
			return true;
		}
	
	}
}

void Quadtree::subDivide()
{
	//once point limit is reached for node divide into subnodes
	topLeft = new Quadtree(bound.getX() - bound.getHalfW() / 2.0f, bound.getY() + bound.getHalfH() /2.0f, bound.getHalfW() / 2.0f, bound.getHalfH() / 2.0f, capacity);
	topRight = new Quadtree(bound.getX() + bound.getHalfW() / 2.0f, bound.getY() + bound.getHalfH() / 2.0f, bound.getHalfW() / 2.0f, bound.getHalfH() / 2.0f, capacity);
	bottomLeft = new Quadtree(bound.getX() - bound.getHalfW() / 2.0f, bound.getY() - bound.getHalfH() / 2.0f, bound.getHalfW() / 2.0f, bound.getHalfH() / 2.0f, capacity);
	bottomRight = new Quadtree(bound.getX() + bound.getHalfW() / 2.0f, bound.getY() - bound.getHalfH() / 2.0f, bound.getHalfW() / 2.0f, bound.getHalfH() / 2.0f, capacity);
	divided = true;
}

float Quadtree::NNDistance(Point * p)
{
	//initialize output with a value easily overriden
	float distance = 20;
	//is the point the the current node's bounds
	if (!bound.doesContain(p) || points.size() == 0)
	{
		return 0.0f;
	}
	//check the distance of each point
	for (auto point : points)
	{
		float tempDistance = sqrtf(pow(point->getX() - p->getX(), 2.0f) + pow(point->getY() - p->getY(), 2.0f));
		if (distance > tempDistance && tempDistance > 0.0f)
		{
			distance = tempDistance;
		}
	}

	//check each sub node recursively
	float recDistance = topLeft->NNDistance(p);

	if (recDistance > 0.0f && recDistance < distance)
	{
		distance = recDistance;
	}

	recDistance = topRight->NNDistance(p);

	if (recDistance > 0.0f && recDistance < distance)
	{
		distance = recDistance;

	}

	recDistance = bottomLeft->NNDistance(p);

	if (recDistance > 0.0f && recDistance < distance)
	{
		distance = recDistance;

	}

	recDistance = bottomRight->NNDistance(p);

	if (recDistance > 0.0f && recDistance < distance)
	{
		distance = recDistance;

	}

	return distance;
}

std::vector<Point*> Quadtree::query(Point * origin, float r)
{
	//initialize a vector of points
	std::vector<Point*> found;

	//check if there is an intersection of the bounds
	if (!intersectWithSphere(origin,r)) 
	{
		return found;
	}

	//add any points which are inside the sphere
	for (auto p : points) 
	{
		if (bound.doesContain(p)) 
		{
			found.push_back(p);
		}
	}

	//recursevly add all the points for the subnodes to the main list
	std::vector<Point*> rec1;
	std::vector<Point*> rec2;
	std::vector<Point*> rec3;
	std::vector<Point*> rec4;
	if (divided)
	{
		rec1 = topLeft->query(origin, r);
		rec2 = topRight->query(origin, r);
		rec3 = bottomLeft->query(origin, r);
		rec4 = bottomRight->query(origin, r);
	}

	for (auto p : rec1)
	{
		found.push_back(p);
	}

	for (auto p : rec2)
	{
		found.push_back(p);
	}
	for (auto p : rec3)
	{
		found.push_back(p);
	}

	for (auto p : rec4)
	{
		found.push_back(p);
	}

	return found;
}

float Quadtree::minimumDistance(Point * p, float d)
{

	std::vector<Point *> closerPoints;

	closerPoints = query(p, d);

	float startDistance = d;
	float distance = d;

	//check if any of the points are closer to the checked point
	for (auto point : closerPoints)
	{
		float tempDist = sqrtf(pow(point->getX() - p->getX(), 2.0f) + pow(point->getY() - p->getY(), 2.0f));

		if (tempDist < distance && tempDist> 0.0f)
		{
			distance = tempDist;
		}
	}

	return distance;
	
}

bool Quadtree::intersectWithSphere(Point * origin, float r)
{
	float xDis = abs(bound.getX() - origin->getX());
	float yDis = abs(bound.getY() - origin->getY());

	float w = bound.getHalfW();
	float h = bound.getHalfH();

	float edges = sqrtf(pow((xDis - w), 2) + pow((yDis - h), 2));

	//no intersection
	if (xDis > (r + w) || yDis > (r + h))
	{
		return false;
	}

	// intersection within the circle
	if (xDis <= w || yDis <= h)
	{
		return true;
	}

	//edge intersection
	return edges <= r;
}

bool Quadtree::pointInSphere(Point * p, Point * origin, float r)
{
	float d = sqrtf(pow(origin->getX() - p->getX(), 2.0f) + pow(origin->getY() - p->getY(), 2.0f));
	
	if (d <= r)
	{
		return true;
	}

	return false;
}

