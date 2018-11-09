#include <thread>
#include <typeinfo>
#include <list>
#include <iostream>
#include <vector>

namespace unit_5_2
{	
	template<class iter, class F1, class F2>
	auto thread_calculating(iter p, iter q, F1 f1, F2 f2) -> decltype(f1(*p))
	{
		auto answ = f1(*p);
		p++;
		while(p != q)
		{
    		answ = f2(answ, f1(*p));
    		p++;
    	};
		return answ;
	}
	
	template<class iter, class F1, class F2>
	auto map_reduce(iter p, iter q, F1 f1, F2 f2, size_t threads) -> decltype(f1(*p))
	{
		size_t distance = std::distance(p, q);
		int elements_in_thread = distance / threads;
		int elements_in_first_thread = distance - (threads - 1) * elements_in_thread;
		typedef decltype(f1(*p)) result;
		
		iter start_iterator = p;
		iter end_iterator = p;
		for (int i = 0; i < elements_in_first_thread; i++)
			end_iterator++;

		std::thread futures[threads];
		std::vector<result> calc_result(threads);
		futures[0] = std::thread([&calc_result, &start_iterator, &end_iterator, &f1, &f2](){calc_result[0] = thread_calculating<iter, F1, F2>(start_iterator, end_iterator, f1, f2);});
		start_iterator = end_iterator;
		
		for (size_t i = 1; i < threads; i++)
		{
			for (int j = 0; j < elements_in_thread; j++)
				end_iterator++;
			futures[i] = std::thread([&i, &calc_result, &start_iterator, &end_iterator, &f1, &f2]() {calc_result[i] = thread_calculating<iter, F1, F2>(start_iterator, end_iterator, f1, f2);});
			start_iterator = end_iterator;
		};
		
		for (size_t i = 0; i < threads; i++)
			futures[i].join();
				
		result answ = calc_result[0];
		for (size_t i = 1; i < threads; i++)
			answ = f2(answ, calc_result[i]);

		return answ;
	}
	
	void test()
	{
		std::list<int> l = {1,2,3,4};
		// параллельное суммирование в 3 потока
		int sum = map_reduce(l.begin(), l.end(), 
			[](int i){return i;}, std::plus<int>(), 3);
		std::cout << sum << '\n';
		// проверка наличия чётных чисел в четыре потока
		auto has_even = map_reduce(l.begin(), l.end(), 
			[](int i){return i % 2 == 0;}, std::logical_or<bool>(), 4);
		std::cout << has_even << '\n';
	}
}
