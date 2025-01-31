#include <dimensionedScalar.hxx>

#include <scalar.hxx>
#include <dimensionedType.hxx>

namespace AutLib
{

	dimensionedScalar operator+(const dimensionedScalar& ds1, const scalar s2)
	{
		return ds1 + dimensionedScalar(s2);
	}

	dimensionedScalar operator+(const scalar s1, const dimensionedScalar& ds2)
	{
		return dimensionedScalar(s1) + ds2;
	}

	dimensionedScalar operator-(const dimensionedScalar& ds1, const scalar s2)
	{
		return ds1 - dimensionedScalar(s2);
	}

	dimensionedScalar operator-(const scalar s1, const dimensionedScalar& ds2)
	{
		return dimensionedScalar(s1) - ds2;
	}

	dimensionedScalar operator*(const dimensionedScalar& ds1, const scalar s2)
	{
		return ds1 * dimensionedScalar(s2);
	}

	dimensionedScalar operator/(const scalar s1, const dimensionedScalar& ds2)
	{
		return dimensionedScalar(s1) / ds2;
	}

	dimensionedScalar pow(const dimensionedScalar& ds, const dimensionedScalar& expt)
	{
		return dimensionedScalar
		(
			"pow(" + ds.name() + ',' + expt.name() + ')',
			pow(ds.dimensions(), expt),
			::pow(ds.value(), expt.value())
		);
	}

	dimensionedScalar pow3(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pow3(" + ds.name() + ')',
			pow3(ds.dimensions()),
			pow3(ds.value())
		);
	}

	dimensionedScalar pow4(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pow4(" + ds.name() + ')',
			pow4(ds.dimensions()),
			pow4(ds.value())
		);
	}

	dimensionedScalar pow5(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pow5(" + ds.name() + ')',
			pow5(ds.dimensions()),
			pow5(ds.value())
		);
	}

	dimensionedScalar pow6(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pow6(" + ds.name() + ')',
			pow6(ds.dimensions()),
			pow6(ds.value())
		);
	}

	dimensionedScalar sqrt(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"sqrt(" + ds.name() + ')',
			pow(ds.dimensions(), dimensionedScalar("0.5", dimless, 0.5)),
			::sqrt(ds.value())
		);
	}

	dimensionedScalar cbrt(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"cbrt(" + ds.name() + ')',
			pow(ds.dimensions(), dimensionedScalar("(1|3)", dimless, 1.0 / 3.0)),
			::cbrt(ds.value())
		);
	}

	dimensionedScalar hypot
	(
		const dimensionedScalar& x,
		const dimensionedScalar& y
	)
	{
		return dimensionedScalar
		(
			"hypot(" + x.name() + ',' + y.name() + ')',
			x.dimensions() + y.dimensions(),
			::hypot(x.value(), y.value())
		);
	}

	dimensionedScalar sign(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"sign(" + ds.name() + ')',
			sign(ds.dimensions()),
			::AutLib::sign(ds.value())
		);
	}

	dimensionedScalar pos(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"pos(" + ds.name() + ')',
			pos(ds.dimensions()),
			::AutLib::pos(ds.value())
		);
	}

	dimensionedScalar neg(const dimensionedScalar& ds)
	{
		return dimensionedScalar
		(
			"neg(" + ds.name() + ')',
			neg(ds.dimensions()),
			::AutLib::neg(ds.value())
		);
	}

	dimensionedScalar exp(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("exp(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"exp(" + ds.name() + ')',
			dimless,
			::exp(ds.value())
		);
	}

	dimensionedScalar log(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("log(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"log(" + ds.name() + ')',
			dimless,
			::log(ds.value())
		);
	}

	dimensionedScalar log10(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("log10(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"log10(" + ds.name() + ')',
			dimless,
			::log10(ds.value())
		);
	}

	dimensionedScalar sin(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("sin(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"sin(" + ds.name() + ')',
			dimless,
			::sin(ds.value())
		);
	}

	dimensionedScalar cos(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("cos(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"cos(" + ds.name() + ')',
			dimless,
			::cos(ds.value())
		);
	}

	dimensionedScalar tan(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("tan(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"tan(" + ds.name() + ')',
			dimless,
			::tan(ds.value())
		);
	}

	dimensionedScalar asin(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("asin(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"asin(" + ds.name() + ')',
			dimless,
			::asin(ds.value())
		);
	}

	dimensionedScalar acos(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("acos(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"acos(" + ds.name() + ')',
			dimless,
			::acos(ds.value())
		);
	}

	dimensionedScalar atan(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("atan(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"atan(" + ds.name() + ')',
			dimless,
			::atan(ds.value())
		);
	}

	dimensionedScalar sinh(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("sinh(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"sinh(" + ds.name() + ')',
			dimless,
			::sinh(ds.value())
		);
	}

	dimensionedScalar cosh(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("cosh(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"cosh(" + ds.name() + ')',
			dimless,
			::cosh(ds.value())
		);
	}

	dimensionedScalar tanh(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("tanh(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"tanh(" + ds.name() + ')',
			dimless,
			::tanh(ds.value())
		);
	}

	dimensionedScalar asinh(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("asinh(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"asinh(" + ds.name() + ')',
			dimless,
			::asinh(ds.value())
		);
	}

	dimensionedScalar acosh(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("acosh(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"acosh(" + ds.name() + ')',
			dimless,
			::acosh(ds.value())
		);
	}

	dimensionedScalar atanh(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("atanh(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"atanh(" + ds.name() + ')',
			dimless,
			::atanh(ds.value())
		);
	}

	dimensionedScalar erf(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("erf(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"erf(" + ds.name() + ')',
			dimless,
			::erf(ds.value())
		);
	}

	dimensionedScalar erfc(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("erfc(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"erfc(" + ds.name() + ')',
			dimless,
			::erfc(ds.value())
		);
	}

	dimensionedScalar lgamma(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("lgamma(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"lgamma(" + ds.name() + ')',
			dimless,
			::lgamma(ds.value())
		);
	}

	dimensionedScalar j0(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("_j0(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"_j0(" + ds.name() + ')',
			dimless,
			::_j0(ds.value())
		);
	}

	dimensionedScalar j1(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("_j1(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"_j1(" + ds.name() + ')',
			dimless,
			::_j1(ds.value())
		);
	}

	dimensionedScalar y0(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("_y0(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"_y0(" + ds.name() + ')',
			dimless,
			::_y0(ds.value())
		);
	}

	dimensionedScalar y1(const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("_y1(const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"_y1(" + ds.name() + ')',
			dimless,
			::_y1(ds.value())
		);
	}

	dimensionedScalar jn(const int n, const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("_jn(const int n, const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"_jn(" + name(n) + ',' + ds.name() + ')',
			dimless,
			::_jn(n, ds.value())
		);
	}

	dimensionedScalar yn(const int n, const dimensionedScalar& ds)
	{
		if (!ds.dimensions().dimensionless())
		{
			FatalErrorIn("_yn(const int n, const dimensionedScalar& ds)")
				<< "ds not dimensionless"
				<< abort(FatalError);
		}

		return dimensionedScalar
		(
			"_yn(" + name(n) + ',' + ds.name() + ')',
			dimless,
			::_yn(n, ds.value())
		);
	}
}