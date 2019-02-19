#pragma once
#ifndef _Aft2d_FrontInfo_Header
#define _Aft2d_FrontInfo_Header

#define RESET_FRONT_INFO
#include <Aft_FrontInfo.hxx>
#include <Aft2d_FrontInfoAdaptor.hxx>
#include <Mesh_Counters.hxx>
#include <Aft2d_TriElement.hxx>

namespace AutLib
{

	typedef Aft_FrontInfo<Aft2d_FrontInfoAdaptor>
		Aft2d_FrontInfoBase;

	class Aft2d_FrontInfo
		: public Aft2d_FrontInfoBase
		, public Mesh2d_FrontCounter
	{

		/*Private Data*/

	protected:

		static void AttachToMeshNodes(pHandle(Aft2d_TriElement) theElement)
		{
			Debug_Null_Pointer(theElement);
			auto& element = *theElement;

			element.Node(0)->InsertToElements(theElement.get());
			element.Node(1)->InsertToElements(theElement.get());
			element.Node(2)->InsertToElements(theElement.get());
		}

		static void AttachToMeshNodes(pHandle(Aft2d_Edge) theEdge)
		{
			Debug_Null_Pointer(theEdge);
			auto& edge = *theEdge;

			edge.Node0()->InsertToEdges(theEdge.get());
			edge.Node1()->InsertToEdges(theEdge.get());
		}

		static void AttachToFrontNodes(pHandle(Aft2d_Edge) theEdge)
		{
			Debug_Null_Pointer(theEdge);
			auto& edge = *theEdge;

			edge.Node0()->InsertToFrontEdges(theEdge.get());
			edge.Node1()->InsertToFrontEdges(theEdge.get());
		}

		static void AttachToFronts(pHandle(Aft2d_Edge) theEdge)
		{
			AttachToFrontNodes(theEdge);
		}

		static void deAttachFromMesh(pHandle(Aft2d_TriElement) theElement);

		static void deAttachFromMesh(pHandle(Aft2d_Edge) theEdge)
		{
			Debug_Null_Pointer(theEdge);
			auto& edge = *theEdge;

			if (!edge.IsOrphan())
			{
				FatalErrorIn(FunctionSIG)
					<< " Try to delete a non-orphan edge!"
					<< abort(FatalError);
			}

			edge.Node0()->RemoveFromEdges(theEdge.get());
			edge.Node1()->RemoveFromEdges(theEdge.get());
		}


		static void deAttachFromFront(pHandle(Aft2d_Edge) theEdge)
		{
			Debug_Null_Pointer(theEdge);
			auto& edge = *theEdge;

			edge.Node0()->RemoveFromFrontEdges(theEdge.get());
			edge.Node1()->RemoveFromFrontEdges(theEdge.get());
		}

		void SetPairedEdges();

		template<class SizeMap>
		void UpdateEdges(const SizeMap& theSizeMap)
		{
			Debug_Null_Pointer(CurrentFront());
			const auto& current = *CurrentFront();

			if (IsPairedEdge0())
			{
				SetCreatedEdge0(nullptr);

				// remove the old coicident face from the GF
				deAttachFromFront(PairedEdge0());

				// remove cavity face
				if (PairedEdge0()->IsOnCavity())
					PairedEdge0()->RemoveEntityAsCavity();
			}
			else
			{
				EdgeCounter()++;

				const auto& P1 = ValidNode()->Coord();
				const auto& P2 = current.Node1()->Coord();

				SetCreatedEdge0(new Aft2d_Edge(EdgeCounter()));
				auto& edge = *CreatedEdge0();

				edge.SetCharLength(theSizeMap.CalcDistance(P1, P2));
				edge.SetCentre(theSizeMap.CalcCentreOf(P1, P2));
				edge.SetNode0(ValidNode());
				edge.SetNode1(current.Node1());

				AttachToFrontNodes(CreatedEdge0());
				AttachToMeshNodes(CreatedEdge0());
			}

			if (IsPairedEdge1())
			{
				SetCreatedEdge1(nullptr);

				// remove the old coicident face from the GF
				deAttachFromFront(PairedEdge1());

				// remove cavity face
				if (PairedEdge1()->IsOnCavity())
					PairedEdge1()->RemoveEntityAsCavity();
			}
			else
			{
				EdgeCounter()++;

				const auto& P1 = ValidNode()->Coord();
				const auto& P2 = current.Node0()->Coord();

				SetCreatedEdge1(new Aft2d_Edge(EdgeCounter()));
				auto& edge = *CreatedEdge1();

				edge.SetCharLength(theSizeMap.CalcDistance(P1, P2));
				edge.SetCentre(theSizeMap.CalcCentreOf(P1, P2));
				edge.SetNode0(ValidNode());
				edge.SetNode1(current.Node0());

				AttachToFrontNodes(CreatedEdge1());
				AttachToMeshNodes(CreatedEdge1());
			}
		}

	public:

		Aft2d_FrontInfo()
		{}

		void SetPaires()
		{
			SetPairedEdges();
		}

		template<class SizeMap>
		void UpdatePaires(const SizeMap& theSizeMap)
		{
			UpdateEdges(theSizeMap);
		}

		void CreateElement();

		void UpdateElement();
	};
}

#endif // !_Aft2d_FrontInfo_Header
