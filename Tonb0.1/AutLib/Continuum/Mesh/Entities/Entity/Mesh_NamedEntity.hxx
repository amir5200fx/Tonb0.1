#pragma once
#ifndef _Mesh_NamedEntity_Header
#define _Mesh_NamedEntity_Header

#include <Mesh_Entity.hxx>
#include <word.hxx>

namespace AutLib
{

	class Mesh_NamedEntity
		: public Mesh_Entity
	{

		/*Private Data*/

		word theName_;

	public:

		Mesh_NamedEntity()
			: theName_("Unknown")
		{}

		Mesh_NamedEntity
		(
			const Standard_Integer theIndex
		)
			: Mesh_Entity(theIndex)
			, theName_("Unknown")
		{}

		Mesh_NamedEntity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Mesh_Entity(theIndex)
			, theName_(theName)
		{}

		const word& Name() const
		{
			return theName_;
		}

		void SetName(const word& theName)
		{
			theName_ = theName;
		}
	};
}

#endif // !_Mesh_NamedEntity_Header