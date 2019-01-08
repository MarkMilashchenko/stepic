//https://stepik.org/lesson/58812/step/5?unit=36393
#pragma once
#include <tuple>


namespace unit_5_3 {
	template<int N>
	struct Fib
	{ 
		static int const value = Fib<N - 1>::value + Fib<N - 2>::value; 
	};
	
	template<>
	struct Fib<1>
	{ 
		static int const value = 1; 
	};
	
	template<>
	struct Fib<0>
	{ 
		static int const value = 0; 
	};
	
	template<int ... input>
	struct IntList;
	
	template<int H, int ... T>
	struct IntList<H, T...>
	{
		static int const Head = H;
		using Tail = IntList<T...>;
	};
	
	template<>
	struct IntList<> 
	{};
	
	template<class IntList>
	struct Length
	{ 
		int static const value = 1 + Length<class IntList::Tail>::value; 
	};
	
	template<>
	struct Length<IntList<>>
	{ 
		int static const value = 0; 
	};
	
	template<int H, class TL>
	struct IntCons;
	
	template<int H, int ...L>
	struct IntCons<H, IntList<L...>>
	{
		using type = IntList<H, L...>;
	};
	
	template<int H, int B = 0>
	struct Generate
	{
		using type = typename IntCons<B, typename Generate<H - 1, B + 1>::type>::type;
	};
	
	template<int B>
	struct Generate<0, B>
	{
		using type = IntList<>;
	};
	
	template<typename T, typename... Args, int... val>
	auto calc_fcn(T fcn, std::tuple<Args...> tuple, IntList<val...> list) -> decltype(fcn(std::forward<Args>(std::get<val>(tuple))...))
	{
		return fcn(std::forward<Args>(std::get<val>(tuple))...);
	};

	template<typename T, typename... Args>
	auto apply(T fcn, std::tuple<Args...> tuple) -> decltype(calc_fcn(fcn, tuple, typename Generate<sizeof... (Args)>::type()))
	{
		return calc_fcn(fcn, tuple, typename Generate<sizeof...(Args)>::type());
	};
	
	template<int a, int b>
	struct Plus
	{
    	static int const value = a + b;    
	};
	
	template<typename T1, typename T2, template<int, int> class F>
	struct Zip;

	template<int... L1, int... L2, template<int, int> class F>
	struct Zip<IntList<L1...>, IntList<L2...>, F>
	{
		static int const value = F<IntList<L1...>::Head, IntList<L2...>::Head>::value;
        using recursiveTail = typename Zip<typename IntList<L1...>::Tail, typename IntList<L2...>::Tail, F>::type;
		using type = typename IntCons<value, recursiveTail>::type;
	};
	
	template<template<int, int> class F>
	struct Zip<IntList<>, IntList<>, F>
	{
		using type = IntList<>;
	};
	
	
//	template<int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0, int cd = 0>
//	using Dimension = IntList<m, kg, s, A, K, mol, cd>;
//	
//	template<IntList<int... Args> list>
//	struct Quantity
//	{
//		Quantity();
//		explicit Quantity(double input);
//		
//		void operator+();
//		
//		double value;
//	};
	
	void test();
}

