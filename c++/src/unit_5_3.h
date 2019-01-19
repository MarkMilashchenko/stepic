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
	
	template<int a, int b>
	struct Minus
	{
    	static int const value = a - b;    
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
	
	
	template<int m = 0, int kg = 0, int s = 0, int A = 0, int K = 0, int mol = 0, int cd = 0>
	using Dimension = IntList<m, kg, s, A, K, mol, cd>;
	
	template<typename T>
	struct Quantity
	{
		Quantity();
		explicit Quantity(double const & input);
		Quantity(Quantity<T> const & input);

		Quantity<T> operator+(Quantity<T> const & input);
		Quantity<T> operator-(Quantity<T> const & input);
		
		template<typename T2>
		Quantity<typename Zip<T, T2, Plus>::type> operator*(Quantity<T2> const & input);
		template<typename T2>
		Quantity<typename Zip<T, T2, Minus>::type> operator/(Quantity<T2> const & input);
		
		Quantity<T> operator*(double const & input);
		Quantity<T> operator/(double const & input);

		double value() const;
				
		double data;
		T dimension;
	};
	
	typedef char METHOD;
	struct VALUE {METHOD m[2];};
	
	template<bool b>
	struct Bool2type { using type = METHOD; };
	
	template<>
	struct Bool2type<false> { using type = VALUE; };
	
	template<typename T>
	size_t call_size(T& a, METHOD) { return a.size(); };
	
	template<typename T>
	size_t call_size(T& a, VALUE) { return a.size; };
		
	template<typename T>
	struct is_size_defined
	{
		template<typename Z, size_t (Z::*)() const = &Z::size>
		struct wrapper_method {};
		
		template<typename C>
		static METHOD check(wrapper_method<C>* p) { return METHOD();};
		
		template<typename C>
		static VALUE check(...) { return VALUE(); };
		
		static bool const value = sizeof(METHOD) == sizeof(check<T>(0));
	};
	
	template<typename T>
	size_t get_size(T& input)
	{
		constexpr bool value = is_size_defined<T>::value;
		using CALL = typename Bool2type<value>::type;
		return call_size(input, CALL());
	};

//	более крутое решение
//	template<class T, size_t (T::*)() const = &T::size>
//	size_t get_size(T const& t)
//	{
//    	return t.size();
//	};
//
//	template<class T, size_t (T::*) = &T::size>
//	size_t get_size(T const& t)
//	{
//    	return t.size;
//	};
	
	void test();
}

