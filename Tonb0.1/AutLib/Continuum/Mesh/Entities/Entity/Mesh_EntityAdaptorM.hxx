#pragma once
#ifndef _Mesh_EntityAdaptorM_Header
#define _Mesh_EntityAdaptorM_Header

#define Mesh_EntityToEntityAdaptor(EntityName, toEntityName, EntityType)				\
	template<class EntityType>															\
	class Mesh_##EntityName##To##toEntityName##Adaptor									\
	{																					\
																						\
		/*Private Data*/																\
																						\
		Adt_AvlTree<const EntityType*> the##toEntityName##s_;							\
																						\
	public:																				\
																						\
		Mesh_##EntityName##To##toEntityName##Adaptor()									\
		{}																				\
																						\
		Standard_Integer Nb##toEntityName##s() const									\
		{																				\
			return the##toEntityName##s_.Size();										\
		}																				\
																						\
																						\
		Standard_Boolean InsertTo##toEntityName##s(const EntityType* theEntity)			\
		{																				\
			try																			\
			{																			\
				the##toEntityName##s_.Insert(theEntity);								\
				return Standard_False;													\
			}																			\
			catch (...)																	\
			{																			\
				return Standard_True;													\
			}																			\
		}																				\
																						\
																						\
		Standard_Boolean RemoveFrom##toEntityName##s(const EntityType* theEntity)		\
		{																				\
			try																			\
			{																			\
				the##toEntityName##s_.Remove(theEntity);								\
				return Standard_False;													\
			}																			\
			catch (...)																	\
			{																			\
				return Standard_True;													\
			}																			\
		}																				\
																						\
		Standard_Boolean IsOn##toEntityName##s(const EntityType* theEntity) const		\
		{																				\
			return the##toEntityName##s_.IsContains(theEntity);							\
		}																				\
																						\
		void Retrieve##toEntityName##sTo(Stl_Vector<const EntityType*>& theList) const	\
		{																				\
			the##toEntityName##s_.RetrieveTo(theList, 1);								\
		}																				\
																						\
		void Clear##toEntityName##s()													\
		{																				\
			the##toEntityName##s_.Clear();												\
		}																				\
	}

#endif // !_Mesh_EntityAdaptorM_Header
