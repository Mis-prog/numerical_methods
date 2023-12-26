#pragma once
#include <stdio.h>
#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include <time.h>
#include <vector>

using namespace std;
const double eps = 1e-5;

double randomValue(double min, double max) {
	min = 0;
	return (double)(rand()) / RAND_MAX * (max - min) + min;
}

void printVector2dDouble(vector<vector<double>> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			cout << " " << vec[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void printVector1dDouble(vector<double> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << " " << vec[i];
	}
	cout << endl;
}

vector<double> MatrixVectorMultiply(int N, vector<vector<double>> Matrix, vector<double> Vector)
{
	vector<double> VectorSolution(N, 0);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			VectorSolution[i] += Matrix[i][j] * Vector[j];
		}
	}
	return VectorSolution;
}

vector<double> MatrixLentaVectorMultiply(int N, int lw, vector<vector<double>> MatrixLenta, vector<double> Vector)
{
	vector<double> VectorSolution(N, 0);
	for (int i = 0; i < N; i++)
	{
		//cout << "string = " << i << endl;
		for (int j = 0; j < N; j++)
		{
			int ind = j - i + lw;
			if ((ind >= 0) && (ind < 2 * lw + 1))
			{
				VectorSolution[i] += MatrixLenta[i][ind] * Vector[j];
				//cout << Vector[ind] << "  ";
			}
		}
		//cout << endl;
	}
	return VectorSolution;
}

double VectorVectorMult(int N, vector<double> Vector1, vector<double> Vector2)
{
	double result = 0;
	for (int i = 0; i < N; i++)
	{
		result += Vector1[i] * Vector2[i];
	}
	return result;
}

vector<vector<double>> MatrixMatrixmult(int N, vector<vector<double>> M1, vector<vector<double>> M2)
{
	vector<vector<double>> Mres(N, vector<double>(N, 0));
	double num;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			num = 0;
			for (int k = 0; k < N; k++)
			{
				num += M1[i][k] * M2[k][j];
			}
			Mres[i][j] = num;
		}
	}

	return Mres;
}

vector<vector<double>> MatrixTranspose(int N, vector<vector<double>> M)
{
	double num;
	double t;
	for (int i = 0; i < N; ++i)
	{
		for (int j = i; j < N; ++j)
		{
			t = M[i][j];
			M[i][j] = M[j][i];
			M[j][i] = t;
		}
	}

	return M;
}

vector<vector<double>> MatrixtoLenta(int N, int l, vector<vector<double>> Matrix,
	vector<vector<double>> MatrixLenta)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Matrix[i][j] != 0)
				MatrixLenta[i][j - i + l] = Matrix[i][j];
		}
	}
	return MatrixLenta;
}


vector<double> Jacobian(int N, int lw, vector<vector<double>> A, vector<double> b)
{
	vector<double> xprev(N, 0); // ��������� �����������
	vector<double> x(N, 0); // ������� �����������
	double diff; // ������� ����� ������� � ���������� ������������
	int iter = 0;
	do
	{
		iter++;
		for (int i = 0; i < N; i++)
		{
			x[i] = b[i];
			for (int j = 0; j < N; j++)
			{
				int ind = j - i + lw;
				if ((j != i) && (ind >= 0) && (ind < 2 * lw + 1))
					x[i] -= A[i][ind] * xprev[j];
			}
			x[i] /= A[i][lw];
		}
		diff = fabs(x[0] - xprev[0]);
		for (int i = 0; i < N; i++)
		{
			if (fabs(x[i] - xprev[i]) > diff)
				diff = fabs(x[i] - xprev[i]);
			xprev[i] = x[i];
		}
	} while (diff > eps);
	cout << " " << iter << " Iterations" << endl;
	return x;
}


vector<double> SORLenta(int N, int l, vector<vector<double>> A, vector<double> b, double relaxation)
{
	vector<double> xprev(N, 0); // ��������� �����������
	vector<double> x(N, 0); // ������� �����������
	double diff; // ������� ����� ������� � ���������� ������������
	int iter = 0;

	do
	{
		iter++;
		for (int i = 0; i < N; i++)
		{
			x[i] = b[i];
			for (int j = 0; j < i; j++)
			{
				int ind = j - i + l;
				if ((j != i) && (ind >= 0) && (ind < 2 * l + 1))
					x[i] -= A[i][ind] * x[j];
			}
			for (int j = i + 1; j < N; j++)
			{
				int ind = j - i + l;
				if ((j != i) && (ind >= 0) && (ind < 2 * l + 1))
					x[i] -= A[i][ind] * xprev[j];
			}
			x[i] /= A[i][l];
			x[i] *= relaxation;
			x[i] += (1 - relaxation) * xprev[i];
		}
		diff = fabs(x[0] - xprev[0]);
		for (int i = 0; i < N; i++)
		{
			if (fabs(x[i] - xprev[i]) > diff)
				diff = fabs(x[i] - xprev[i]);
			xprev[i] = x[i];
		}
	} while (diff > eps);
	cout << " " << iter << " Iterations" << endl;
	return x;
}


vector<double> CGMLenta(int N, int l, vector<vector<double>> A, vector<double> b)
{
	vector<double> xprev(N, 0);
	vector<double> x(N, 0);
	vector<double> rprev(N, 0);
	vector<double> r(N, 0);
	vector<double> pprev(N, 0);
	vector<double> p(N, 0);
	double alpha = 0;
	double beta = 0;
	vector<double> Ax(N, 0);
	vector<double> Ap(N, 0);
	Ax = MatrixLentaVectorMultiply(N, l, A, xprev);
	for (int i = 0; i < N; i++)
	{

		rprev[i] = b[i] - Ax[i];
		pprev[i] = rprev[i];

	}

	double diff; // ������� ����� ������� � ���������� ������������
	int iter = 0;
	do
	{
		iter++;
		Ap = MatrixLentaVectorMultiply(N, l, A, pprev);
		alpha = (double)(VectorVectorMult(N, rprev, rprev) / VectorVectorMult(N, Ap, pprev));
		for (int i = 0; i < N; i++)
		{
			x[i] = xprev[i] + alpha * pprev[i];
			r[i] = rprev[i] - alpha * Ap[i];
		}
		beta = (double)(VectorVectorMult(N, r, r) / VectorVectorMult(N, rprev, rprev));

		for (int i = 0; i < N; i++)
		{
			p[i] = r[i] + beta * pprev[i];
		}

		diff = fabs(r[0] - rprev[0]);

		for (int i = 0; i < N; i++)
		{
			if (fabs(r[i] - rprev[i]) > diff)
				diff = fabs(r[i] - rprev[i]);
			xprev[i] = x[i];
		}

		for (int i = 0; i < N; i++)
		{
			pprev[i] = p[i];
			xprev[i] = x[i];
			rprev[i] = r[i];
		}
	} while (diff > eps);

	cout << " " << iter << " Iterations" << endl;

	return x;
}

void norma(int N, vector<double> solTrue, vector<double> solOur)
{
	double max = fabs(solOur[0] - solTrue[0]);
	for (int i = 0; i < N; i++)
	{
		if (fabs(solOur[i] - solTrue[i]) > max)
			max = fabs(solOur[i] - solTrue[i]);
	}
	cout << " Norm = " << max << endl;
}