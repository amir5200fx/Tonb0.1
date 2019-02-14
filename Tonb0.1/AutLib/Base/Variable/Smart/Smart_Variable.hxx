#pragma once
#ifndef _Smart_Variable_Header
#define _Smart_Variable_Header

#include <Standard_TypeDef.hxx>
#include <dimensionedType.hxx>

namespace AutLib
{

	class Smart_VariableSpecified
	{

		/*Private Data*/

		Standard_Boolean IsSpecified_;

	protected:

		void doSpecify()
		{
			IsSpecified_ = Standard_True;
		}

		void unSpecify()
		{
			IsSpecified_ = Standard_False;
		}

	public:

		Smart_VariableSpecified()
			: IsSpecified_(Standard_False)
		{}

		Smart_VariableSpecified(const Standard_Boolean Sp)
			: IsSpecified_(Sp)
		{}

		Standard_Boolean IsSpecified() const
		{
			return IsSpecified_;
		}
	};


	template<class T>
	class Smart_Variable
		: public dimensioned<T>
		, public Smart_VariableSpecified
	{

		/*Private Data*/

	public:

		// Constructors

		//- Construct given a name, a value and its dimensionSet.
		Smart_Variable(const word& theName, const dimensionSet& dim, const T t)
			: dimensioned<T>(theName, dim, t)
			, Smart_VariableSpecified(Standard_True)
		{}

		//- Construct from a dimensioned<Type> changing the name.
		Smart_Variable(const word& theName, const dimensioned<T>& dim)
			: dimensioned<T>(theName, dim)
		{}

		//- Construct given a value (creates dimensionless value).
		Smart_Variable(const T& t)
			: dimensioned<T>(t)
			, Smart_VariableSpecified(Standard_True)
		{}

		//- Construct from Istream.
		explicit Smart_Variable(Istream& is)
			: dimensioned<T>(is)
			, Smart_VariableSpecified(Standard_True)
		{}

		//- Construct from an Istream with a given name
		Smart_Variable(const word& theName, Istream& is)
			: dimensioned<T>(theName, is)
			, Smart_VariableSpecified(Standard_True)
		{}

		//- Construct from an Istream with a given name and dimensions
		Smart_Variable(const word& theName, const dimensionSet& dim, Istream& is)
			: dimensioned<T>(theName, dim, is)
			, Smart_VariableSpecified(Standard_True)
		{}
	};
}

#endif // !_Smart_Variable_Header
