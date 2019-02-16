#pragma once
#ifndef _Model_Entity_Header
#define _Model_Entity_Header

#include <word.hxx>
#include <Entity3d_Box.hxx>

#include <gp_Ax2.hxx>
#include <TopoDS_Shape.hxx>

#include <memory>

namespace AutLib
{

	// Forward Declarations
	class dictionary;

	namespace Io
	{
		enum EntityIO_Format
		{
			EntityIO_Format_IGES,
			EntityIO_Format_STEP,
			EntityIO_Format_TecPlot
		};
	}

	class Model_EntityIO
	{

		/*Private Data*/

		word theFileName_;

		Io::EntityIO_Format theFormat_;

		//- Control data dictionary
		const dictionary& theDict_;

	public:

		Model_EntityIO();

		Model_EntityIO(const dictionary& theDict)
			: theDict_(theDict)
		{}

		const word&  FileName() const
		{
			return theFileName_;
		}

		word& FileName()
		{
			return theFileName_;
		}

		const Io::EntityIO_Format FileFromat() const
		{
			return theFormat_;
		}

		Io::EntityIO_Format& FileFromat()
		{
			return theFormat_;
		}

		const dictionary& Dictionary() const
		{
			return theDict_;
		}

		void SetFileName(const word& theName)
		{
			theFileName_ = theName;
		}

		void SetFileFromat(const Io::EntityIO_Format format)
		{
			theFormat_ = format;
		}
	};

	class Model_EntitySystem
	{

		/*Private Data*/

		gp_Ax2 theSystem_;

	protected:

		gp_Ax2& System()
		{
			return theSystem_;
		}

		void SetSystem(const gp_Ax2& theSys)
		{
			theSystem_ = theSys;
		}

	public:

		Model_EntitySystem()
		{}

		Model_EntitySystem(const gp_Ax2& theSystem)
			: theSystem_(theSystem)
		{}

		const gp_Ax2& System() const
		{
			return theSystem_;
		}

	};

	class Model_EntityID
	{

		/*Private Data*/

		Standard_Integer theIndex_;

		word theName_;

	public:

		Model_EntityID()
			: theIndex_(0)
			, theName_("Unknown")
		{}

		Model_EntityID(const Standard_Integer theIndex)
			: theIndex_(theIndex)
			, theName_("Unknown")
		{}

		Model_EntityID
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: theIndex_(theIndex)
			, theName_(theName)
		{}

		Standard_Integer Index() const
		{
			return theIndex_;
		}

		Standard_Integer& Index()
		{
			return theIndex_;
		}

		const word& Name() const
		{
			return theName_;
		}

		word& Name()
		{
			return theName_;
		}

		void SetName(const word& theName)
		{
			theName_ = theName;
		}

		void SetIndex(const Standard_Integer theIndex)
		{
			theIndex_ = theIndex;
		}
	};

	class Model_EntityDiscrete
	{

		/*Private Data*/

		Standard_Real theDeflection_;
		Standard_Real theAngle_;

	public:

		static const Standard_Real DEFAULT_DEFLECTION;
		static const Standard_Real DEFAULT_ANGLE;

		Model_EntityDiscrete()
			: theDeflection_(DEFAULT_DEFLECTION)
			, theAngle_(DEFAULT_ANGLE)
		{}

		Standard_Real Deflection() const
		{
			return theDeflection_;
		}

		Standard_Real& Deflection()
		{
			return theDeflection_;
		}

		Standard_Real Angle() const
		{
			return theAngle_;
		}

		Standard_Real& Angle()
		{
			return theAngle_;
		}
	};

	class Model_EntityBase
	{

		/*Private Data*/

		Standard_Boolean toDiscrete_;
		Standard_Boolean toSolid_;

		std::shared_ptr<Entity3d_Box> theBox_;

	protected:

		mutable Standard_Boolean IsDone_;

		Standard_Boolean& toDiscrete()
		{
			return toDiscrete_;
		}

		Standard_Boolean& toSolid()
		{
			return toSolid_;
		}

		Standard_Boolean& IsDone()
		{
			return IsDone_;
		}

		std::shared_ptr<Entity3d_Box>& Box()
		{
			return theBox_;
		}

	public:

		Model_EntityBase()
			: toDiscrete_(Standard_False)
			, toSolid_(Standard_False)
			, IsDone_(Standard_False)
		{}

		Standard_Boolean toDiscrete() const
		{
			return toDiscrete_;
		}

		Standard_Boolean toSolid() const
		{
			return toSolid_;
		}

		virtual Standard_Boolean IsDone() const
		{
			return IsDone_;
		}

		const std::shared_ptr<Entity3d_Box>& Box() const
		{
			return theBox_;
		}
	};

	class Model_Entity
		: public Model_EntityBase
		, public Model_EntityIO
		, public Model_EntitySystem
		, public Model_EntityID
		, public Model_EntityDiscrete
	{

		/*Private Data*/

		TopoDS_Shape theEntity_;

		// Private functions and operators

	protected:

		TopoDS_Shape& Entity()
		{
			return theEntity_;
		}

	public:

		Model_Entity()
		{}

		Model_Entity(const dictionary& theDict)
			: Model_EntityIO(theDict)
		{}

		Model_Entity(const Standard_Integer theIndex)
			: Model_EntityID(theIndex)
		{}

		Model_Entity
		(
			const Standard_Integer theIndex,
			const word& theName
		)
			: Model_EntityID(theIndex, theName)
		{}

		Model_Entity
		(
			const dictionary& theDict,
			const Standard_Integer theIndex
		)
			: Model_EntityIO(theDict)
			, Model_EntityID(theIndex)
		{}

		Model_Entity
		(
			const dictionary& theDict,
			const Standard_Integer theIndex,
			const word& theName
		)
			: Model_EntityIO(theDict)
			, Model_EntityID(theIndex, theName)
		{}

		const Model_EntityIO& IO() const
		{
			return *this;
		}

		Model_EntityIO& IO()
		{
			return *this;
		}

		const TopoDS_Shape& Entity() const
		{
			return theEntity_;
		}

		TopoDS_Shape Section(const gp_Pln& thePlane) const;

		void Discrete();

		void MakeSolid();

		void TransformTo
		(
			const gp_Ax2& theSystem
		);

		void Scale
		(
			const Standard_Real theScale
		);

		void ExportToFile() const;

		void CalcBoundingBox();

		static Entity3d_Box BoundingBox(const TopoDS_Shape& theShape);

	};
}

#endif // !_Model_Entity_Header
