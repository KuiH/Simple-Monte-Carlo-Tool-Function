# Simple-Monte-Carlo-Tool-Function

**Languages** [中文](README.md)|English



This is a simple asynchronous Monte Carlo algorithm tool function implemented using C++



## C++ Standard

C++14



## Usage

```c++
auto res = MonteCarlo(sample_nums, check_sample_funtion, generate_sample_funtion, ...args);	
double p = res.get();
std::cout<<p<<std::endl;
```

**sample_nums:** The number of samples that needs to be generated.

**check_sample_funtion:** To check whether the samples meet the condition.

​											parameter: a sample

​											return：a bool value. It is true if a sample meet the condition

**generate_sample_funtion:** To generate and return a sample. This return value will be the argument of *check_sample_funtion*.

**args:** Arguments of *generate_sample_funtion*. There is no number limitation of these arguments. Using comma to separate them if more than one argus used.

**res.get():** To get the result. It returns the ratio of samples that fulfill the *check_sample_funtion*. ***get()* can be called only once.**



## Example

```C++
// use MonteCarlo algorithm to calculate PI

#include"MonteCarloTool.h"
#include<iostream>
#include<random>


std::default_random_engine engine(time(0));
std::uniform_real_distribution<double> unifrom(0, 1);

struct Point
{
	double x, y;
};

//these params(a,b),is meaningless. It is just an example to show how to use params. 
Point generate_point(int a,int b) 
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
   	//a=1,b=2 are arguments of generate_point. Generate 50000 samples
	auto res = MonteCarlo(50000,check_distance, generate_point,1,2); 
	std::cout <<"test";
	double p = res.get();
   	double PI = 4 * p;
	std::cout << PI;
	return 0;
}
```

