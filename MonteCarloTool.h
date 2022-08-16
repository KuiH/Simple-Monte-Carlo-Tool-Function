#pragma once
#include<future>
#include<functional>

template<typename CheckFn, typename GenFn, typename ... Args>
auto MonteCarlo(std::size_t sample_nums, CheckFn&& check_fn, GenFn&& fn, Args&& ... args) -> std::future<double>
{
	using return_type = typename std::result_of<GenFn(Args...)>::type;
	//check_fn、sample_nums要按值捕获，args ...要按引用捕获，不然有bug。
	auto res = std::async(std::launch::async, [=,&args ...]() ->double { 
		std::size_t hit_times = 0;
		for (std::size_t i = 0; i < sample_nums; ++i)
		{
			return_type sample = std::invoke(std::forward<GenFn>(fn), std::forward<Args>(args)...);
			if ((bool)check_fn(std::forward<return_type>(sample) ))
				hit_times++;
		}
		return 1.0 * hit_times / sample_nums;
	});
	return res;
}