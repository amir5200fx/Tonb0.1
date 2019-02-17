#pragma once
#ifndef _LocalFrontIdentifiers_Node_Header
#define _LocalFrontIdentifiers_Node_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{

	class LocalFrontIdentifiers_Node
	{

		/*Private Data*/

		//- Searching radius
		Standard_Real theRadius_;

		//- maximum length adjasted to the node
		Standard_Real theMaxL_;

	public:

		LocalFrontIdentifiers_Node()
			: theRadius_(0)
			, theMaxL_(0)
		{}

		Standard_Real Radius() const
		{
			return theRadius_;
		}

		Standard_Real MaxAdjLength() const
		{
			return theMaxL_;
		}

		Standard_Real& Radius()
		{
			return theRadius_;
		}

		Standard_Real& MaxAdjLength()
		{
			return theMaxL_;
		}

		void SetRadius(const Standard_Real theRadius)
		{
			theRadius_ = theRadius;
		}

		void SetMaxAdjLength(const Standard_Real theMaxL)
		{
			theMaxL_ = theMaxL;
		}
	};
}

#endif // !_LocalFrontIdentifiers_Node_Header
