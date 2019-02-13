#pragma once
#ifndef _NonConvergency_Iteration_Failure_Header
#define _NonConvergency_Iteration_Failure_Header

#include <error.hxx>

namespace AutLib
{

	class NonConvergency_Iteration_Failure
		: public error
	{

		/*Private Data*/
		
		label nbIterations_;

	public:

		NonConvergency_Iteration_Failure(const string& title)
			: error(title)
		{}

		virtual ~NonConvergency_Iteration_Failure()
		{}

		label NbIterations() const
		{
			return nbIterations_;
		}

		void SetNbIterations(const label theNbIterations)
		{
			nbIterations_ = theNbIterations;
		}

		OSstream& operator()
			(
				const char* functionName,
				const char* sourceFileName,
				const int sourceFileLineNumber,
				const label nbIterations
				);

		//- Exit : can be called for any error to exit program
		void exit(const int errNo = 1);

		//- Abort : used to stop code for fatal errors
		void abort();


		// Ostream operator

		friend Ostream& operator<<(Ostream&, const NonConvergency_Iteration_Failure&);
	};

	extern NonConvergency_Iteration_Failure IterFail;
}

#define IterFailedIn(fn, nbIters) IterFail(fn, __FILE__, __LINE__, nbIters)


#endif // !_NonConvergency_Iteration_Failure_Header
