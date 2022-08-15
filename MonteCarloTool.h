#pragma once
#include<future>
#include<functional>

template<typename CheckFn, typename GenFn, typename ... Args>
auto MonteCarlo(std::size_t times, CheckFn&& check_fn, GenFn&& fn, Args&& ... args) -> std::future<double>
{
	using return_type = typename std::result_of<GenFn(Args...)>::type;
	auto res = std::async(std::launch::async, [=]() ->double {			
		std::size_t hit_times = 0;
		for (std::size_t i = 0; i < times; ++i)
		{
			return_type sample = std::invoke(std::forward<GenFn>(fn), std::forward<Args>(args)...);
			if (check_fn(std::forward<return_type>(sample) ))
				hit_times++;
		}
		return 1.0 * hit_times / times;
	});
	return res;
}