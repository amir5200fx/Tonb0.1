#pragma once
#ifndef _Mesh_EdgeAdaptor_Header
#define _Mesh_EdgeAdaptor_Header

#include <Adt_AvlTree.hxx>
#include <Mesh_EntityAdaptorM.hxx>

namespace AutLib
{

	Mesh_EntityToEntityAdaptor(Edge, Facet, FacetType);
	Mesh_EntityToEntityAdaptor(Edge, Element, ElementType);

	template<class ElementType, class FacetType = void>
	class Mesh_EdgeAdaptor
		: public Mesh_EdgeToFacetAdaptor<FacetType>
		, public Mesh_EdgeToElementAdaptor<ElementType>
	{

		/*Private Data*/

	public:

		Mesh_EdgeAdaptor()
		{}
	};


	template<class ElementType>
	class Mesh_EdgeAdaptor<ElementType, void>
	{

		/*Private Data*/

		const ElementType* theRight_;
		const ElementType* theLeft_;

	public:

		Mesh_EdgeAdaptor()
		{}

		const ElementType* RightElement() const
		{
			return theRight_;
		}

		const ElementType*& RightElement()
		{
			return theRight_;
		}

		const ElementType* LeftElement() const
		{
			return theLeft_;
		}

		const ElementType*& LeftElement()
		{
			return theLeft_;
		}

		Standard_Boolean IsOrphan() const
		{
			return IsNULL(RightElement()) AND IsNULL(LeftElement());
		}

		void SetRightElement(const ElementType* theElement)
		{
			theRight_ = theElement;
		}

		void SetLeftElement(const ElementType* theElement)
		{
			theLeft_ = theElement;
		}
	};
}

#endif // !_Mesh_EdgeAdaptor_Header
