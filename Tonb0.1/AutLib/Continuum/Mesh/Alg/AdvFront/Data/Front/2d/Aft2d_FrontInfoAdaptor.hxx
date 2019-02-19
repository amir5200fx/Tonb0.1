#pragma once
#ifndef _Aft2d_FrontInfoAdaptor_Header
#define _Aft2d_FrontInfoAdaptor_Header

#include <handle.hxx>

namespace AutLib
{

	class Aft2d_Node;
	class Aft2d_Edge;
	class Aft2d_TriElement;

	class Aft2d_FrontInfoAdaptor
	{

		/*Private Data*/

		pHandle(Aft2d_Edge) thePaired0_;
		pHandle(Aft2d_Edge) thePaired1_;

		pHandle(Aft2d_Edge) theCreated0_;
		pHandle(Aft2d_Edge) theCreated1_;

	public:

		typedef Aft2d_Node nodeType;
		typedef Aft2d_Edge frontType;
		typedef Aft2d_TriElement elementType;

		Aft2d_FrontInfoAdaptor()
		{}

		const pHandle(Aft2d_Edge)& PairedEdge0() const
		{
			return thePaired0_;
		}

		pHandle(Aft2d_Edge)& PairedEdge0()
		{
			return thePaired0_;
		}

		const pHandle(Aft2d_Edge)& PairedEdge1() const
		{
			return thePaired1_;
		}

		pHandle(Aft2d_Edge)& PairedEdge1()
		{
			return thePaired1_;
		}

		const pHandle(Aft2d_Edge)& CreatedEdge0() const
		{
			return theCreated0_;
		}

		pHandle(Aft2d_Edge)& CreatedEdge0()
		{
			return theCreated0_;
		}

		const pHandle(Aft2d_Edge)& CreatedEdge1() const
		{
			return theCreated1_;
		}

		pHandle(Aft2d_Edge)& CreatedEdge1()
		{
			return theCreated1_;
		}

		Standard_Boolean IsPairedEdge0() const
		{
			return (Standard_Boolean)thePaired0_;
		}

		Standard_Boolean IsPairedEdge1() const
		{
			return (Standard_Boolean)thePaired1_;
		}

		Standard_Boolean IsCreatedEdge0() const
		{
			return (Standard_Boolean)theCreated0_;
		}

		Standard_Boolean IsCreatedEdge1() const
		{
			return (Standard_Boolean)theCreated1_;
		}

		void SetPairedEdge0(const pHandle(Aft2d_Edge)& theEdge)
		{
			thePaired0_ = theEdge;
		}

		void SetPairedEdge1(const pHandle(Aft2d_Edge)& theEdge)
		{
			thePaired1_ = theEdge;
		}

		void SetCreatedEdge0(const pHandle(Aft2d_Edge)& theEdge)
		{
			theCreated0_ = theEdge;
		}

		void SetCreatedEdge1(const pHandle(Aft2d_Edge)& theEdge)
		{
			theCreated1_ = theEdge;
		}

#ifdef RESET_FRONT_INFO
		void Reset()
		{
			PairedEdge0() = 0;
			PairedEdge1() = 0;

			CreatedEdge0() = 0;
			CreatedEdge1() = 0;
		}
#endif
	};
}

#endif // !_Aft2d_FrontInfoAdaptor_Header
