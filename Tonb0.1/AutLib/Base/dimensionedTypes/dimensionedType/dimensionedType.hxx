#pragma once
#ifndef dimensionedType_Header
#define _dimensionedType_Header

#include <dimensionSet.hxx>

namespace AutLib
{

	template <class Type>
	class dimensioned
	{

		// private data

		//- Variable name
		word name_;

		//- The dimension set
		dimensionSet dimensions_;

		//- The data value
		Type value_;

	public:

		//- Component type
		typedef typename pTraits<Type>::cmptType cmptType;

		//- Construct from dictionary, with default value.
		static dimensioned<Type> lookupOrDefault
		(
			const word&,
			const dictionary&,
			const Type& defaultValue = pTraits<Type>::zero,
			const dimensionSet& dims = dimless
		);

		//- Construct from dictionary, with default value.
		//  If the value is not found, it is added into the dictionary.
		static dimensioned<Type> lookupOrAddToDict
		(
			const word&,
			dictionary&,
			const Type& defaultValue = pTraits<Type>::zero,
			const dimensionSet& dims = dimless
		);


		// Constructors

		//- Construct given a name, a value and its dimensionSet.
		dimensioned(const word&, const dimensionSet&, const Type);

		//- Construct from a dimensioned<Type> changing the name.
		dimensioned(const word&, const dimensioned<Type>&);

		//- Construct given a value (creates dimensionless value).
		dimensioned(const Type& t)
			: name_(AutLib::name(t))
			, dimensions_(dimless)
			, value_(t)
		{}

		//- Construct from Istream.
		explicit dimensioned(Istream&);

		//- Construct from an Istream with a given name
		dimensioned(const word&, Istream&);

		//- Construct from an Istream with a given name and dimensions
		dimensioned(const word&, const dimensionSet&, Istream&);

		// Member functions

		//- Return const reference to name.
		const word& name() const
		{
			return name_;
		}

		//- Return non-const reference to name.
		word& name()
		{
			return name_;
		}

		//- Return const reference to dimensions.
		const dimensionSet& dimensions() const
		{
			return dimensions_;
		}

		//- Return non-const reference to dimensions.
		dimensionSet& dimensions()
		{
			return dimensions_;
		}

		//- Return const reference to value.
		const Type& value() const
		{
			return value_;
		}

		//- Return non-const reference to value.
		Type& value()
		{
			return value_;
		}

		//- Return a component as a dimensioned<cmptType>
		dimensioned<cmptType> component(const direction d) const;

		//- Return a component with a dimensioned<cmptType>
		void replace(const direction, const dimensioned<cmptType>&);

		//- Return transpose.
		dimensioned<Type> T() const;

		//- Update the value of dimensioned<Type> if found in the dictionary.
		bool readIfPresent(const dictionary&);


		// Member operators

		//- Return a component as a dimensioned<cmptType>
		dimensioned<cmptType> operator[](const direction) const;

		void operator+=(const dimensioned<Type>&);
		void operator-=(const dimensioned<Type>&);
		void operator*=(const scalar);
		void operator/=(const scalar);


		// IOstream operators
		template <class Type>
		friend Istream& operator>>(Istream&, dimensioned<Type>&);

		template <class Type>
		friend Ostream& operator<<(Ostream&, const dimensioned<Type>&);
	};
}

#include <dimensionedTypeI.hxx>

#endif // !dimensionedType_Header
