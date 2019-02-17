#pragma once
#ifndef _LocalFrontIdentifiers_FrontEntity_Header
#define _LocalFrontIdentifiers_FrontEntity_Header

#include <Standard_TypeDef.hxx>
#include <error.hxx>

namespace AutLib
{

	template<class Point>
	class LocalFrontIdentifiers_FrontEntity
	{

		/*Private Data*/

		//- Centre of entity
		Point theCentre_;

		Standard_Real theCharLength_;

		Standard_Boolean IsOnCavity_;

	public:

		LocalFrontIdentifiers_FrontEntity()
			: theCharLength_(0)
		{}

		const Point& Centre() const
		{
			return theCentre_;
		}

		Point& Centre()
		{
			return theCentre_;
		}

		Standard_Real CharLength() const
		{
			return theCharLength_;
		}

		Standard_Real& CharLength()
		{
			return theCharLength_;
		}

		Standard_Boolean IsOnCavity() const
		{
			return IsOnCavity_;
		}

		Standard_Boolean& IsOnCavity()
		{
			return IsOnCavity_;
		}

		void SetCentre(const Point& theCoord)
		{
			theCentre_ = theCoord;
		}

		void SetCharLength(const Standard_Real theLength)
		{
			Debug_If_Condition(theLength <= 0);
			theCharLength_ = theLength;
		}

		void MarkEntityAsCavity()
		{
			IsOnCavity_ = Standard_True;
		}

		void RemoveEntityAsCavity()
		{
			IsOnCavity_ = Standard_False;
		}
	};
}

#endif // !_LocalFrontIdentifiers_FrontEntity_Header
