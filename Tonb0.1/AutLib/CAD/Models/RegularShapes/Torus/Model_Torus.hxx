#pragma once
#ifndef _Model_Torus_Header
#define _Model_Torus_Header

#include <Model_RegularShapes.hxx>

namespace AutLib
{

	class Model_Torus
		: public Model_RegularShapes
	{

	public:

		struct parameters
		{

			Standard_Real theR1;
			Standard_Real theR2;

			Pnt3d theO;

			parameters()
				: theR1(2.0)
				, theR2(0.3)
			{
				theO.X() = 0;
				theO.Y() = 0;
				theO.Z() = 0;
			}
		};


	private:

		/*Private Data*/

		parameters theParameters_;

	public:

		Model_Torus()
		{}

		Model_Torus
		(
			const Standard_Real theR1,
			const Standard_Real theR2
		)
		{
			theParameters_.theR1 = theR1;
			theParameters_.theR2 = theR2;
		}

		parameters& Parameters()
		{
			return theParameters_;
		}

		const parameters& Parameters() const
		{
			return theParameters_;
		}

		void Make();
	};
}

#endif // !_Model_Torus_Header
