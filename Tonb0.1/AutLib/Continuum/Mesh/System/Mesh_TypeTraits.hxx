#pragma once
#ifndef _Mesh_TypeTraits_Header
#define _Mesh_TypeTraits_Header

#include <iostream>

namespace AutLib
{
	class Aft2d_Node;
	class Aft2d_Edge;
	class Aft2d_TriElement;

	template<class T, int Rank, int Dim> struct is_validType : std::false_type {};


	template<> struct is_validType<Aft2d_Node, 0, 2> : std::true_type {};
	template<> struct is_validType<Aft2d_Edge, 1, 2> : std::true_type {};
	template<> struct is_validType<Aft2d_TriElement, 2, 2> : std::true_type {};

	template<class T, int Rank> struct sub_Type {};
	template<> struct sub_Type<Aft2d_Node, 0> { typedef Aft2d_Node type; };
	template<> struct sub_Type<Aft2d_Edge, 0> { typedef Aft2d_Node type; };
	template<> struct sub_Type<Aft2d_Edge, 1> { typedef Aft2d_Edge type; };
	template<> struct sub_Type<Aft2d_TriElement, 0> { typedef Aft2d_Node type; };
	template<> struct sub_Type<Aft2d_TriElement, 1> { typedef Aft2d_Edge type; };
	template<> struct sub_Type<Aft2d_TriElement, 2> { typedef Aft2d_TriElement type; };

	template<class T, int Rank> struct has_subType : std::false_type {};

	template<> struct has_subType<Aft2d_Node, 0> : std::true_type {};
	template<> struct has_subType<Aft2d_Edge, 0> : std::true_type {};
	template<> struct has_subType<Aft2d_Edge, 1> : std::true_type {};
	template<> struct has_subType<Aft2d_TriElement, 0> : std::true_type {};
	template<> struct has_subType<Aft2d_TriElement, 1> : std::true_type {};
	template<> struct has_subType<Aft2d_TriElement, 2> : std::true_type {};

	/*template <bool Condition, typename TrueStatement, typename FalseStatement> struct if_;
	template <class TrueStatement, class FalseStatement> struct if_<true, TrueStatement, FalseStatement> {typedef TrueStatement value;};
	template <class TrueStatement, class FalseStatement> struct if_<false, TrueStatement, FalseStatement> { typedef FalseStatement value; };*/

	template<int Dim> struct is_two_dimension : std::false_type {};
	template<> struct is_two_dimension<2> : std::true_type {};

	template<int Dim> struct is_three_dimension : std::false_type {};
	template<> struct is_two_dimension<3> : std::true_type {};

	template<bool Cond> struct if_true : std::false_type {};
	template<> struct if_true<true> : std::true_type {};

	template<bool Cond> struct if_false : std::false_type {};
	template<> struct if_false<false> : std::true_type {};
}

#endif // !_Mesh_TypeTraits_Header
