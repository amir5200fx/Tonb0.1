#pragma once
#ifndef _TypeTraits_Header
#define _TypeTraits_Header

#include <handle.hxx>

namespace AutLib
{
	template<class T> struct remove_pointer { typedef T type; };
	template<class T> struct remove_pointer<T*> { typedef T type; };
	template<class T> struct remove_pointer<T* const> { typedef T type; };
	template<class T> struct remove_pointer<T* volatile> { typedef T type; };
	template<class T> struct remove_pointer<T* const volatile> { typedef T type; };

	template<class T> struct remove_pointer<pHandle(T)> { typedef T type; };
}

#endif // !_TypeTraits_Header
