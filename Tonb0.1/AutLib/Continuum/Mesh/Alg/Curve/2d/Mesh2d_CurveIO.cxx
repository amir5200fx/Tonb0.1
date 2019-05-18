#include <Mesh2d_Curve.hxx>

#include <Entity2d_Chain.hxx>
#include <TecPlot.hxx>

namespace AutLib
{

	template<>
	void Mesh2d_Curve::ExportToPlt(OFstream& File) const
	{
#if MESH_DEBUG
		if (NOT theChain_)
		{
			FatalErrorIn("void Mesh2d_Curve::ExportToPlt(OFstream& File) const")
				<< "The Chain has not been created!"
				<< abort(FatalError);
		}
#endif
		if (NOT theChain_)
		{
			return;
		}

		theChain_->ExportToPlt(File);
	}
}