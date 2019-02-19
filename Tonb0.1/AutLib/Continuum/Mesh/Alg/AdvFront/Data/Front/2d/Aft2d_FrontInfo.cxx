//#include <Aft2d_FrontInfo.hxx>
//
//#include <Aft2d_Edge.hxx>
//#include <Aft2d_Node.hxx>
//
//void AutLib::Aft2d_FrontInfo::deAttachFromMesh(pHandle(Aft2d_TriElement) theElement)
//{
//	Debug_Null_Pointer(theElement);
//
//	auto& element = *theElement;
//
//	Debug_Null_Pointer(element.Node(0));
//	Debug_Null_Pointer(element.Node(1));
//	Debug_Null_Pointer(element.Node(2));
//
//	element.Node(0)->RemoveFromElements(theElement.get());
//	element.Node(1)->RemoveFromElements(theElement.get());
//	element.Node(2)->RemoveFromElements(theElement.get());
//
//	Debug_Null_Pointer(element.Edge(0));
//	Debug_Null_Pointer(element.Edge(1));
//	Debug_Null_Pointer(element.Edge(2));
//
//	auto& edge0 = *element.Edge(0);
//	auto& edge1 = *element.Edge(1);
//	auto& edge2 = *element.Edge(2);
//
//	if (NOT edge0.RightElement() AND NOT edge0.IsOnBoundary())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "Contradictory data"
//			<< abort(FatalError);
//	}
//
//	if (NOT edge1.RightElement() AND NOT edge1.IsOnBoundary())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "Contradictory data"
//			<< abort(FatalError);
//	}
//
//	if (NOT edge2.RightElement() AND NOT edge2.IsOnBoundary())
//	{
//		FatalErrorIn(FunctionSIG)
//			<< "Contradictory data"
//			<< abort(FatalError);
//	}
//
//	if (edge0.RightElement() IS_EQUAL &element)
//	{
//		edge0.SetRightElement(nullptr);
//		edge0.Reverse();
//	}
//	else
//		edge0.SetLeftElement(nullptr);
//
//	if (edge1.RightElement() IS_EQUAL &element)
//	{
//		edge1.SetRightElement(nullptr);
//		edge1.Reverse();
//	}
//	else
//		edge1.SetLeftElement(nullptr);
//
//	if (edge2.RightElement() IS_EQUAL &element)
//	{
//		edge2.SetRightElement(nullptr);
//		edge2.Reverse();
//	}
//	else
//		edge2.SetLeftElement(nullptr);
//
//	Aft2d_TriElement* neighbor0 = const_cast<Aft2d_TriElement*>(element.Element(0));
//	Aft2d_TriElement* neighbor1 = const_cast<Aft2d_TriElement*>(element.Element(1));
//	Aft2d_TriElement* neighbor2 = const_cast<Aft2d_TriElement*>(element.Element(2));
//
//	if (neighbor0)
//	{
//		neighbor0->SetElement(neighbor0->OppositeVertexIndex(element), nullptr);
//	}
//
//	if (neighbor1)
//	{
//		neighbor1->SetElement(neighbor1->OppositeVertexIndex(element), nullptr);
//	}
//
//	if (neighbor2)
//	{
//		neighbor2->SetElement(neighbor2->OppositeVertexIndex(element), nullptr);
//	}
//}
//
//namespace AutLib
//{
//	static inline Standard_Boolean IsPaired
//	(
//		const Aft2d_Node& theN0,
//		const Aft2d_Node& theN1,
//		const Aft2d_Node& theV0,
//		const Aft2d_Node& theV1
//	)
//	{
//		if (
//			Geom::IsPairedSegments
//			(
//				theN0.Index(),
//				theN1.Index(),
//				theV0.Index(),
//				theV1.Index()
//			)
//			)
//			return Standard_True;
//		return Standard_False;
//	}
//}
//
//void AutLib::Aft2d_FrontInfo::SetPairedEdges()
//{
//	SetCreatedEdge0(0);
//	SetCreatedEdge1(0);
//
//	SetPairedEdge0(0);
//	SetPairedEdge1(0);
//
//	Debug_Null_Pointer(CurrentFront());
//	const auto& current = *CurrentFront();
//
//	Debug_Null_Pointer(current.Node0());
//	Debug_Null_Pointer(current.Node1());
//	const auto& node0 = *current.Node0();
//	const auto& node1 = *current.Node1();
//
//	Debug_Null_Pointer(ValidNode());
//	const auto& validNode = *ValidNode();
//
//	Stl_Vector<const Aft2d_Edge*> edgesList;
//	validNode.RetrieveEdgesTo(edgesList);
//
//	for (const auto& edgePtr : edgesList)
//	{
//		Debug_Null_Pointer(edgePtr);
//
//		const auto& edge = *edgePtr;
//
//		if (
//			!IsPairedEdge1()
//			&& IsPaired
//			(
//				*edge.Node0(),
//				*edge.Node1(),
//				node0,
//				validNode
//			)
//			)
//		{
//			SetPairedEdge1(edgePtr);
//		}
//
//		if (
//			!IsPairedEdge0()
//			&& IsPaired
//			(
//				*edge.Node0(),
//				*edge.Node1(),
//				node1,
//				validNode
//			)
//			)
//		{
//			SetPairedEdge0(edgePtr);
//		}
//	}
//}
//
//void AutLib::Aft2d_FrontInfo::CreateElement()
//{
//	ElementCounter()++;
//	SetElement(new Aft2d_TriElement(ElementCounter()));
//
//	Debug_Null_Pointer(Element());
//	auto& element = *Element();
//
//	Debug_Null_Pointer(CurrentFront());
//	const auto& current = *CurrentFront();
//
//	element.SetNode(0, current.Node0());
//	element.SetNode(1, current.Node1());
//	element.SetNode(2, ValidNode());
//
//	if (IsCreatedEdge0())
//	{
//		element.SetEdge(0, CreatedEdge0());
//	}
//	else
//	{
//		element.SetEdge(0, PairedEdge0());
//	}
//
//	if (IsCreatedEdge1())
//	{
//		element.SetEdge(1, CreatedEdge1());
//	}
//	else
//	{
//		element.SetEdge(1, PairedEdge1());
//	}
//
//	element.SetEdge(2, CurrentFront());
//}
//
//void AutLib::Aft2d_FrontInfo::UpdateElement()
//{
//	Debug_Null_Pointer(Element());
//	auto& element = *Element();
//
//	AttachToMeshNodes(Element());
//
//	/* Attach the element to the edges */
//	Debug_Null_Pointer(CurrentFront());
//	auto& current = *CurrentFront();
//
//	// update right/ left side element pointer of the faces
//	// update adjacent elements
//	current.SetLeftElement(&element);
//	element.SetElement(2, current.RightElement());
//
//	if (current.RightElement())
//	{
//		const_cast<Aft2d_TriElement*>(current.RightElement())->SetElement
//		(
//			current.RightElement()->OppositeVertexIndex(current),
//			&element
//		);
//	}
//
//	if (IsCreatedEdge0())
//	{
//		CreatedEdge0()->SetRightElement(&element);
//		element.SetElement(0, nullptr);
//	}
//	else
//	{
//		Debug_Null_Pointer(PairedEdge0());
//		auto& edge = *PairedEdge0();
//
//		Aft2d_TriElement* neighbor = const_cast<Aft2d_TriElement*>(edge.RightElement());
//
//		element.SetElement(0, neighbor);
//
//		if (edge.LeftElement())
//		{
//			FatalErrorIn(FunctionSIG)
//				<< "Contradiction Data"
//				<< abort(FatalError);
//		}
//
//		edge.SetLeftElement(&element);
//
//		if (neighbor)
//		{
//			neighbor->SetElement(neighbor->OppositeVertexIndex(edge), &element);
//		}
//	}
//
//	if (IsCreatedEdge1())
//	{
//		CreatedEdge1()->SetRightElement(&element);
//		element.SetElement(1, nullptr);
//	}
//	else
//	{
//		Debug_Null_Pointer(PairedEdge1());
//		auto& edge = *PairedEdge1();
//
//		Aft2d_TriElement* neighbor = const_cast<Aft2d_TriElement*>(edge.RightElement());
//
//		element.SetElement(1, neighbor);
//
//		if (edge.LeftElement())
//		{
//			FatalErrorIn(FunctionSIG)
//				<< "Contradiction Data"
//				<< abort(FatalError);
//		}
//
//		edge.SetLeftElement(&element);
//
//		if (neighbor)
//		{
//			neighbor->SetElement(neighbor->OppositeVertexIndex(edge), &element);
//		}
//	}
//}