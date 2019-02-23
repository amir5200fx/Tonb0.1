#pragma once
#ifndef _TypeTraits_Header
#define _TypeTraits_Header

#include <handle.hxx>
#include <iostream>

namespace AutLib
{
	template<int Dim> struct is_two_dimension : std::false_type {};
	template<> struct is_two_dimension<2> : std::true_type {};

	template<int Dim> struct is_three_dimension : std::false_type {};
	template<> struct is_two_dimension<3> : std::true_type {};

	template<bool Cond> struct if_true : std::false_type {};
	template<> struct if_true<true> : std::true_type {};

	template<bool Cond> struct if_false : std::false_type {};
	template<> struct if_false<false> : std::true_type {};

	template<class T> struct remove_pointer { typedef T type; };
	template<class T> struct remove_pointer<T*> { typedef T type; };
	template<class T> struct remove_pointer<T* const> { typedef T type; };
	template<class T> struct remove_pointer<T* volatile> { typedef T type; };
	template<class T> struct remove_pointer<T* const volatile> { typedef T type; };

	template<class T> struct remove_pointer<pHandle(T)> { typedef T type; };
}

#endif // !_TypeTraits_Header
