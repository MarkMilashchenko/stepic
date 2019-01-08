#include <iostream>
#include <tuple>
#include "unit_5_3.h"

namespace unit_5_3
{	
	void test()
	{
		std::cout << unit_5_3::Fib<10>::value << '\n';
		
		using primes = unit_5_3::IntList<2,3,5,7,11,13,12>;
		constexpr int head = primes::Head;
		//using odd_primes = primes::Tail;
		
		std::cout << "Head: " << head << " Length: " << unit_5_3::Length<primes>::value << '\n';
		
		using L1 = unit_5_3::IntList<2,3,4>;
		using L2 = unit_5_3::IntCons<1, L1>::type;   // IntList<1,2,3,4>

		std::cout << "Head: " << L2::Head << " Length: " << unit_5_3::Length<L2>::value << '\n';
		using L3 = unit_5_3::Generate<5>::type;      // IntList<0,1,2,3,4>
		std::cout << "Head: " << L3::Head << " Length: " << unit_5_3::Length<L3>::value << '\n';
	
		auto f = [](int x, double y, double z) { return x + y + z; };
		auto t = std::make_tuple(30, 5.0, 1.6);  // std::tuple<int, double, double>
		auto res = unit_5_3::apply(f, t);                // res = 36.6
		std::cout << res << "\n";

		// два списка одной длины
		using L4 = unit_5_3::IntList<1,2,3,4,5>;
		using L5 = unit_5_3::IntList<1,3,7,7,2>;

		// результат применени€ Ч список с поэлементными суммами
		using L6 = unit_5_3::Zip<L4, L5, unit_5_3::Plus>::type;  // IntList<2, 5, 10, 11, 7>
		std::cout << "Head: " << L6::Head << " Length: " << unit_5_3::Length<L6>::value << '\n';

//		using NumberQ = unit_5_3::Quantity<unit_5_3::Dimension<>>;
//		using LengthQ = unit_5_3::Quantity<unit_5_3::Dimension<1>>;
//		using MassQ = unit_5_3::Quantity<unit_5_3::Dimension<0, 1>>;
//		using TimeQ = unit_5_3::Quantity<unit_5_3::Dimension<0, 0, 1>>;
//		using VelocityQ = unit_5_3::Quantity<unit_5_3::Dimension<1, 0, -1>>;
//		using AccelQ = unit_5_3::Quantity<unit_5_3::Dimension<1, 0, -2>>;
//		using ForceQ = unit_5_3::Quantity<unit_5_3::Dimension<1, 1, -2>>;
		
	}
}
