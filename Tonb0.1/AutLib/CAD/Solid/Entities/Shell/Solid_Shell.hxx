#pragma once
#ifndef _Solid_Shell_Header
#define _Solid_Shell_Header

#include <Pnt3d.hxx>
#include <Solid_Entity.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Solid_Face;

	template<class T> class Entity_Box;

	typedef Entity_Box<Pnt3d> Entity3d_Box;

	class Solid_Shell
		: public Solid_Entity
		, public std::enable_shared_from_this<Solid_Shell>
	{

		typedef std::shared_ptr<Solid_Face> face_ptr;
		typedef std::vector<face_ptr> faceList;
		typedef std::shared_ptr<faceList> faceList_ptr;
		typedef std::shared_ptr<Solid_Shell> shell_ptr;

		typedef std::shared_ptr<Entity3d_Box> box_ptr;

		/*Private Data*/

		faceList_ptr theFaces_;

		box_ptr theBoundingBox_;

		Standard_Boolean IsClosed_;

		void CloseCondition();

		void CalcBoundingBox();

	public:

		Solid_Shell
		(
			const faceList_ptr& theFaces
		)
			: theFaces_(theFaces)
		{
			CloseCondition();

			CalcBoundingBox();
		}

		Solid_Shell
		(
			const Standard_Integer theIndex,
			const faceList_ptr& theFaces
		)
			: Solid_Entity(theIndex)
			, theFaces_(theFaces)
		{
			CloseCondition();

			CalcBoundingBox();
		}

		Solid_Shell
		(
			const Standard_Integer theIndex,
			const word& theName,
			const faceList_ptr& theFaces
		)
			: Solid_Entity(theIndex, theName)
			, theFaces_(theFaces)
		{
			CloseCondition();

			CalcBoundingBox();
		}

		const faceList_ptr& Faces() const
		{
			return theFaces_;
		}

		const box_ptr& BoundingBox() const
		{
			return theBoundingBox_;
		}

		Standard_Boolean IsClosed() const
		{
			return IsClosed_;
		}

		void ExportToPlt(fstream& File) const;

		static Standard_Boolean IsLess
		(
			const shell_ptr& theSh1,
			const shell_ptr& theSh2
		)
		{
			Debug_Null_Pointer(theSh1);
			Debug_Null_Pointer(theSh2);

			return theSh1->Index() < theSh2->Index();
		}
	};
}

#endif // !_Solid_Shell_Header
