#include"MonteCarloTool.h"
#include<iostream>
#include<random>


std::default_random_engine engine(time(0));
std::uniform_real_distribution<double> unifrom(0, 1);

struct Point
{
	double x, y;
};

Point generate_point()
{
	double x = unifrom(engine);
	double y = unifrom(engine);
	Point point{ x , y };
	return point;
}

bool check_distance(const Point& p)
{
	// distance = sqrt(x^2+y^2)
	return std::sqrt(std::pow(p.x,2)+std::pow(p.y,2)) <= 1.0;
}

int main()
{
	auto res = MonteCarlo(50000,check_distance, generate_point);	
	double p = res.get();
	double PI = 4 * p;
	std::cout << PI;
	return 0;
}