//https://stepik.org/lesson/58812/step/5?unit=36393
#pragma once

namespace unit_5_3 {
	template<int N>
	struct Fib
	{ static int const value = (Fib<N - 1>::value + Fib<N - 2>::value); };
	
	template<>
	struct Fib<1>
	{ static int const value = 1; };
	
	template<>
	struct Fib<0>
	{ static int const value = 0; };
	
	void test();
}

