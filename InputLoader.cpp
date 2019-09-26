#include "InputLoader.h"

InputLoader::InputLoader(std::string srcPath)
{
	//start reading file
	std::ifstream infile;
	infile.open(srcPath);
	if (infile.fail())
	{
		std::cout << "Could not open file : " << srcPath << std::endl;
	}

	std::string line;
	//parameters in each line
	std::string name;
	float x, y;

	while (infile >> name >> x >> y)
	{
		Point * p = new Point(x / 1000000.0f, y / 1000000.0f, name);

		points.push_back(p);
	}

	infile.close();
}

InputLoader::~InputLoader()
{

}
