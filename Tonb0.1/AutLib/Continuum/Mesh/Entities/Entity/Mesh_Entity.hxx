#pragma once
#ifndef _Mesh_Entity_Header
#define _Mesh_Entity_Header

#include <Transient.hxx>

namespace AutLib
{

	class Mesh_Entity
		: public Transient
	{

		/*Private Data*/

		Standard_Integer theIndex_;

	protected:

		Mesh_Entity()
			: theIndex_(0)
		{}

		Mesh_Entity(const Standard_Integer theIndex)
			: theIndex_(theIndex)
		{}

	public:

		/*virtual ~Mesh_Entity()
		{}*/

		Standard_Integer Index() const
		{
			return theIndex_;
		}

		Standard_Integer& Index()
		{
			return theIndex_;
		}

		void SetIndex(const Standard_Integer theIndex)
		{
			theIndex_ = theIndex;
		}
	};
}

#endif // !_Mesh_Entity_Header
