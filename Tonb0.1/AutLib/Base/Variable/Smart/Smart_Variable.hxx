#pragma once
#ifndef _Smart_Variable_Header
#define _Smart_Variable_Header

#include <Standard_TypeDef.hxx>
#include <Global_Named.hxx>
#include <UnitSystem.hxx>
#include <error.hxx>
#include <OSstream.hxx>

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


	template<class Type, class UnitTypeExp>
	class Smart_Variable
		: public Global_Named
		, public Smart_VariableSpecified
	{

		typename typedef UnitType
			<
			UnitTypeExp::MASS,
			UnitTypeExp::LENGTH,
			UnitTypeExp::TIME,
			UnitTypeExp::TEMPERATURE,
			UnitTypeExp::MOLES,
			UnitTypeExp::CURRENT,
			UnitTypeExp::LUMINOUS_INTENSITY
			>::type unit;

		/*Private Data*/

		//- The data value
		Type theValue_;

		unit theUnit_;

	public:

		Smart_Variable(const word& theName, const Type x)
			: Global_Named(theName)
			, Smart_VariableSpecified(Standard_True)
			, theValue_(x)
		{}

		void SetUnit(const unit theUnit)
		{
			if (theUnit_ != theUnit)
			{
				theValue_ *= ConvertUnit(theUnit_, theUnit);
				theUnit_ = theUnit;
			}
		}

		Type Value() const
		{
			if (!IsSpecified())
			{
				FatalErrorIn("Type Value() const")
					<< " No value is specified: " << Name()
					<< abort(FatalError);
			}
			return theValue_;
		}

		Type& Value()
		{
			if (!IsSpecified()) doSpecify();
			return theValue_;
		}

		unit Unit() const
		{
			return theUnit_;
		}
	};

	template<class Type>
	class Smart_Variable<Type, NullUnitExps>
		: public Global_Named
		, public Smart_VariableSpecified
	{

		/*Private Data*/

		//- The data value
		Type theValue_;

	public:

		Smart_Variable(const word& theName, const Type x)
			: Global_Named(theName)
			, Smart_VariableSpecified(Standard_True)
			, theValue_(x)
		{}

		Type Value() const
		{
			if (!IsSpecified())
			{
				FatalErrorIn("Type Value() const")
					<< " No value is specified: " << Name()
					<< abort(FatalError);
			}
			return theValue_;
		}

		Type& Value()
		{
			if (!IsSpecified()) doSpecify();
			return theValue_;
		}
	};

	namespace Variables
	{

		typedef Smart_Variable<Standard_Real, MassUnitExps> mass;
		typedef Smart_Variable<Standard_Real, LengthUnitExps> length;
		typedef Smart_Variable<Standard_Real, PressureUnitExps> pressure;
		typedef Smart_Variable<Standard_Real, VelocityUnitExps> velocity;
		typedef Smart_Variable<Standard_Real, AccelerationUnitExps> acceleration;
		typedef Smart_Variable<Standard_Real, DensityUnitExps> density;
		typedef Smart_Variable<Standard_Real, PowerUnitExps> power;
		typedef Smart_Variable<Standard_Real, ForceUnitExps> force;
		typedef Smart_Variable<Standard_Real, DynViscosityUnitExps> dynViscosity;
		typedef Smart_Variable<Standard_Real, KinViscosityUnitExps> kinViscosity;

		typedef Smart_Variable<Standard_Real, NullUnitExps> realDimless;
		typedef Smart_Variable<unsigned int, NullUnitExps> labelDimless;
	}
}

#endif // !_Smart_Variable_Header
