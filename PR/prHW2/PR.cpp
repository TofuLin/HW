#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <fstream>
#include <cv.h>
#include <highgui.h>
#include <iomanip>
#include <Windows.h>
#include "MatPlot.h"

#define STEP 100
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)
#define M_PI 3.14159265358979323846
using namespace std; 
using namespace MatPlot;
void PrintMatrix(CvMat *Matrix, int Rows, int Cols);

double ran1(long *idum)
{
	int j;
	long k;
	static long iy = 0;
	static long iv[NTAB];
	double temp;
	if (*idum <= 0 || !iy) {
		if (-(*idum) < 1)
			*idum = 1;
		else
			*idum = -(*idum);
		for (j = NTAB + 7; j >= 0; j--) {
			k = (*idum) / IQ;
			*idum = IA*(*idum - k*IQ) - IR*k;
			if (*idum < 0)
				*idum += IM;
			if (j < NTAB)
				iv[j] = *idum;
		}
		iy = iv[0];
	}
	k = (*idum) / IQ;
	*idum = IA*(*idum - k*IQ) - IR*k;
	if (*idum < 0)
		*idum += IM;
	j = iy / NDIV;
	iy = iv[j];
	iv[j] = *idum;
	if ((temp = AM*iy) > RNMX)
		return RNMX;
	else
		return temp;
}
	double rand_normal(long *idum,double mean, double var)
	{
		double ran1(long *idum);
		static double n2 = 0.0;
		static int n2_cached = 0;
		if (!n2_cached)
		{
			double x, y, r;
			do
			{
				x = 2.0*ran1(idum) - 1.0;
				y = 2.0*ran1(idum) - 1.0;

				r = x*x + y*y;
			} while (r == 0.0 || r > 1.0);
			{
				double d = sqrt(-2.0*log(r) / r);
				double n1 = x*d;
				n2 = y*d;
				double result = n1*sqrt(var)+mean;
				//double result = n1*(1/sqrt(var))*Q;
				n2_cached = 1;
				return result;
			}
		}
		else
		{
			n2_cached = 0;
			//return n2*(1 / sqrt(var))*Q;
			return n2*sqrt(var)+mean;
		}
	}

	int main(int argc, char *argv[]) {

		fstream fx, fy, fx2, fy2;
		fx.open("datax.out", ios::out);
		fy.open("datay.out", ios::out);
		fx2.open("datax2.out", ios::out);
		fy2.open("datay2.out", ios::out);
		int mean = 0;
		int std = 1;
		double p1 = 0.9;
		double p2 = 0.5;
		double eigendet = -0.9873;
		double cov1[2][2] = { 4,4,4,9 };
		double cov2[2][2] = { 4,4,4,9 };

		double ranclass1[20];
		double ranclass2[20];
		double randomx[100];
		double randomy[100];
		double randomx2[100];
		double randomy2[100];
		double ran_1[20];
		double ran_2[20];
		long seed = (long)time(NULL);

		CvMat *Matrix1 = cvCreateMat(2, 2, CV_64FC1);
		CvMat *EigenValue_Row = cvCreateMat(2, 1, CV_64FC1);
		CvMat *EigenValue = cvCreateMat(2, 2, CV_64FC1);
		CvMat *EigenVector = cvCreateMat(2, 2, CV_64FC1);

		cvSetData(Matrix1, cov1, Matrix1->step);
		cvSetZero(EigenValue);

		cvEigenVV(Matrix1, EigenVector, EigenValue_Row, DBL_EPSILON);

		cout << "\nThe EigenValue1 is:\n";
		PrintMatrix(EigenValue_Row, EigenValue_Row->rows, EigenValue_Row->cols);

		cout << "\nThe EigenVector1 is:\n";
		PrintMatrix(EigenVector, EigenVector->rows, EigenVector->cols);
		double meanv1[2] = { 1,2 };
		double meanv[2] = { 4,6 };
		double eigendetinver = -1.0128;
	double ev1[2] = { 11.22,1.78 };
	double ev2[2] = { 11.22,1.78 };
	double eigenv1[2][2] = {0.48,0.87,0.87,-0.48};
	double eigenv2[2][2] = { 0.48,0.87,0.87,-0.48 };
	CvMat *Matrix2 = cvCreateMat(2, 2, CV_64FC1);
	CvMat *EigenValue_Row2 = cvCreateMat(2, 1, CV_64FC1);
	CvMat *EigenValue2 = cvCreateMat(2, 2, CV_64FC1);
	CvMat *EigenVector2 = cvCreateMat(2, 2, CV_64FC1);

	cvSetData(Matrix2, cov2, Matrix2->step);
	cvSetZero(EigenValue2);

	cvEigenVV(Matrix2, EigenVector2, EigenValue_Row2, DBL_EPSILON,-1,-1);

	cout << "\nThe EigenValue2 is:\n";
	PrintMatrix(EigenValue_Row2, EigenValue_Row2->rows, EigenValue_Row2->cols);

	cout << "\nThe EigenVector2 is:\n";
	PrintMatrix(EigenVector2, EigenVector2->rows, EigenVector2->cols);
	for (int i = 0; i < STEP; ++i)
	{
		for (int a = 0; a < 1; a++) {
			/*ranclass1[a] = (rand_normal(&seed, *meanv1,ev1[a]))*(cos(eigenv1[1][0]));
			ranclass2[a] = (rand_normal(&seed, meanv1[a + 1], ev1[a]))*sin((eigenv1[1][0]));
			ran_1[a] = (rand_normal(&seed, *meanv, ev1[a]))*cos(eigenv1[1][0]);
			ran_2[a] = (rand_normal(&seed, meanv[a + 1], ev2[a]));
			*/
			ranclass1[a] = (rand_normal(&seed, *meanv1, ev1[a]));
			ranclass2[a] = (rand_normal(&seed, meanv1[a + 1], ev1[a]));
			ran_1[a] = (rand_normal(&seed, *meanv, ev1[a]));
			ran_2[a] = (rand_normal(&seed, meanv[a + 1], ev2[a]));
		}
		randomx[i] = *ranclass1*cos(eigenv1[1][0]);
		fx << randomx[i] << endl;
		randomy[i] = *ranclass2;
		fy << randomy[i] << endl;
		randomx2[i] = *ran_1*cos(eigenv2[1][0]);
		fx2 << randomx2[i] << endl;
		randomy2[i] = *ran_2;
		fy2 << randomy2[i] << endl;
	}

	int N{ 100 };
	MatPlotInit();
	scatter(randomx, randomy, N, 'r');
	scatter(randomx2, randomy2, N, 'b');
	Sleep(1000000);
	MatPlotClose();
	fx.close();
	fy.close();
	fx2.close();
	fy2.close();
	system("Pause");
	return 0;
}
void PrintMatrix(CvMat *Matrix, int Rows, int Cols)
{
	for (int i = 0; i<Rows; i++)
	{
		for (int j = 0; j<Cols; j++)
		{
			cout<<fixed << setprecision(2) << " "<<cvGet2D(Matrix, i, j).val[0] ;
		}
		printf("\n");
	}
}
