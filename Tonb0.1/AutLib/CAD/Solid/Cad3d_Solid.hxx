#pragma once
#ifndef _Cad3d_Solid_Header
#define _Cad3d_Solid_Header

#include <Global_Named.hxx>
#include <Global_Indexed.hxx>
#include <Pnt3d.hxx>
#include <Solid_EntityManager.hxx>
#include <OFstream.hxx>

#include <memory>
#include <vector>

namespace AutLib
{

	// Forward Declarations
	class Solid_Face;
	class Solid_Shell;
	class Solid_Entity;
	class Solid_Paired;

	template<class T> class Entity_Box;

	typedef Entity_Box<Pnt3d> Entity3d_Box;

	struct Cad3d_SolidInfo
	{
		Standard_Real Tolerance;

		static const Standard_Real DEFAULT_TOLERANCE;

		Cad3d_SolidInfo()
			: Tolerance(DEFAULT_TOLERANCE)
		{}
	};

	class Cad3d_Solid
		: public Global_Indexed
		, public Global_Named
		, public std::enable_shared_from_this<Cad3d_Solid>
		, public Cad3d_SolidInfo
	{

		typedef std::shared_ptr<Solid_EntityManager> entityManager_ptr;
		typedef std::shared_ptr<Solid_Shell> shell_ptr;
		typedef std::vector<shell_ptr> shellList;
		typedef std::shared_ptr<shellList> shellList_ptr;
		typedef std::shared_ptr<Solid_Face> face_ptr;
		typedef std::shared_ptr<Solid_Paired> paired_ptr;
		typedef std::vector<face_ptr> faceList;

		typedef shell_ptr outer;
		typedef shellList_ptr inner;

		typedef std::shared_ptr<Entity3d_Box> box_ptr;
		typedef std::shared_ptr<Solid_Entity> entity_ptr;

		/*Private Data*/

		entityManager_ptr theVertices_;
		entityManager_ptr theEdges_;
		entityManager_ptr theFaces_;

		outer theOutter_;
		inner theInner_;

		box_ptr theBoundingBox_;

		void CalcBoundingBox(const faceList& theFaces);

		Standard_Boolean MakeShells(const faceList& theFaces);

		void SplitByShells();

		void Make(const faceList& theFaces);

	public:

		Cad3d_Solid
		(
			const faceList& theFaces
		)
		{
			Make(theFaces);
		}

		~Cad3d_Solid()
		{}

		const box_ptr& BoundingBox() const
		{
			return theBoundingBox_;
		}

		entityManager_ptr Vertices() const
		{
			return theVertices_;
		}

		entityManager_ptr Edges() const
		{
			return theEdges_;
		}

		entityManager_ptr Faces() const
		{
			return theFaces_;
		}

		Standard_Integer NbVertices() const
		{
			Debug_Null_Pointer(theVertices_);
			return (Standard_Integer)theVertices_->Size();
		}

		Standard_Integer NbEdges() const
		{
			Debug_Null_Pointer(theEdges_);
			return (Standard_Integer)theEdges_->Size();
		}

		Standard_Integer NbFaces() const
		{
			Debug_Null_Pointer(theFaces_);
			return (Standard_Integer)theFaces_->Size();
		}

		Standard_Integer NbHoles() const
		{
			if (NOT theInner_) return 0;
			return (Standard_Integer)theInner_->size();
		}

		Standard_Integer NbFreeEdges() const;

		Standard_Boolean HasFreeEdge() const;

		void RetrieveFreeEdgesTo(std::vector<paired_ptr>& theEdges) const;

		void ExportToPlt(OFstream& File) const;

		void ExportVerticesToPlt(OFstream& File) const;

		void ExportEdgesToPlt(OFstream& File) const;

		void ExportFacesToPlt(OFstream& File) const;

		void ExportFreeEdgesToPlt(OFstream& File) const;

		void ExportNormalsToPlt(OFstream& File, const Standard_Real theCoeff = 0.01) const;

		void ExportShellsToPlt(OFstream& File) const;

		void Report(Standard_OStream& Ostream = cout) const;
		
	};
}

#endif // !_Cad3d_Solid_Header
