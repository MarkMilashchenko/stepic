#include <iostream>
#include "unit_5_3.h"

namespace unit_5_3
{	
	void test()
	{
		std::cout << unit_5_3::Fib<10>::value << '\n';
		
		using primes = unit_5_3::IntList<2,3,5,7,11,13, 12>;
		constexpr int head = primes::Head;
		//using odd_primes = primes::Tail;
		
		std::cout << "Head: " << head << " Length: " << unit_5_3::Length<primes>::value << '\n';
	}
}
