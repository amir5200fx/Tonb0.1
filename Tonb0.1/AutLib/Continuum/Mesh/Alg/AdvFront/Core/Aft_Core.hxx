#pragma once
#ifndef _Aft_Core_Header
#define _Aft_Core_Header

#include <Standard_Real.hxx>
#include <Geom_Sort.hxx>
#include <Mesh_GlobalData.hxx>
#include <Aft_FrontGlobalData.hxx>
#include <Aft_FrontInfo.hxx>
#include <Mesh_TypeTraits.hxx>

#include <memory>

namespace AutLib
{

	template
		<
		class FrontInfo,
		template<class> class GeomSearch,
		template<class> class PriorityList,
		template<class> class SizeMap
		>
	class Aft_Core
		: public FrontInfo
		, public Mesh_GlobalData<typename FrontInfo::elementType>
		, public Aft_FrontGlobalData<typename FrontInfo::frontType, GeomSearch, PriorityList>
	{

	protected:

		typedef Mesh_GlobalData<typename FrontInfo::elementType>
			globalData;
		typedef FrontInfo frontInfo;
		typedef Aft_FrontGlobalData<typename FrontInfo::frontType, GeomSearch, PriorityList>
			frontData;
		typedef typename FrontInfo::frontType frontType;
		typedef typename FrontInfo::nodeType nodeType;
		typedef typename nodeType::ptType Point;
		typedef SizeMap<typename FrontInfo::frontType>
			sizeMap;

		typedef Aft_Core
			<
			FrontInfo,
			GeomSearch,
			PriorityList,
			SizeMap
			> core;

		typedef pHandle(frontType) front_Ptr;
		typedef pHandle(nodeType) node_Ptr;
		typedef std::shared_ptr<SizeMap<typename FrontInfo::frontType>> sizeMap_ptr;

		typedef typename sub_Type<frontType, (int)frontType::rank - 1>::type subType;
		typedef pHandle(subType) subType_Ptr;

		template< bool cond, typename U >
		using resolvedType = typename std::enable_if< cond, U >::type;

	private:


		/*Private Data*/

		static const Standard_Real SIZE_TO_HIGHT_ELEMENT_COEFF;

		sizeMap_ptr theSizeMap_;


		struct mySort
		{

			static const Standard_Integer RESERVED_SORT_SIZE;
			static Stl_Vector<Standard_Real> Quality_;
			static Stl_Vector<Standard_Integer> Indices_;

			static Standard_Integer Size_;

			void Import
			(
				const Stl_Vector<node_Ptr>& theNodes,
				const Point& theCentre,
				const sizeMap& SizeMap
			)
			{
#if MESH_DEBUG
				if (theNodes.Size() > mySort::RESERVED_SORT_SIZE)
				{
					FatalErrorIn(FunctionSIG)
						<< "Too large front size to sorting"
						<< abort(FatalError);
				}
#endif

				if (theNodes.size() > mySort::Quality_.size())
				{
					mySort::Quality_.reserve(theNodes.size() * 2);
					mySort::Indices_.reserve(theNodes.size() * 2);
				}

				Standard_Integer k = 0;
				for (const auto& node : theNodes)
				{
					Debug_Null_Pointer(node);
					mySort::Quality_[k] =
						SizeMap.CalcSquareDistance(theCentre, node->Coord());
					mySort::Indices_[k] =
						k;
					++k;
				}

				Size_ = theNodes.size();
			}

			void Perform
			(
				const Standard_Integer theSize
			)
			{
				Geom_Sort::Sort
					<
					Standard_Real,
					Stl_Vector
					>
					(Quality_, Indices_, theSize);
			}
		};

		static mySort Sort;

		template<class U = void>
		resolvedType
			<
			is_validType<frontType, (int)frontType::rank, 2>::value, U
			>
			RetrieveFronts
			(
				const nodeType& theNode,
				Stl_Vector<const frontType*>& theEntities
			) const
		{
			theNode.RetrieveFrontEdgesTo(theEntities);
		}

		template<class U = void>
		resolvedType
			<
			is_validType<frontType, (int)frontType::rank, 3>::value, U
			>
			RetrieveFronts
			(
				const nodeType& theNode,
				Stl_Vector<const frontType*>& theEntities
			) const
		{
			theNode.RetrieveFrontFacetsTo(theEntities);
		}

		template<class U = void>
		resolvedType
			<
			is_two_dimension<(int)frontType::dim>::value, U
			>
			Update_Pmin_Pmax
			(
				const Point& P,
				Point& Pmin,
				Point& Pmax
			) const
		{
			if (P.X() > Pmax.X()) Pmax.X() = P.X();
			if (P.X() < Pmin.X()) Pmin.X() = P.X();

			if (P.Y() > Pmax.Y()) Pmax.Y() = P.Y();
			if (P.Y() < Pmin.Y()) Pmin.Y() = P.Y();
		}

		template<class U = void>
		resolvedType
			<
			is_three_dimension<(int)frontType::dim>::value, U
			>
			Update_Pmin_Pmax
			(
				const Point& P,
				Point& Pmin,
				Point& Pmax
			) const
		{
			if (P.X() > Pmax.X()) Pmax.X() = P.X();
			if (P.X() < Pmin.X()) Pmin.X() = P.X();

			if (P.Y() > Pmax.Y()) Pmax.Y() = P.Y();
			if (P.Y() < Pmin.Y()) Pmin.Y() = P.Y();

			if (P.Z() > Pmax.Z()) Pmax.Z() = P.Z();
			if (P.Z() < Pmin.Z()) Pmin.Z() = P.Z();
		}

		Standard_Boolean IsIntersect
		(
			const Point& P,
			const Point& Pmin,
			const Point& Pmax
		) const
		{
			forThose(coord, 0, Point::nbCmpts - 1)
			{
				Standard_Real x = P.Coord(coord);
				if (x > Pmax.Coord(coord) && x < Pmin.Coord(coord))
				{
					return Standard_False;
				}
			}
			return Standard_True;
		}

	protected:

		template<class U = void>
		resolvedType
			<
			is_validType<frontType, (int)frontType::rank, 2>::value, U
			>
			RemoveEntitiesFromGeometry()
		{
			Debug_Null_Pointer(frontInfo::Element());
			auto& element = *frontInfo::Element();

			forThose(Iter, 0, element.nbNodes - 1)
			{
				Debug_Null_Pointer(element.Node(Iter));

				if (!element.Node(Iter)->NbFrontEdges())
				{
					frontData::RemoveFromGeometry
					(
						element.Node(Iter)
					);
				}
			}
		}

		template<class U = void>
		resolvedType
			<
			is_validType<frontType, (int)frontType::rank, 3>::value, U
			>
			RemoveEntitiesFromGeometry()
		{
			Debug_Null_Pointer(frontData::Element());
			auto& element = *frontData::Element();

			forThose(Iter, 0, element.nbEdges - 1)
			{
				Debug_Null_Pointer(element.Edge(Iter));

				if (!element.Edge(Iter)->NbFrontFacets())
				{
					auto& edge = *element.Edge
					(
						Iter
					);

					edge.Node0()->RemoveFromFrontEdges
					(
						&edge
					);
					edge.Node1()->RemoveFromFrontEdges
					(
						&edge
					);
				}
			}

			forThose(Iter, 0, element.nbNodes - 1)
			{
				Debug_Null_Pointer(element.Node(Iter));

				if (!element.Node(Iter)->NbFrontEdges())
				{
					Debug_If_Condition_Message(element.Node(Iter)->NbFrontFacets(), "Contradictory Data");
					geomData::RemoveFromGeometry
					(
						element.Node(Iter)
					);
				}
			}
		}

		Standard_Boolean GetFrontEntity()
		{
			front_Ptr entity;
			Standard_Boolean Token = frontData::RetrieveFromPriority(entity);

#ifdef RESET_FRONT_INFO
			frontInfo::Reset();
#endif // RESET_FRONT_INFO

			if (NOT Token) return Standard_False;
			frontInfo::SetCurrentFront(entity);
			return Standard_True;
		}

		Standard_Boolean IsBelongToFront() const
		{
			Debug_Null_Pointer(frontInfo::CurrentFront());
			return frontInfo::CurrentFront()->IsOnFront();
		}

		Standard_Boolean ChackDistCriteria(const Stl_Vector<const frontType*>& theFronts) const
		{
			Standard_Real factor = frontInfo::MinDistFactor();
			Debug_If_Condition
			(
				factor <= RealSmall()
			);

			Debug_Null_Pointer(theSizeMap_);
			const auto& sizeMap = *theSizeMap_;

			const auto& Pt = frontInfo::Coord();
			for (const auto& front : theFronts)
			{
				Debug_Null_Pointer(front);
				const auto& entity = *front;

				Standard_Real charLength = factor * entity.CharLength();
				if (sizeMap.CalcSquareDistance(Pt, entity) <= charLength * charLength)
				{
					return Standard_True;
				}
			}
			return Standard_False;
		}

		template<class U = Standard_Boolean>
		resolvedType
			<
			is_validType<frontType, (int)frontType::rank, 3>::value, U
			>
			ChackDistCriteria
			(
				const Point& theP0,
				const Point& theP1,
				const Stl_Vector<pHandle(subType)>& theFronts
			) const
		{
			Standard_Real factor = frontInfo::MinDistFactor();
			Debug_If_Condition
			(
				factor <= RealSmall()
			);

			for (const auto& front : theFronts)
			{
				Debug_Null_Pointer(front);
				const auto& entity = *front;

				Standard_Real charLength = factor * entity.CharLength();
				if (
					sizeMap::CalcSquareDistance
					(
						theP0,
						theP1,
						entity.Node0()->Coord(),
						entity.Node1()->Coord()
					) <= charLength * charLength
					)
				{
					return Standard_True;
				}
			}
			return Standard_False;
		}

		Standard_Boolean IsSameLevelFueled()
		{
			if (frontData::IsCurrentLevelEmpty())
			{
				return Standard_False;
			}

			Stl_Vector<front_Ptr> entities;
			frontData::RetrieveCurrentFrontsTo(entities);

			frontData::InsertToPriority
			(
				entities
			);
			return Standard_True;
		}

		Standard_Boolean IsNextLevelFueled()
		{
			if (frontData::IsNextLevelEmpty())
			{
				return Standard_False;
			}

			Stl_Vector<front_Ptr> entities;
			frontData::RetrieveNextFrontsTo(entities);
			for (auto& entity : entities)
			{
				Debug_Null_Pointer(entity);
				if (entity->IsOnCavity())
					entity->RemoveEntityAsCavity();
			}

			frontData::ClearNextFronts();
			frontData::SetLevelMaxIndex(frontInfo::NodeCounter());
			return Standard_True;
		}

		Standard_Boolean IsCavityRemoverFueled()
		{
			if (NOT frontData::NbUnCertaintyCavities())
			{
				return Standard_False;
			}

			if (frontInfo::AlgCondition() IS_EQUAL Aft_AlgCondition_Generation)
			{
				Stl_Vector<front_Ptr> entities;
				frontData::RetrieveUnCertaintyCavitiesTo(entities);

				for (auto& entity : entities)
				{
					Debug_Null_Pointer(entity);
					entity->RemoveEntityAsCavity();
				}

				frontData::InsertToPriority
				(
					entities
				);
				frontData::ClearUnCertaintyCavities();
				return Standard_True;
			}

			if (frontInfo::AlgCondition() IS_EQUAL Aft_AlgCondition_Repair)
			{
				Stl_Vector<front_Ptr> entities;
				frontData::RetrieveUnCertaintyCavitiesTo(entities);

				for (const auto& entity : entities)
				{
					Debug_Null_Pointer(entity);
					frontData::InsertToCertaintyCavities(entity);
				}

				frontData::ClearUnCertaintyCavities();
				return Standard_False;
			}

			FatalErrorIn(FunctionSIG)
				<< "Something goes wong!"
				<< abort(FatalError);

			return Standard_True;
		}

		Standard_Real CalcElementSize()
		{
			Debug_Null_Pointer(frontInfo::CurrentFront());
			const auto& coord = frontInfo::CurrentFront()->Centre();

			Debug_Null_Pointer(theSizeMap_);
			frontInfo::SetElementSize
			(
				theSizeMap_->CalcElementSize(coord)*
				SIZE_TO_HIGHT_ELEMENT_COEFF
			);
		}

		void CalcOptimumCoord()
		{
			Debug_Null_Pointer(frontInfo::CurrentFront());
			Debug_Null_Pointer(theSizeMap_);
			frontInfo::SetCoord
			(
				theSizeMap_->CalcOptimumCoord(frontInfo::ElementSize(),
					*frontInfo::CurrentFront())
			);
		}

		void CalcLocalFrontRadius()
		{
			Debug_Null_Pointer(frontInfo::CurrentFront());
			const auto& current = *frontInfo::CurrentFront();

			const auto& coord = frontInfo::Coord();

			Debug_Null_Pointer(theSizeMap_);
			const auto& sizeMap = *theSizeMap_;

			Standard_Real maxLenght = (Standard_Real)0.;
			forThose(Iter, 0, frontType::dim - 1)
			{
				Standard_Real length =
					sizeMap.CalcDistance(coord, current.Node(Iter)->Coord());

				if (length > maxLenght) maxLenght = length;
			}
			maxLenght = MAX(maxLenght, frontInfo::ElementSize() / SIZE_TO_HIGHT_ELEMENT_COEFF);

			frontInfo::SetLocFrontRadius
			(
				MAX(maxLenght, current.SearchRadius())
			);
		}

		void AddOptimumNodeTo(Stl_Vector<node_Ptr>& theNodes)
		{
			frontInfo::SetTempoNode
			(
				new nodeType(frontInfo::NodeCounter() + 1, frontInfo::Coord())
			);

			Debug_Null_Pointer(frontInfo::TempoNode());
			theNodes.push_back
			(
				frontInfo::TempoNode()
			);
			frontInfo::AppendedNode() = Standard_True;
		}

		void SortNodes
		(
			const Stl_Vector<node_Ptr>& theNodes
		) const
		{
			if (theNodes.size() < 2) return;

			Debug_Null_Pointer(frontInfo::CurrentFront());
			const auto& centre = frontInfo::CurrentFront()->Centre();

			core::Sort.Import(theNodes, centre, *theSizeMap_);
			core::Sort.Perform(theNodes.size());

			for (Standard_Integer i = 0; i < theNodes.size() - 1; i++)
			{
				while (i != mySort::Indices_[i])
				{
					Standard_Integer alt = mySort::Indices_[i];
					std::swap(theNodes[i], theNodes[alt]);
					std::swap(mySort::Indices_[i], mySort::Indices_[alt]);
				}
			}
		}

		void RemoveCurrentFromFront() const
		{
			Debug_Null_Pointer(frontInfo::CurrentFront());
			frontInfo::deAttachFromFront
			(
				frontInfo::CurrentFront()
			);
		}

		void RetrieveEffectiveFronts
		(
			const Stl_Vector<node_Ptr>& theNodes,
			const Stl_Vector<const frontType*>& theEntities,
			Stl_Vector<const frontType*>& theEffectives
		) const
		{
			Debug_Null_Pointer(frontInfo::CurrentFront());
			const auto& current =
				*frontInfo::CurrentFront();

			Point Pmin, Pmax;
			Point P;
			Pmin = Pmax = frontInfo::Coord();

			forThose(Iter, 0, frontType::nbNodes - 1)
			{
				Debug_Null_Pointer(current.Node(Iter));
				Update_Pmin_Pmax(current.Node(Iter)->Coord(), Pmin, Pmax);
			}

			for (const auto& node : theNodes)
			{
				Debug_Null_Pointer(node);
				Update_Pmin_Pmax(node->Coord(), Pmin, Pmax);
			}

			for (const auto& entityPtr : theEntities)
			{
				Debug_Null_Pointer(entityPtr);
				const auto& entity = *entityPtr;

				Standard_Boolean intersect = Standard_True;

				forThose(Iter, 0, frontType::nbNodes - 1)
				{
					const auto& point = entity.Node(Iter)->Coord();

					if (!IsIntersect(point, Pmin, Pmax))
					{
						intersect = Standard_False;
						break;
					}
				}

				if (intersect)
					theEffectives.push_back(entityPtr);
			}
		}

		void RetrieveLocalFrontNodes
		(
			Stl_Vector<node_Ptr>& theLocals,
			Stl_Vector<node_Ptr>& theSearching
		) const
		{
			Stl_Vector<node_Ptr> Locals;
			Debug_Null_Pointer(theSizeMap_);
			const auto& sizeMap = *theSizeMap_;

			frontData::GeometrySearch
			(
				sizeMap.CalcSearchRegion
				(
					frontInfo::LocFrontRadius(),
					frontInfo::Coord()
				),
				Locals
			);

			Debug_If_Condition_Message
			(
				frontInfo::SquareSearchRadius(),
				"Invalid Searching Radius"
			);
			const Standard_Real squareSearchingRadius =
				frontInfo::SquareSearchRadius();

			Debug_If_Condition_Message
			(
				frontInfo::SquareLocFrontRadius(),
				"Invalid Local Radius"
			);
			const Standard_Real squareLocalRadius =
				frontInfo::SquareLocFrontRadius();

			const Point& coord = frontInfo::Coord();

			for (auto& node : Locals)
			{
				Standard_Real radius =
					sizeMap.CalcSquareDistance(coord, node->Coord());

				if (radius <= squareSearchingRadius)
					theSearching.push_back
					(
						node
					);
				if (radius <= squareLocalRadius)
					theLocals.push_back
					(
						node
					);
			}
		}

		void RetrieveLocalFrontEntities
		(
			const Stl_Vector<node_Ptr>& theNodes,
			Stl_Vector<const frontType*>& theEntities
		) const
		{
			Adt_AvlTree<const frontType*> compact;
			compact.SetComparableFunction(&frontType::IsLessRaw);

			for (const auto& node : theNodes)
			{
				Debug_Null_Pointer(node);

				Stl_Vector<const frontType*> entities;
				RetrieveFronts(*node, entities);

				for (const auto& entity : entities)
				{
					Debug_Null_Pointer(entity);

					compact.InsertIgnoreDup
					(
						entity
					);
				}
			}
			compact.RetrieveTo(theEntities);
		}

		void NodesInRadius
		(
			const Standard_Real theRadius,
			const Point& theCoord,
			const Stl_Vector<node_Ptr>& theNodes,
			Stl_Vector<node_Ptr>& theInners
		) const
		{
			Debug_If_Condition_Message(theRadius <= 0., "Invalid Radius");
			const Standard_Real squareRadius = theRadius * theRadius;

			Debug_Null_Pointer(theSizeMap_);
			const auto& sizeMap = *theSizeMap_;

			for (auto& node : theNodes)
			{
				if (sizeMap.CalcSquareDistance(theCoord, node->Coord()) <= squareRadius)
					theInners.push_back
					(
						node
					);
			}
		}

		void ModifyLocalFront
		(
			const Standard_Real theFactor
		)
		{
			if (theFactor < (Standard_Real)1.0)
			{
				FatalErrorIn(FunctionSIG)
					<< "Invalid Factor"
					<< abort(FatalError);
			}

			if (frontData::IsGeometryEmpty())
			{
				return;
			}

			Debug_Null_Pointer(theSizeMap_);
			const auto& sizeMap = *theSizeMap_;

			Stl_Vector<node_Ptr> nodes;
			frontData::RetrieveFromGeometryTo(nodes);

			for (auto& ptr : nodes)
			{
				Debug_Null_Pointer(ptr);
				auto& node = *ptr;

				Stl_Vector<const frontType*> fronts;
				node.RetrieveFrontEdgesTo(fronts);

				Standard_Real maxLength = (Standard_Real)0.;
				for (auto& entity : fronts)
				{
					Debug_Null_Pointer(entity);
					if (entity->CharLength() > maxLength)
						maxLength = entity->CharLength();
				}

				maxLength *= theFactor;

				Debug_If_Condition_Message
				(
					maxLength <= (Standard_Real)0.,
					" Invalid MaxLength Value"
				);

				node.SetRadius
				(
					MAX(node.Radius(), maxLength)
				);

				Stl_Vector<node_Ptr> locals;
				frontData::GeometrySearch
				(
					sizeMap.CalcSearchRegion(maxLength, node.Coord()),
					locals
				);

				Stl_Vector<node_Ptr> inners;
				NodesInRadius
				(
					maxLength,
					node.Coord(),
					locals,
					inners
				);

				for (auto& innerNode : inners)
					innerNode->SetRadius
					(
						MAX(innerNode->Radius(), maxLength)
					);
			}
		}

		void RejectCurrent
		(
			const front_Ptr& theEntity
		)
		{
			Debug_Null_Pointer(theEntity);
			auto& entity = *theEntity;

			if (entity.IsOnFront())
			{
				FatalErrorIn(FunctionSIG)
					<< "Failed to Reject the current"
					<< abort(FatalError);
			}

			entity.MarkEntityAsCavity();

			frontInfo::AttachToFronts(theEntity);
			frontData::InsertToUnCertaintyCavities(theEntity);
		}

	public:

		Aft_Core(const sizeMap_ptr& theSizeMap)
			: theSizeMap_(theSizeMap)
		{}

		void RegisterElement()
		{
			globalData::InsertToElements(frontInfo::Element());
		}

		void UpdateFront()
		{
			Debug_Null_Pointer(frontInfo::ValidNode());
			const auto& node = *frontInfo::ValidNode();

			frontInfo::PointCondition() = Aft_PointCondition_PickedUp;

			// check for updating the nodes tree
			if (node.Index() IS_EQUAL frontInfo::NodeCounter() + 1)
			{
				frontInfo::NodeCounter()++;

				frontInfo::PointCondition() = Aft_PointCondition_NewPoint;

				// insert the new node into the NODES TREE
				frontData::InsertToGeometry(frontInfo::ValidNode());
			}

			frontInfo::SetPaires();

			frontInfo::UpdatePaires(*this);

			frontInfo::CreateElement();

			frontInfo::UpdateElement();

			RemoveEntitiesFromGeometry();

			RegisterElement();
		}
	};
}

#endif // !_Aft_Core_Header
