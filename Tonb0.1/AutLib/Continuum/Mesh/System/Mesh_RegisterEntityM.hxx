#pragma once
#ifndef _Mesh_RegisterEntityM_Header
#define _Mesh_RegisterEntityM_Header

#define Mesh_RegisterEntity(EntityName, EntityType)											\
	template<class EntityType>																\
	class Mesh_Register##EntityName															\
	{																						\
																							\
		/*Private Data*/																	\
																							\
		Adt_AvlTree<pHandle(EntityType)> the##EntityName##s_;								\
																							\
	public:																					\
																							\
		Mesh_Register##EntityName()															\
		{}																					\
																							\
		Standard_Integer Nb##EntityName##s() const											\
		{																					\
			return the##EntityName##s_.Size();												\
		}																					\
																							\
		Standard_Boolean InsertTo##EntityName##s(const pHandle(EntityType)& theEntity)		\
		{																					\
			try																				\
			{																				\
				the##EntityName##s_.Insert(theEntity);										\
				return Standard_False;														\
			}																				\
			catch (...)																		\
			{																				\
				return Standard_True;														\
			}																				\
		}																					\
																							\
		Standard_Boolean RemoveFrom##EntityName##s(const pHandle(EntityType)& theEntity)	\
		{																					\
			try																				\
			{																				\
				the##EntityName##s_.Remove(theEntity);										\
				return Standard_False;														\
			}																				\
			catch (...)																		\
			{																				\
				return Standard_True;														\
			}																				\
		}																					\
																							\
		Standard_Boolean IsOn##EntityName##s(const pHandle(EntityType)& theEntity) const	\
		{																					\
			return the##EntityName##s_.IsContains(theEntity);								\
		}																					\
																							\
		void Retrieve##EntityName##sTo(Stl_Vector<pHandle(EntityType)>& theList) const		\
		{																					\
			the##EntityName##s_.RetrieveTo(theList, 1);										\
		}																					\
																							\
		void Clear##EntityName##s()															\
		{																					\
			the##EntityName##s_.Clear();													\
		}																					\
	}

#endif // !_Mesh_RegisterEntityM_Header
