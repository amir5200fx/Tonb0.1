#pragma once
#ifndef _Model_Cone_Header
#define _Model_Cone_Header

#include <Model_RegularShapes.hxx>

namespace AutLib
{

	class Model_Cone
		: public Model_RegularShapes
	{

	public:

		struct parameters
		{

			Standard_Real theR1;
			Standard_Real theR2;
			Standard_Real theHeight;

			Pnt3d theP0;

			parameters()
				: theR1(0.0)
				, theR2(1.0)
				, theHeight(1.0)
			{
				theP0.X() = 0;
				theP0.Y() = 0;
				theP0.Z() = 0;
			}
		};


	private:

		/*Private Data*/

		parameters theParameters_;

	public:

		Model_Cone()
		{}

		Model_Cone
		(
			const Standard_Real theR1,
			const Standard_Real theR2,
			const Standard_Real theHeight
		)
		{
			theParameters_.theR1 = theR1;
			theParameters_.theR2 = theR2;
			theParameters_.theHeight = theHeight;
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

#endif // !_Model_Cone_Header
