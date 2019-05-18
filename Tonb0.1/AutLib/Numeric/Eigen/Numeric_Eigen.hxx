#pragma once
#ifndef _Numeric_Eigen_Header
#define _Numeric_Eigen_Header

#include <Adt_Ary2d.hxx>
#include <Adt_Ary1d.hxx>

namespace AutLib
{

	class Numeric_Eigen
	{

	public:

		typedef Adt_Ary2d<Standard_Real> realMat;
		typedef Adt_Ary1d<Standard_Real> realList;

	private:

		static realMat MatMul
		(
			const realMat& A, 
			const realMat& B
		)
		{
			Standard_Real Dot = 0;

			if (A.Size(1) NOT_EQUAL B.Size(0))
			{
				FatalErrorIn("static realMat MatMul(const realMat& A, const realMat& B)")
					<< "Error in MatMul function: different two size matrices"
					<< abort(FatalError);
			}

			Standard_Integer m = A.Size(0);
			Standard_Integer n = A.Size(1);
			Standard_Integer p = B.Size(0);
			Standard_Integer q = B.Size(1);

			realMat C(m, q);
			C.Init(0);

			for (Standard_Integer i = 0; i < m; i++)
				for (Standard_Integer j = 0; j < q; j++)
				{
					Dot = 0;
					for (Standard_Integer k = 0; k < n; k++)
						Dot += A[i][k] * B[k][j];
					C[i][j] = Dot;
				}

			MOVE(C);
		}

		static realList Diag(const realMat& A)
		{
			Standard_Integer n = A.Size(0);
			realList ary(n);
			ary.Init(0);
			for (Standard_Integer i = 0; i < n; i++)
				ary[i] = A[i][i];
			MOVE(ary);
		}

		static realMat Iden(const Standard_Integer n)
		{
			realMat a(n, n);
			a.Init(0);
			for (Standard_Integer i = 0; i < n; i++)
				a[i][i] = 1;
			MOVE(a);
		}

		static realMat tril(const realMat& A)
		{
			Standard_Integer n = A.Size(0);
			realMat ary(n, n);
			ary.Init(0);

			for (Standard_Integer j = 0; j < n; j++)
				for (Standard_Integer i = j; i < n; i++)
					ary[i][j] = A[i][j];
			MOVE(ary);
		}

		static realMat Transpose(const realMat& a)
		{
			Standard_Integer m = a.Size(0);
			Standard_Integer n = a.Size(1);

			realMat b(n, m);
			b.Init(0);
			for (Standard_Integer i = 0; i < n; i++)
				for (Standard_Integer j = 0; j < m; j++)
					b[j][i] = a[i][j];
			MOVE(b);
		}

		static realMat Invert_Low_Tri(const realMat& l)
		{
			realMat L = l;
			Standard_Integer n = L.Size(0);
			Standard_Real dot = 0;

			for (Standard_Integer j = 0; j < n - 1; j++)
			{
				L[j][j] = 1.0 / L[j][j];
				for (Standard_Integer i = j + 1; i < n; i++)
				{
					dot = 0;
					for (Standard_Integer k = j; k <= i - 1; k++)
						dot += L[i][k] * L[k][j];
					L[i][j] = -dot / L[i][i];
				}
			}
			L[n - 1][n - 1] = 1.0 / L[n - 1][n - 1];
			MOVE(L);
		}

		static void Choleski(realMat& a)
		{
			Standard_Integer n = a.Size(0);
			Standard_Real dot = 0;
			Standard_Real temp = 0;

			for (Standard_Integer j = 0; j < n; j++)
			{
				dot = 0;
				for (Standard_Integer k = 0; k < j; k++)
					dot += a[j][k] * a[j][k];
				temp = a[j][j] - dot;
				if (temp < 0.0)
				{
					FatalErrorIn("static void Choleski(realMat& a)")
						<< "Matrix is not positive definite"
						<< abort(FatalError);
				}
				a[j][j] = sqrt(temp);
				for (Standard_Integer i = j + 1; i < n; i++)
				{
					dot = 0;
					for (Standard_Integer k = 0; k < j; k++)
						dot += a[i][k] * a[j][k];
					a[i][j] = (a[i][j] - dot) / a[j][j];
				}
			}
			a = tril(a);
		}

		static void maxElem
		(
			const realMat& a,
			Standard_Real& amax, 
			Standard_Integer& k, 
			Standard_Integer& l
		)
		{
			Standard_Integer n = a.Size(0);
			amax = 0;
			for (Standard_Integer i = 0; i < n - 1; i++)
				for (Standard_Integer j = i + 1; j < n; j++)
					if (ABS(a[i][j]) >= amax)
					{
						amax = ABS(a[i][j]);
						k = i;
						l = j;
					}
		}

		static void Rotate
		(
			Standard_Integer k,
			Standard_Integer l, 
			realMat& A, 
			realMat& P
		)
		{
			Standard_Integer n = A.Size(0);
			Standard_Real diff = A[l][l] - A[k][k];
			Standard_Real t;
			Standard_Real phi;
			if (ABS(A[k][l]) < ABS(diff)*1.0e-36)
				t = A[k][l];
			else
			{
				phi = diff / (2 * A[k][l]);
				t = 1.0 / (ABS(phi) + sqrt(phi*phi + 1.0));
				if (phi < 0.0) t = -t;
			}
			Standard_Real c = 1.0 / sqrt(t*t + 1.0);
			Standard_Real s = t * c;
			Standard_Real tau = s / (1.0 + c);
			Standard_Real temp = A[k][l];
			A[k][l] = 0;
			A[k][k] -= t * temp;
			A[l][l] += t * temp;

			for (Standard_Integer i = 0; i < k; i++)
			{
				temp = A[i][k];
				A[i][k] = temp - s * (A[i][l] + tau * temp);
				A[i][l] += s * (temp - tau * A[i][l]);
			}

			for (Standard_Integer i = k + 1; i < l; i++)
			{
				temp = A[k][i];
				A[k][i] = temp - s * (A[i][l] + tau * A[k][i]);
				A[i][l] += s * (temp - tau * A[i][l]);
			}

			for (Standard_Integer i = l + 1; i < n; i++)
			{
				temp = A[k][i];
				A[k][i] = temp - s * (A[l][i] + tau * temp);
				A[l][i] += s * (temp - tau * A[l][i]);
			}

			for (Standard_Integer i = 0; i < n; i++)
			{
				temp = P[i][k];
				P[i][k] = temp - s * (P[i][l] + tau * P[i][k]);
				P[i][l] += s * (temp - tau * P[i][l]);
			}
		}

		static void sortEigen
		(
			realList& eVals,
			realMat& eVecs
		)
		{
			Standard_Integer n = eVals.Size();
			Standard_Integer indx;
			Standard_Real val;
			Standard_Real temp;

			for (Standard_Integer i = 0; i < n - 1; i++)
			{
				indx = i;
				val = eVals[i];
				for (Standard_Integer j = i + 1; j < n; j++)
					if (eVals[j] < val)
					{
						indx = j;
						val = eVals[j];
					}
				if (indx != i)
				{
					temp = eVals[i];
					eVals[i] = eVals[indx];
					eVals[indx] = temp;
					swapCols(i, indx, eVecs);
				}
			}
		}

		static void stdForm
		(
			const realMat& A,
			const realMat& B,
			realMat& H,
			realMat& T
		)
		{
			realMat L = B;
			Choleski(L);
			realMat Linv = Invert_Low_Tri(L);
			T = Transpose(Linv);
			H = MatMul(Linv, MatMul(A, T));
		}

		template<typename T>
		static inline void swapRows
		(
			const Standard_Integer i,
			const Standard_Integer j,
			Adt_Ary2d<T>& a
		)
		{
			Standard_Integer n = a.Size(0);
			Adt_Ary1d<T> temp(n);

			for (Standard_Integer k = 0; k < n; k++)
				temp[k] = a[i][k];
			for (Standard_Integer k = 0; k < n; k++)
				a[i][k] = a[j][k];
			for (Standard_Integer k = 0; k < n; k++)
				a[j][k] = temp[k];
		}

		template<typename T>
		static inline void swapCols
		(
			const Standard_Integer i, 
			const Standard_Integer j,
			Adt_Ary2d<T>& a
		)
		{
			Standard_Integer n = a.Size(0);
			Adt_Ary1d<T> temp(n);

			for (Standard_Integer k = 0; k < n; k++)
				temp[k] = a[k][i];
			for (Standard_Integer k = 0; k < n; k++)
				a[k][i] = a[k][j];
			for (Standard_Integer k = 0; k < n; k++)
				a[k][j] = temp[k];
		}

	public:


		static void CalcEigen
		(
			const realMat& A,
			realList& eVals,
			realMat& eVecs, 
			const Standard_Real tol
		)
		{
			realMat a = A;

			Standard_Integer n = a.Size(0);
			Standard_Integer maxRot = 5 * n*n;  // Limit number of rotations

			realMat P = Iden(n);  // Initialize rotation matrix

			Standard_Integer k, l;
			Standard_Real amax;

			for (Standard_Integer i = 1; i <= maxRot; i++)  // Begin Jacobi rotations
			{
				maxElem(a, amax, k, l);
				if (amax < tol)
				{
					eVals = Diag(a);
					eVecs = P;
					return;
				}
				Rotate(k, l, a, P);
			}

			FatalErrorIn("static void CalcEigen(const realMat& A, realList& eVals, realMat& eVecs, const Standard_Real tol)")
				<< "Too many Jacobi rotations"
				<< abort(FatalError);
		}

		static void CalcGenEigen
		(
			const realMat& A,
			const realMat& B, 
			realList& eVals, 
			realMat& eVecs, 
			const Standard_Real eps
		)
		{
			Standard_Integer n = A.Size(0);
			realMat H(n, n), T(n, n);
			realMat Z(n, n);

			H.Init(0);
			T.Init(0);
			Z.Init(0);

			stdForm(A, B, H, T);
			CalcEigen(H, eVals, Z, eps);
			eVecs = MatMul(T, Z);

			Standard_Real dot;
			Standard_Real xMag;
			for (Standard_Integer i = 0; i < n; i++)
			{
				dot = 0;
				for (Standard_Integer k = 0; k < n; k++)
					dot += eVecs[k][i] * eVecs[k][i];
				xMag = sqrt(dot);
				for (Standard_Integer k = 0; k < n; k++)
					eVecs[k][i] /= xMag;
			}

			sortEigen(eVals, eVecs);
		}
		
	};
}

#endif // !_Numeric_Eigen_Header
