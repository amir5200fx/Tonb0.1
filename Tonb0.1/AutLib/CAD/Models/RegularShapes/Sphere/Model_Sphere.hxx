#pragma once
#ifndef _Model_Sphere_Header
#define _Model_Sphere_Header

#include <Model_RegularShapes.hxx>

namespace AutLib
{

	class Model_Sphere
		: public Model_RegularShapes
	{

	public:

		struct parameters
		{

			Standard_Real theRadius;

			Pnt3d theCentre;

			parameters()
				: theRadius(1.0)
			{
				theCentre.X() = 0;
				theCentre.Y() = 0;
				theCentre.Z() = 0;
			}

		};

	private:

		/*Private Data*/

		parameters theParameters_;

	public:

		Model_Sphere()
		{}

		Model_Sphere
		(
			const Standard_Real theRadius
		)
		{
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

#endif // !_Model_Sphere_Header
