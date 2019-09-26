#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <iostream>

#include "Point.h"
class InputLoader
{
public:
	InputLoader() {};
	InputLoader(std::string srcPath);

	std::vector<Point*> getPoints() { return points; }

	~InputLoader();

private:
	std::vector<Point*> points;
};