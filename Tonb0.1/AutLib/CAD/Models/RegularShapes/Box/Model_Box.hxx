#pragma once
#ifndef _Model_Box_Header
#define _Model_Box_Header

#include <Model_RegularShapes.hxx>

namespace AutLib
{

	class Model_Box
		: public Model_RegularShapes
	{

	public:

		struct parameters
		{

			Standard_Real theDx;
			Standard_Real theDy;
			Standard_Real theDz;

			Pnt3d theP0;

			parameters()
				: theDx(1.0)
				, theDy(1.0)
				, theDz(1.0)
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

		Model_Box()
		{}

		Model_Box
		(
			const Standard_Real theDx,
			const Standard_Real theDy,
			const Standard_Real theDz
		)
		{
			theParameters_.theDx = theDx;
			theParameters_.theDy = theDy;
			theParameters_.theDz = theDz;
		}

		Model_Box
		(
			const Pnt3d& theP0,
			const Standard_Real theDx,
			const Standard_Real theDy,
			const Standard_Real theDz
		)
		{
			theParameters_.theDx = theDx;
			theParameters_.theDy = theDy;
			theParameters_.theDz = theDz;
			theParameters_.theP0 = theP0;
		}

		Model_Box
		(
			const Pnt3d& theP0,
			const Pnt3d& theP1
		)
		{
			theParameters_.theDx = theP1.X() - theP0.X();
			theParameters_.theDy = theP1.Y() - theP0.Y();
			theParameters_.theDz = theP1.Z() - theP0.Z();
			theParameters_.theP0 = theP0;
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

#endif // !_Model_Box_Header
