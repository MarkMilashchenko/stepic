#include <utility> // std::declval

namespace unit_4_3 
{
	// without move semantics
	template<class T>
	void do_math() noexcept(
                	noexcept(std::declval<T>() + std::declval<T>()) && \
                   	noexcept(std::declval<T&>() = std::declval<T>()) && \
                   	std::is_nothrow_constructible<T, const T&>::value )
	{}

	// with move semantics
	template<class T>
	void do_math_move_semantics() noexcept(
                   noexcept(std::declval<T>() + std::declval<T>()) && \
                   noexcept(std::declval<T&>() = std::declval<T>()) && \
                   std::is_nothrow_constructible<T, const T&>::value && \
                   std::is_nothrow_move_constructible<T>::value && \
                   std::is_nothrow_copy_assignable<T>::value)
    {}
}
