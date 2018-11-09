//https://stepik.org/lesson/58810/step/6?unit=36391
#pragma once

namespace unit_5_2 {
	template<class iter, class F1, class F2>
	auto thread_calculating(iter p, iter q, F1 f1, F2 f2) -> decltype(f1(*p));

	template<class iter, class F1, class F2>
	auto map_reduce(iter p, iter q, F1 f1, F2 f2, size_t threads) -> decltype(f1(*p));
	
	void test();
}

