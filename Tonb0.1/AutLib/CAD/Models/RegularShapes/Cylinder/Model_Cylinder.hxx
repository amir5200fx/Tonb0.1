#pragma once
#ifndef _Model_Cylinder_Header
#define _Model_Cylinder_Header

#include <Model_RegularShapes.hxx>

namespace AutLib
{

	class Model_Cylinder
		: public Model_RegularShapes
	{

	public:

		struct parameters
		{

			Standard_Real theRadius;
			Standard_Real theHeight;

			Pnt3d theP0;

			parameters()
				: theRadius(1.0)
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

		Model_Cylinder()
		{}

		Model_Cylinder
		(
			const Standard_Real theRadius,
			const Standard_Real theHeight
		)
		{
			theParameters_.theHeight = theHeight;
			theParameters_.theRadius = theRadius;
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

#endif // !_Model_Cylinder_Header
