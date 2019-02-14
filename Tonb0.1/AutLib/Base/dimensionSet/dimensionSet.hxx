#pragma once
#ifndef _dimensionSet_Header
#define _dimensionSet_Header

#include <scalar.hxx>
#include <dimensionedScalarFwd.hxx>
#include <debugSwitch.hxx>

namespace AutLib
{

	class dimensionSet
	{

	public:

		// Member constants

		enum
		{
			nDimensions = 7    // Number of dimensions in SI is 7
		};

		//- Define an enumeration for the names of the dimension exponents
		enum dimensionType
		{
			MASS,               // kilogram   kg
			LENGTH,             // metre      m
			TIME,               // second     s
			TEMPERATURE,        // Kelvin     K
			MOLES,              // mole       mol
			CURRENT,            // Ampere     A
			LUMINOUS_INTENSITY  // Candela    Cd
		};


		// Static data members

		static const scalar smallExponent;

	private:

		// private data

		// dimensionSet stored as an array of dimension exponents
		scalar exponents_[nDimensions];

	public:

		// Declare name of the class and its debug switch
		static const char* typeName_() { return "dimensionSet"; }

		static const word typeName;
		static debug::debugSwitch debug;


		// Constructors

		//- Construct given individual dimension exponents for all
		//  seven dimensions
		dimensionSet
		(
			const scalar mass,
			const scalar length,
			const scalar time,
			const scalar temperature,
			const scalar moles,
			const scalar current,
			const scalar luminousIntensity
		);

		//- Construct given individual dimension exponents for first
		//  five dimensions
		dimensionSet
		(
			const scalar mass,
			const scalar length,
			const scalar time,
			const scalar temperature,
			const scalar moles
		);

		//- Construct from Istream
		dimensionSet(Istream&);


		// Member functions

		bool dimensionless() const;
		void reset(const dimensionSet&);


		// Member operators

		scalar operator[](const dimensionType) const;
		scalar& operator[](const dimensionType);
		bool operator==(const dimensionSet&) const;
		bool operator!=(const dimensionSet&) const;

		bool operator=(const dimensionSet&) const;

		bool operator+=(const dimensionSet&) const;
		bool operator-=(const dimensionSet&) const;
		bool operator*=(const dimensionSet&);
		bool operator/=(const dimensionSet&);


		// Friend functions

		friend dimensionSet max(const dimensionSet&, const dimensionSet&);
		friend dimensionSet min(const dimensionSet&, const dimensionSet&);
		friend dimensionSet cmptMultiply(const dimensionSet&, const dimensionSet&);
		friend dimensionSet cmptDivide(const dimensionSet&, const dimensionSet&);

		friend dimensionSet pow(const dimensionSet&, const scalar);
		friend dimensionSet pow(const dimensionSet&, const dimensionedScalar&);
		friend dimensionSet pow(const dimensionedScalar&, const dimensionSet&);

		friend dimensionSet sqr(const dimensionSet&);
		friend dimensionSet pow3(const dimensionSet&);
		friend dimensionSet pow4(const dimensionSet&);
		friend dimensionSet pow5(const dimensionSet&);
		friend dimensionSet pow6(const dimensionSet&);

		friend dimensionSet sqrt(const dimensionSet&);
		friend dimensionSet magSqr(const dimensionSet&);
		friend dimensionSet mag(const dimensionSet&);
		friend dimensionSet sign(const dimensionSet&);
		friend dimensionSet pos(const dimensionSet&);
		friend dimensionSet neg(const dimensionSet&);
		friend dimensionSet inv(const dimensionSet&);
		friend dimensionSet hinv(const dimensionSet&);

		//- Function to check the argument is dimensionless
		//  for transcendental functions
		friend dimensionSet trans(const dimensionSet&);

		//- Return the argument; transformations do not change the dimensions
		friend dimensionSet transform(const dimensionSet&);


		// Friend operators

		friend dimensionSet operator-(const dimensionSet&);

		friend dimensionSet operator+(const dimensionSet&, const dimensionSet&);

		friend dimensionSet operator-(const dimensionSet&, const dimensionSet&);

		friend dimensionSet operator*(const dimensionSet&, const dimensionSet&);

		friend dimensionSet operator/(const dimensionSet&, const dimensionSet&);

		friend dimensionSet operator&(const dimensionSet&, const dimensionSet&);

		friend dimensionSet operator^(const dimensionSet&, const dimensionSet&);

		friend dimensionSet operator&&(const dimensionSet&, const dimensionSet&);


		// IOstream operators

		friend Istream& operator>>(Istream&, dimensionSet&);
		friend Ostream& operator<<(Ostream&, const dimensionSet&);
	};
}

#include <dimensionSets.hxx>

#endif // !_dimensionSet_Header
