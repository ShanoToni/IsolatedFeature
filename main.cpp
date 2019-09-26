#include <iostream>
#include <string>

#include "InputLoader.h"
#include "Quadtree.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	string src = "";

	//check for parameters
	if (argc < 2) 
	{
		//ask for input
		std::cout << "Argument not provided!" << std::endl;
		std::cout << "Source path: ";
		std::cin >> src;
	}
	else if(argc > 3)
	{
		//handle too many arguments
		std::cerr << "Too many arguments" << std::endl;
		return 1;
	}
	else
	{
		src = argv[1];
	}
	

	//read file from source
	InputLoader loader = InputLoader(src);

	//create a Quadtree (Values changed to a scale from [0..10] for ease )
	Quadtree qt = Quadtree(10 / 2.0f, 10 / 2.0f, 10 / 2.0f, 10 / 2.0f, 2);

	//pass points to quadTree
	for (auto p : loader.getPoints())
	{
		qt.addPoint(p);
	}

	//check all points for the distance to nearest neighbours
	//store the name of the point with the largest distance
	string isolated = "";
	float largestDist = 0.0f;
	for (auto p : loader.getPoints())
	{
		if (qt.minimumDistance(p, qt.NNDistance(p)) > largestDist)
		{
			largestDist = qt.minimumDistance(p, qt.NNDistance(p));
			isolated = p->getName();
		}
	}

	cout << "The most isolated feature is: " << isolated <<" Distance is : "<<largestDist<< endl;
	system("pause");
}