# Simple-Monte-Carlo-Tool-Function

**Languages** 中文|[English](README_EN.md)



这是一个使用C++实现的简单的异步蒙特卡洛算法工具函数



## C++标准: 

C++14



## 使用

```c++
auto res = MonteCarlo(sample_nums,check_sample_funtion, generate_sample_funtion, ...args);	
double p = res.get();
std::cout<<p<<std::endl;
```

**sample_nums:** 需要生成的样本个数。

**check_sample_funtion:** 检测样本是否符合条件。

​											参数: 样本

​											返回值：一个bool值，true表示样本符合条件。

**generate_sample_funtion:** 生成并返回一个样本。其返回值将作为*check_sample_funtion*的参数。

**generate_sample_funtion:** 生成样本的函数。该返回应当返回一个样本

**args:** 传给*generate_sample_funtion*的参数。可以有任意多的参数。若有多个参数，则使用逗号分隔。

**res.get():** 获得结果。返回在给定的样本数量下，符合*check_sample_funtion*函数的样本比例。**get()函数只能被调用一次。**



## 使用示例

```C++
// 使用蒙特卡洛方法计算pi值

#include"MonteCarloTool.h"
#include<iostream>
#include<random>


std::default_random_engine engine(time(0));
std::uniform_real_distribution<double> unifrom(0, 1);

struct Point
{
	double x, y;
};

Point generate_point(int a,int b) //这里的参数没什么用，只是示范如何传入参数
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
    //给generate_point传递参数: a=1,b=2。生成50000个样本
	auto res = MonteCarlo(50000,check_distance, generate_point,1,2); 
	std::cout <<"test";
	double p = res.get();
    double PI = 4 * p;
	std::cout << PI;
	return 0;
}
```

