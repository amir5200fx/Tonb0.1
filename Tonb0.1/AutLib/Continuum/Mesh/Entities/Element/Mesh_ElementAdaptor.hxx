#pragma once
#ifndef _Mesh_ElementAdaptor_Header
#define _Mesh_ElementAdaptor_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{

	template<class ElementType, int NbCmpts>
	class Mesh_ElementAdaptor{};

	template<class ElementType>
	class Mesh_ElementAdaptor<ElementType, 3>
	{

		/*Private Data*/

		const ElementType* theElements_[3];

	public:

		const int nbCmpts = 3;

		Mesh_ElementAdaptor()
		{
			for (int i = 0; i < nbCmpts; i++) theElements_[i] = 0;
		}

		const ElementType* Element(const Standard_Integer theIndex) const
		{
			return theElements_[theIndex];
		}

		const ElementType*& Element(const Standard_Integer theIndex)
		{
			return theElements_[theIndex];
		}

		void SetElement
		(
			const Standard_Integer theIndex,
			const ElementType* theElement
		)
		{
			theElements_[theIndex] = theElement;
		}
	};
}

#endif // !_Mesh_ElementAdaptor_Header
