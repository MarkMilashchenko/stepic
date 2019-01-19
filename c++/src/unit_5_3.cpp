#include <iostream>
#include <tuple>
#include "unit_5_3.h"

namespace unit_5_3
{	
	template<typename T>
	Quantity<T>::Quantity(): data(0.0)
	{}
	
	template<typename T>
	Quantity<T>::Quantity(double const & input): data(input)
	{}
	
	template<typename T>
	Quantity<T>::Quantity(Quantity<T> const & input): data(input.value())
	{}
	
	template<typename T>
	Quantity<T> Quantity<T>::operator+(Quantity<T> const & input)
	{
		return Quantity<T>(data + input.value());
	}
	
	template<typename T>
	Quantity<T> Quantity<T>::operator-(Quantity<T> const & input)
	{
		return Quantity<T>(data - input.value());
	}
	
	template<typename T>
	template<typename T2>
	Quantity<typename unit_5_3::Zip<T, T2, unit_5_3::Plus>::type> Quantity<T>::operator*(Quantity<T2> const & input)
	{
		using newDimension = typename unit_5_3::Zip<T, T2, unit_5_3::Plus>::type;
		double newValue = data * input.value();
		return Quantity<newDimension>(newValue);
	};
	
	template<typename T>
	template<typename T2>
	Quantity<typename unit_5_3::Zip<T, T2, unit_5_3::Minus>::type> Quantity<T>::operator/(Quantity<T2> const & input)
	{
		using newDimension = typename unit_5_3::Zip<T, T2, unit_5_3::Minus>::type;
		double newValue = 0.0;
		if (input.value() != 0)
			newValue = data / input.value();
		return Quantity<newDimension>(newValue);
	};
	
	template<typename T>
	Quantity<T> Quantity<T>::operator*(double const & input)
	{
		return Quantity<T>(data * input);
	}
	
	template<typename T>
	Quantity<T> Quantity<T>::operator/(double const & input)
	{
		return Quantity<T>(data / input);
	}
	
	template<typename T>
	Quantity<T> operator*(double const & A, Quantity<T> B)
	{
		return B * A;
	}
	
	template<typename T>
	Quantity<typename unit_5_3::Zip<Dimension<>, T, unit_5_3::Minus>::type> operator/(double const & A, Quantity<T> B)
	{
		double newValue = B.value() / A;
		return Quantity<typename unit_5_3::Zip<Dimension<>, T, unit_5_3::Minus>::type>(newValue);
	}
	
	template<typename T>
	double Quantity<T>::value() const
	{
		return data;
	}

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

		using NumberQ = unit_5_3::Quantity<Dimension<1, 0, -1>>;
		NumberQ Q1{3};
		NumberQ Q2{4};
		NumberQ Q3{2};
		NumberQ Q4{1};
		auto n = (2.0 / Q3) * Q2 / Q1;
		std::cout << n.value() << '\n';
		
		std::string s{"Hello"};
		size_t s_size = unit_5_3::get_size(s);   // 5, вызываетс€ метод size()

		struct Struct 
		{ 
    		size_t size = 10;  
		};

		Struct x;
		size_t x_size = unit_5_3::get_size(x);  // 10, читаетс€ поле size
		std::cout << s_size << " " << x_size << '\n';
	}
}
