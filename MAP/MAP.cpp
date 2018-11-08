#include <iostream>                              
#include <sstream>                               
#include <fstream>                                                                             　                               
#include "MAP.h"      
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<math.h>
#include<stdio.h>
#include <opencv2/core/mat.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/ml.hpp>
using namespace std;
using namespace cv;
using namespace ml;
double R[3];
int m = 0, n = 0;
Mat wine1(30, 13, CV_64F);
Mat wine2(35, 13, CV_64F);
Mat wine3(24, 13, CV_64F);
Mat winetest2(89, 13, CV_64F);
Mat rantest2(100, 20, CV_64F);
Mat cov, cov2, cov3, mu, mu2, mu3, covr1, covr2;
double cova, cova2, cova3, covra1, covra2;
Mat wm1, wm2, wm3, wm1t, wm2t, wm3t;
Mat mean = (Mat_<double>(20, 1) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
Mat invcov1, invcov2, invcov3, invcovr1, invcovr2;
double P[89], O[89], Q[89], p[100], q[100];
double a, b, c, d, e;

vector<oridata> testdata;
vector<oridata> traindata;
vector<oridata2> testdata2;
vector<oridata2> traindata2;
ifstream   file1;
Mat winetrain(89, 13, CV_32F);
Mat winetest(89, 13, CV_32F);
Mat winetotal(178, 13, CV_32F);
Mat rantrain(100, 20, CV_32F);
Mat rantest(100, 20, CV_32F);
Mat rantotal(200,20,CV_32F);
void DataRead(vector<oridata> &data, const char* fileName)
{
	file1.open(fileName);
	int s = trainnum;
	string line;
	oridata Ttrainingwine;
	for (int a = 0; a < s; a++)
	{
		file1 >> line;
		while (line.find(',') > 0 && line.find(',') < line.length())
		{
			line[line.find(',')] = ' ';
		}
		istringstream stream(line);
		stream >> Ttrainingwine.M1 >> Ttrainingwine.M2 >> Ttrainingwine.M3 >> Ttrainingwine.M4 >> Ttrainingwine.M5 >> Ttrainingwine.M6 >> Ttrainingwine.M7 >> Ttrainingwine.M8 >>
			Ttrainingwine.M9 >> Ttrainingwine.M10 >> Ttrainingwine.M11 >> Ttrainingwine.M12 >> Ttrainingwine.M13 >> Ttrainingwine.M14;
		data.push_back(Ttrainingwine);
	}
	file1.close();
}
void DataReadt(vector<oridata> &data, const char* fileName)
{
	file1.open(fileName);
	int s = testtotal;
	string line;
	oridata Ttrainingwine;
	for (int a = 0; a < s; a++)
	{
		file1 >> line;
		while (line.find(',') > 0 && line.find(',') < line.length())
		{
			line[line.find(',')] = ' ';
		}
		istringstream stream(line);
		stream >> Ttrainingwine.M1 >> Ttrainingwine.M2 >> Ttrainingwine.M3 >> Ttrainingwine.M4 >> Ttrainingwine.M5 >> Ttrainingwine.M6 >> Ttrainingwine.M7 >> Ttrainingwine.M8 >>
			Ttrainingwine.M9 >> Ttrainingwine.M10 >> Ttrainingwine.M11 >> Ttrainingwine.M12 >> Ttrainingwine.M13 >> Ttrainingwine.M14;
		data.push_back(Ttrainingwine);
	}
	file1.close();
}
void DataReadr(vector<oridata2> &data, const char* fileName)
{
	file1.open(fileName);
	int s = 100;
	string line;
	oridata2 Ttrainingwine;
	for (int a = 0; a < s; a++)
	{
		file1 >> line;
		while (line.find(',') > 0 && line.find(',') < line.length())
		{
			line[line.find(',')] = ' ';
		}
		istringstream stream(line);
		stream >> Ttrainingwine.N1 >> Ttrainingwine.N2 >> Ttrainingwine.N3 >> Ttrainingwine.N4 >> Ttrainingwine.N5 >> Ttrainingwine.N6 >> Ttrainingwine.N7 >> Ttrainingwine.N8 >>
			Ttrainingwine.N9 >> Ttrainingwine.N10 >> Ttrainingwine.N11 >> Ttrainingwine.N12 >> Ttrainingwine.N13 >> Ttrainingwine.N14 >> Ttrainingwine.N15 >> Ttrainingwine.N16
			>> Ttrainingwine.N17 >> Ttrainingwine.N18 >> Ttrainingwine.N19 >> Ttrainingwine.N20 >> Ttrainingwine.N21;
		data.push_back(Ttrainingwine);
	}
	file1.close();
}

void DataReadrt(vector<oridata2> &data, const char* fileName)
{
	file1.open(fileName);
	int s = testtotal2;
	string line;
	oridata2 Ttrainingwine;
	for (int a = 0; a < s; a++)
	{
		file1 >> line;
		while (line.find(',') > 0 && line.find(',') < line.length())
		{
			line[line.find(',')] = ' ';
		}
		istringstream stream(line);
		stream >> Ttrainingwine.N1 >> Ttrainingwine.N2 >> Ttrainingwine.N3 >> Ttrainingwine.N4 >> Ttrainingwine.N5 >> Ttrainingwine.N6 >> Ttrainingwine.N7 >> Ttrainingwine.N8 >>
			Ttrainingwine.N9 >> Ttrainingwine.N10 >> Ttrainingwine.N11 >> Ttrainingwine.N12 >> Ttrainingwine.N13 >> Ttrainingwine.N14 >> Ttrainingwine.N15 >> Ttrainingwine.N16
			>> Ttrainingwine.N17 >> Ttrainingwine.N18 >> Ttrainingwine.N19 >> Ttrainingwine.N20 >> Ttrainingwine.N21;
		data.push_back(Ttrainingwine);
	}
	file1.close();
}
void Prior()
{
	int number1 = 0;
	int number2 = 0;
	int number3 = 0;
	int a;
	for (a = 0; a < trainnum; a++)
	{
		if (traindata[a].M1 == 1)
		{
			number1++;
		}
		if (traindata[a].M1 == 2)
		{
			number2++;
		}
		if (traindata[a].M1 == 3)
		{
			number3++;
		}
	}


	R[0] = (double)number1 / (double)trainnum;
	R[1] = (double)number2 / (double)trainnum;
	R[2] = (double)number3 / (double)trainnum;

}



void cov_mean() {

	for (int i = 0; i < 30; i++) {

		for (int j = 0; j <13; j++) {
			wine1.at<double>(i, j) = traindata[i].M2;
			if (j = 1) {
				wine1.at<double>(i, j) = traindata[i].M3;
			}
			if (j = 2) {
				wine1.at<double>(i, j) = traindata[i].M4;
			}
			if (j = 3) {
				wine1.at<double>(i, j) = traindata[i].M5;
			}
			if (j = 4) {
				wine1.at<double>(i, j) = traindata[i].M6;
			}
			if (j = 5) {
				wine1.at<double>(i, j) = traindata[i].M7;
			}
			if (j = 6) {
				wine1.at<double>(i, j) = traindata[i].M8;
			}
			if (j = 7) {
				wine1.at<double>(i, j) = traindata[i].M9;
			}
			if (j = 8) {
				wine1.at<double>(i, j) = traindata[i].M10;
			}
			if (j = 9) {
				wine1.at<double>(i, j) = traindata[i].M11;
			}
			if (j = 10) {
				wine1.at<double>(i, j) = traindata[i].M12;
			}
			if (j = 11) {
				wine1.at<double>(i, j) = traindata[i].M13;
			}
			if (j = 12) {
				wine1.at<double>(i, j) = traindata[i].M14;
			}
		}

	}

	calcCovarMatrix(wine1, cov, mu, CV_COVAR_NORMAL | CV_COVAR_ROWS);
	cov = cov / (wine1.rows - 1);



	for (int i = 30; i < 65; i++) {
		for (int j = 0; j <13; j++) {
			wine2.at<double>(i - 30, j) = traindata[i].M2;
			if (j = 1) {
				wine2.at<double>(i - 30, j) = traindata[i].M3;
			}
			if (j = 2) {
				wine2.at<double>(i - 30, j) = traindata[i].M4;
			}
			if (j = 3) {
				wine2.at<double>(i - 30, j) = traindata[i].M5;
			}
			if (j = 4) {
				wine2.at<double>(i - 30, j) = traindata[i].M6;
			}
			if (j = 5) {
				wine2.at<double>(i - 30, j) = traindata[i].M7;
			}
			if (j = 6) {
				wine2.at<double>(i - 30, j) = traindata[i].M8;
			}
			if (j = 7) {
				wine2.at<double>(i - 30, j) = traindata[i].M9;
			}
			if (j = 8) {
				wine2.at<double>(i - 30, j) = traindata[i].M10;
			}
			if (j = 9) {
				wine2.at<double>(i - 30, j) = traindata[i].M11;
			}
			if (j = 10) {
				wine2.at<double>(i - 30, j) = traindata[i].M12;
			}
			if (j = 11) {
				wine2.at<double>(i - 30, j) = traindata[i].M13;
			}
			if (j = 12) {
				wine2.at<double>(i - 30, j) = traindata[i].M14;
			}
		}

	}

	calcCovarMatrix(wine2, cov2, mu2, CV_COVAR_NORMAL | CV_COVAR_ROWS);
	cov2 = cov2 / (wine2.rows - 1);



	for (int i = 65; i < 89; i++) {

		for (int j = 0; j <13; j++) {
			wine3.at<double>(i - 65, j) = traindata[i].M2;
			if (j = 1) {
				wine3.at<double>(i - 65, j) = traindata[i].M3;
			}
			if (j = 2) {
				wine3.at<double>(i - 65, j) = traindata[i].M4;
			}
			if (j = 3) {
				wine3.at<double>(i - 65, j) = traindata[i].M5;
			}
			if (j = 4) {
				wine3.at<double>(i - 65, j) = traindata[i].M6;
			}
			if (j = 5) {
				wine3.at<double>(i - 65, j) = traindata[i].M7;
			}
			if (j = 6) {
				wine3.at<double>(i - 65, j) = traindata[i].M8;
			}
			if (j = 7) {
				wine3.at<double>(i - 65, j) = traindata[i].M9;
			}
			if (j = 8) {
				wine3.at<double>(i - 65, j) = traindata[i].M10;
			}
			if (j = 9) {
				wine3.at<double>(i - 65, j) = traindata[i].M11;
			}
			if (j = 10) {
				wine3.at<double>(i - 65, j) = traindata[i].M12;
			}
			if (j = 11) {
				wine3.at<double>(i - 65, j) = traindata[i].M13;
			}
			if (j = 12) {
				wine3.at<double>(i - 65, j) = traindata[i].M14;
			}
		}

	}

	calcCovarMatrix(wine3, cov3, mu3, CV_COVAR_NORMAL | CV_COVAR_ROWS);
	cov3 = cov3 / (wine3.rows - 1);
	cova = abs(determinant(cov));
	cova2 = abs(determinant(cov2));
	cova3 = abs(determinant(cov3));


	wm1 = wine1.clone();
	for (int i = 0; i < wine1.rows; i++) {

		for (int j = 0; j < wine1.cols; j++) {

			wm1.at<double>(i, j) = wine1.at<double>(i, j) - mu.at<double>(0, j);

		}

	}
	wm1t = wm1.t();
	wm2 = wine2.clone();
	for (int i = 0; i < wine2.rows; i++) {

		for (int j = 0; j < wine2.cols; j++) {

			wm2.at<double>(i, j) = wine2.at<double>(i, j) - mu2.at<double>(0, j);

		}

	}
	wm2t = wm2.t();

	wm3 = wine3.clone();
	for (int i = 0; i < wine3.rows; i++) {

		for (int j = 0; j < wine3.cols; j++) {

			wm3.at<double>(i, j) = wine3.at<double>(i, j) - mu3.at<double>(0, j);

		}

	}
	wm3t = wm3.t();

	covr1 = (Mat_<double>(20, 20) << 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768, 0.205891, 0.185302, 0.166772, 0.150095, 0.135085,
		0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768, 0.205891, 0.185302, 0.166772, 0.150095,
		0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768, 0.205891, 0.185302, 0.166772,
		0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768, 0.205891, 0.185302,
		0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768, 0.205891,
		0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768,
		0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187,
		0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243,
		0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811,
		0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678,
		0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742,
		0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467,
		0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297,
		0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441,
		0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049,
		0.205891, 0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561,
		0.185302, 0.205891, 0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729,
		0.166772, 0.185302, 0.205891, 0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81,
		0.150095, 0.166772, 0.185302, 0.205891, 0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9,
		0.135085, 0.150095, 0.166772, 0.185302, 0.205891, 0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1);

	covr2 = (Mat_<double>(20, 20) << 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906, 0.001953, 0.000977, 0.000488, 0.000244, 0.000122, 0.000061, 0.000031, 0.000015, 0.000008, 0.000004, 0.000002,
		0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906, 0.001953, 0.000977, 0.000488, 0.000244, 0.000122, 0.000061, 0.000031, 0.000015, 0.000008, 0.000004,
		0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906, 0.001953, 0.000977, 0.000488, 0.000244, 0.000122, 0.000061, 0.000031, 0.000015, 0.000008,
		0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906, 0.001953, 0.000977, 0.000488, 0.000244, 0.000122, 0.000061, 0.000031, 0.000015,
		0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906, 0.001953, 0.000977, 0.000488, 0.000244, 0.000122, 0.000061, 0.000031,
		0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906, 0.001953, 0.000977, 0.000488, 0.000244, 0.000122, 0.000061,
		0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906, 0.001953, 0.000977, 0.000488, 0.000244, 0.000122,
		0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906, 0.001953, 0.000977, 0.000488, 0.000244,
		0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906, 0.001953, 0.000977, 0.000488,
		0.001953, 0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906, 0.001953, 0.000977,
		0.000977, 0.001953, 0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906, 0.001953,
		0.000488, 0.000977, 0.001953, 0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813, 0.003906,
		0.000244, 0.000488, 0.000977, 0.001953, 0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.007813,
		0.000122, 0.000244, 0.000488, 0.000977, 0.001953, 0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625,
		0.000061, 0.000122, 0.000244, 0.000488, 0.000977, 0.001953, 0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625, 0.03125,
		0.000031, 0.000061, 0.000122, 0.000244, 0.000488, 0.000977, 0.001953, 0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125, 0.0625,
		0.000015, 0.000031, 0.000061, 0.000122, 0.000244, 0.000488, 0.000977, 0.001953, 0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25, 0.125,
		0.000008, 0.000015, 0.000031, 0.000061, 0.000122, 0.000244, 0.000488, 0.000977, 0.001953, 0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5, 0.25,
		0.000004, 0.000008, 0.000015, 0.000031, 0.000061, 0.000122, 0.000244, 0.000488, 0.000977, 0.001953, 0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1, 0.5,
		0.000002, 0.000004, 0.000008, 0.000015, 0.000031, 0.000061, 0.000122, 0.000244, 0.000488, 0.000977, 0.001953, 0.003906, 0.007813, 0.015625, 0.03125, 0.0625, 0.125, 0.25, 0.5, 1

		);
	covra1 = abs(determinant(covr1));
	covra2 = abs(determinant(covr2));
	invcov1 = cov.inv();
	invcov2 = cov2.inv();
	invcov3 = cov3.inv();
	invcovr1 = covr1.inv();
	invcovr2 = covr2.inv();

}
void winetester() {


	for (int i = 0; i < 89; i++) {

		for (int j = 0; j <13; j++) {
			winetest2.at<double>(i, j) = testdata[i].M2;
			if (j = 1) {
				winetest2.at<double>(i, j) = testdata[i].M3;
			}
			if (j = 2) {
				winetest2.at<double>(i, j) = testdata[i].M4;
			}
			if (j = 3) {
				winetest2.at<double>(i, j) = testdata[i].M5;
			}
			if (j = 4) {
				winetest2.at<double>(i, j) = testdata[i].M6;
			}
			if (j = 5) {
				winetest2.at<double>(i, j) = testdata[i].M7;
			}
			if (j = 6) {
				winetest2.at<double>(i, j) = testdata[i].M8;
			}
			if (j = 7) {
				winetest2.at<double>(i, j) = testdata[i].M9;
			}
			if (j = 8) {
				winetest2.at<double>(i, j) = testdata[i].M10;
			}
			if (j = 9) {
				winetest2.at<double>(i, j) = testdata[i].M11;
			}
			if (j = 10) {
				winetest2.at<double>(i, j) = testdata[i].M12;
			}
			if (j = 11) {
				winetest2.at<double>(i, j) = testdata[i].M13;
			}
			if (j = 12) {
				winetest2.at<double>(i, j) = testdata[i].M14;
			}
		}
	}
	wm1 = winetest2.clone();
	wm2 = winetest2.clone();
	wm3 = winetest2.clone();

	/*a = 0.5*log(cova)-log(R[0]);
	b = 0.5*log(cova2)-log(R[1]);
	c = 0.5*log(cova3)-log(R[2]);
	*/
	a = log(R[0]);
	b = log(R[1]);
	c = log(R[2]);

	for (int i = 0; i < winetest2.rows; i++) {

		for (int j = 0; j < winetest2.cols; j++) {

			wm1.at<double>(i, j) = winetest2.at<double>(i, j) - mu.at<double>(0, j);
			wm2.at<double>(i, j) = winetest2.at<double>(i, j) - mu2.at<double>(0, j);
			wm3.at<double>(i, j) = winetest2.at<double>(i, j) - mu3.at<double>(0, j);

		}

	}
	wm1t = wm1.t();
	wm2t = wm2.t();
	wm3t = wm3.t();
	double p1, p2, p3, max;

	for (int i = 0; i < 89; i++) {
		for (int j = 0; j < 13; j++) {
			//P[i] = 0.5*determinant(wm1t.at<double>(j, i)*invcov1*wm1.at<double>(i, j));
			P[i] = 0.5*determinant(-log(determinant(cov)) + (wm1t.at<double>(j, i)*invcov1*wm1.at<double>(i, j)));
			//O[i] = 0.5*determinant(wm2t.at<double>(j, i)*invcov2*wm2.at<double>(i, j));
			O[i] = 0.5*determinant(-log(determinant(cov2)) + (wm2t.at<double>(j, i)*invcov2*wm2.at<double>(i, j)));
			//Q[i] = 0.5*determinant(wm3t.at<double>(j, i)*invcov3*wm3.at<double>(i, j));
			Q[i] = 0.5*determinant(-log(determinant(cov3)) + (wm3t.at<double>(j, i)*invcov3*wm3.at<double>(i, j)));
		}
		p1 = -(P[i] + a);
		p2 = -(O[i] + b);
		p3 = -(Q[i] + c);
		max = p1 > p2 ? p1 : p2;
		max = max > p3 ? max : p3;
		if (max <= p1) {

			cout << 1 << "	   " << p1 << "		   " << p2 << "		   " << p3 << "		  " << max << endl;
			if (testdata[i].M1 == 1) {
				m++;
			}
		}
		else if (max <= p2) {
			cout << 2 << "	   " << p1 << "		   " << p2 << "		   " << p3 << "		  " << max << endl;
			if (testdata[i].M1 == 2) {
				m++;
			}
		}
		else {
			cout << 3 << "	   " << p1 << "		   " << p2 << "		   " << p3 << "		  " << max << endl;
			if (testdata[i].M1 == 3) {
				m++;
			}
		}
	}
}



void randomtest() {

	for (int i = 0; i < 100; i++) {

		for (int j = 0; j <20; j++) {
			rantest2.at<double>(i, j) = testdata2[i].N2;
			if (j = 1) {
				rantest2.at<double>(i, j) = testdata2[i].N3;
			}
			if (j = 2) {
				rantest2.at<double>(i, j) = testdata2[i].N4;
			}
			if (j = 3) {
				rantest2.at<double>(i, j) = testdata2[i].N5;
			}
			if (j = 4) {
				rantest2.at<double>(i, j) = testdata2[i].N6;
			}
			if (j = 5) {
				rantest2.at<double>(i, j) = testdata2[i].N7;
			}
			if (j = 6) {
				rantest2.at<double>(i, j) = testdata2[i].N8;
			}
			if (j = 7) {
				rantest2.at<double>(i, j) = testdata2[i].N9;
			}
			if (j = 8) {
				rantest2.at<double>(i, j) = testdata2[i].N10;
			}
			if (j = 9) {
				rantest2.at<double>(i, j) = testdata2[i].N11;
			}
			if (j = 10) {
				rantest2.at<double>(i, j) = testdata2[i].N12;
			}
			if (j = 11) {
				rantest2.at<double>(i, j) = testdata2[i].N13;
			}
			if (j = 12) {
				rantest2.at<double>(i, j) = testdata2[i].N14;
			}
			if (j = 13) {
				rantest2.at<double>(i, j) = testdata2[i].N15;
			}
			if (j = 14) {
				rantest2.at<double>(i, j) = testdata2[i].N16;
			}
			if (j = 15) {
				rantest2.at<double>(i, j) = testdata2[i].N17;
			}
			if (j = 16) {
				rantest2.at<double>(i, j) = testdata2[i].N18;
			}
			if (j = 17) {
				rantest2.at<double>(i, j) = testdata2[i].N19;
			}
			if (j = 18) {
				rantest2.at<double>(i, j) = testdata2[i].N20;
			}
			if (j = 19) {
				rantest2.at<double>(i, j) = testdata2[i].N21;
			}
		}
	}

	wm1 = rantest2.clone();
	wm2 = rantest2.clone();

	d = 0.5*log(covra1) - log(0.5);
	e = 0.5*log(covra2) - log(0.5);

	for (int i = 0; i < rantest2.rows; i++) {

		for (int j = 0; j < rantest2.cols; j++) {

			wm1.at<double>(i, j) = rantest2.at<double>(i, j);
			wm2.at<double>(i, j) = rantest2.at<double>(i, j);

		}

	}
	wm1t = wm1.t();
	wm2t = wm2.t();
	double p1, p2, max;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 20; j++) {
			p[i] = 0.5*determinant(wm1t.at<double>(j, i)*invcovr1*wm1.at<double>(i, j));
			q[i] = 0.5*determinant(wm2t.at<double>(j, i)*invcovr2*wm2.at<double>(i, j));
		}
		p1 = (p[i] + d);
		p2 = (q[i] + e);
		max = p1 > p2 ? p1 : p2;
		if (max <= p1) {

			cout << 1 << "	   " << p1 << "		   " << p2 << "		   " << max << endl;
			if (testdata2[i].N1 == 1) {
				n++;
			}
		}
		if (max <= p2) {
			cout << 2 << "	   " << p1 << "		   " << p2 << "		   " << max << endl;
			if (testdata2[i].N1 == 2) {
				n++;
			}
		}
	}
}
void train() {


	for (int i = 0; i < trainnum; i++) {
		winetrain.at<float>(i, 0) = traindata[i].M2;
		winetrain.at<float>(i, 1) = traindata[i].M3;
		winetrain.at<float>(i, 2) = traindata[i].M4;
		winetrain.at<float>(i, 3) = traindata[i].M5;
		winetrain.at<float>(i, 4) = traindata[i].M6;
		winetrain.at<float>(i, 5) = traindata[i].M7;
		winetrain.at<float>(i, 6) = traindata[i].M8;
		winetrain.at<float>(i, 7) = traindata[i].M9;
		winetrain.at<float>(i, 8) = traindata[i].M10;
		winetrain.at<float>(i, 9) = traindata[i].M11;
		winetrain.at<float>(i, 10) = traindata[i].M12;
		winetrain.at<float>(i, 11) = traindata[i].M13;
		winetrain.at<float>(i, 12) = traindata[i].M14;
	}


	
}
void rantraindata() {
	for (int i = 0; i < trainnum2; i++) {
		rantrain.at<float>(i, 0) = traindata2[i].N2;
		rantrain.at<float>(i, 1) = traindata2[i].N3;
		rantrain.at<float>(i, 2) = traindata2[i].N4;
		rantrain.at<float>(i, 3) = traindata2[i].N5;
		rantrain.at<float>(i, 4) = traindata2[i].N6;
		rantrain.at<float>(i, 5) = traindata2[i].N7;
		rantrain.at<float>(i, 6) = traindata2[i].N8;
		rantrain.at<float>(i, 7) = traindata2[i].N9;
		rantrain.at<float>(i, 8) = traindata2[i].N10;
		rantrain.at<float>(i, 9) = traindata2[i].N11;
		rantrain.at<float>(i, 10) = traindata2[i].N12;
		rantrain.at<float>(i, 11) = traindata2[i].N13;
		rantrain.at<float>(i, 12) = traindata2[i].N14;
		rantrain.at<float>(i, 13) = traindata2[i].N15;
		rantrain.at<float>(i, 14) = traindata2[i].N16;
		rantrain.at<float>(i, 15) = traindata2[i].N17;
		rantrain.at<float>(i, 16) = traindata2[i].N18;
		rantrain.at<float>(i, 17) = traindata2[i].N19;
		rantrain.at<float>(i, 18) = traindata2[i].N20;
		rantrain.at<float>(i, 19) = traindata2[i].N21;
	}
}
void test() {

	for (int i = 0; i < testnum; i++) {
		winetest.at<float>(i, 0) = testdata[i].M2;
		winetest.at<float>(i, 1) = testdata[i].M3;
		winetest.at<float>(i, 2) = testdata[i].M4;
		winetest.at<float>(i, 3) = testdata[i].M5;
		winetest.at<float>(i, 4) = testdata[i].M6;
		winetest.at<float>(i, 5) = testdata[i].M7;
		winetest.at<float>(i, 6) = testdata[i].M8;
		winetest.at<float>(i, 7) = testdata[i].M9;
		winetest.at<float>(i, 8) = testdata[i].M10;
		winetest.at<float>(i, 9) = testdata[i].M11;
		winetest.at<float>(i, 10) = testdata[i].M12;
		winetest.at<float>(i, 11) = testdata[i].M13;
		winetest.at<float>(i, 12) = testdata[i].M14;
	}

	
}
void rantestdata() {
	for (int i = 0; i < testnum2; i++) {
		rantest.at<float>(i, 0) = testdata2[i].N2;
		rantest.at<float>(i, 1) = testdata2[i].N3;
		rantest.at<float>(i, 2) = testdata2[i].N4;
		rantest.at<float>(i, 3) = testdata2[i].N5;
		rantest.at<float>(i, 4) = testdata2[i].N6;
		rantest.at<float>(i, 5) = testdata2[i].N7;
		rantest.at<float>(i, 6) = testdata2[i].N8;
		rantest.at<float>(i, 7) = testdata2[i].N9;
		rantest.at<float>(i, 8) = testdata2[i].N10;
		rantest.at<float>(i, 9) = testdata2[i].N11;
		rantest.at<float>(i, 10) = testdata2[i].N12;
		rantest.at<float>(i, 11) = testdata2[i].N13;
		rantest.at<float>(i, 12) = testdata2[i].N14;
		rantest.at<float>(i, 13) = testdata2[i].N15;
		rantest.at<float>(i, 14) = testdata2[i].N16;
		rantest.at<float>(i, 15) = testdata2[i].N17;
		rantest.at<float>(i, 16) = testdata2[i].N18;
		rantest.at<float>(i, 17) = testdata2[i].N19;
		rantest.at<float>(i, 18) = testdata2[i].N20;
		rantest.at<float>(i, 19) = testdata2[i].N21;
	}
}
void total() {

	for (int i = 0; i < testtotal; i++) {
		winetotal.at<float>(i, 0) = testdata[i].M2;
		winetotal.at<float>(i, 1) = testdata[i].M3;
		winetotal.at<float>(i, 2) = testdata[i].M4;
		winetotal.at<float>(i, 3) = testdata[i].M5;
		winetotal.at<float>(i, 4) = testdata[i].M6;
		winetotal.at<float>(i, 5) = testdata[i].M7;
		winetotal.at<float>(i, 6) = testdata[i].M8;
		winetotal.at<float>(i, 7) = testdata[i].M9;
		winetotal.at<float>(i, 8) = testdata[i].M10;
		winetotal.at<float>(i, 9) = testdata[i].M11;
		winetotal.at<float>(i, 10) = testdata[i].M12;
		winetotal.at<float>(i, 11) = testdata[i].M13;
		winetotal.at<float>(i, 12) = testdata[i].M14;
	}


}
void totalran() {

	for (int i = 0; i < testtotal2; i++) {
		rantotal.at<float>(i, 0) = testdata2[i].N2;
		rantotal.at<float>(i, 1) = testdata2[i].N3;
		rantotal.at<float>(i, 2) = testdata2[i].N4;
		rantotal.at<float>(i, 3) = testdata2[i].N5;
		rantotal.at<float>(i, 4) = testdata2[i].N6;
		rantotal.at<float>(i, 5) = testdata2[i].N7;
		rantotal.at<float>(i, 6) = testdata2[i].N8;
		rantotal.at<float>(i, 7) = testdata2[i].N9;
		rantotal.at<float>(i, 8) = testdata2[i].N10;
		rantotal.at<float>(i, 9) = testdata2[i].N11;
		rantotal.at<float>(i, 10) = testdata2[i].N12;
		rantotal.at<float>(i, 11) = testdata2[i].N13;
		rantotal.at<float>(i, 12) = testdata2[i].N14;
		rantotal.at<float>(i, 13) = testdata2[i].N15;
		rantotal.at<float>(i, 14) = testdata2[i].N16;
		rantotal.at<float>(i, 15) = testdata2[i].N17;
		rantotal.at<float>(i, 16) = testdata2[i].N18;
		rantotal.at<float>(i, 17) = testdata2[i].N19;
		rantotal.at<float>(i, 18) = testdata2[i].N20;
		rantotal.at<float>(i, 19) = testdata2[i].N21;
	}


}
int  main()
{
	int tester;
	cout << "Which data set you want to test?" << endl << "1. wine train" << endl << "2. wine test" << endl << "3.wine total data" << endl << "4.random data train" << endl<<"5.random data test" << endl << "6.random total data" << endl
		<< "7. try to calculate for wine and ran" << endl;
	cin >> tester;
	if (tester ==1) {
		DataRead(traindata, "train.data");
		int m = 0;
		int labels[89];
		train();
		for (int i = 0; i < trainnum; i++) {
			labels[i] = { traindata[i].M1 };
		}

		Mat labelsMat(trainnum, 1, CV_32S, labels);
		Ptr<NormalBayesClassifier> normalBayes = NormalBayesClassifier::create();
		Ptr<TrainData> tData = TrainData::create(winetrain, ROW_SAMPLE, labelsMat);
		normalBayes->train(tData);
		DataRead(testdata, "train.data");
		test();
		cout << endl << "For wine train data" << endl;
		cout << "Result"<< endl;
		for (int i = 0; i < testnum; i++) {
			Mat row = winetest.rowRange(i, i + 1).clone();
			//cout << row << endl;
			float respose = normalBayes->predict(row);

			if (respose == 1) {
				cout << "1" << endl;
				if (respose == testdata[i].M1) {
					m++;
				}
			}
			if (respose == 2) {
				cout << "2" << endl;
				if (respose == testdata[i].M1) {
					m++;
				}
			}
			else if (respose == 3) {
				cout << "3" << endl;
				if (respose == testdata[i].M1) {
					m++;
				}
			}
		}
		float rightrate, falserate;
		cout << endl;



		rightrate = (float)m / testnum;
		falserate = 1 - rightrate;
		cout << endl << endl << endl;
		cout << "Correct (%)：" << rightrate * 100 << "%" << " ，" << "False(%)：" << falserate * 100 << "%" << endl << endl;

	}
	
	if (tester ==2) {
		DataRead(traindata, "train.data");
		int m = 0;
		int labels[89];
		train();
		for (int i = 0; i < trainnum; i++) {
			labels[i] = { traindata[i].M1 };
		}

		Mat labelsMat(trainnum, 1, CV_32S, labels);
		Ptr<NormalBayesClassifier> normalBayes = NormalBayesClassifier::create();
		Ptr<TrainData> tData = TrainData::create(winetrain, ROW_SAMPLE, labelsMat);
		normalBayes->train(tData);
		DataRead(testdata, "test.data");
		test();
		cout << endl << "For wine test data" << endl;
		cout << "Result" << "    " << endl;
		for (int i = 0; i < testnum; i++) {
			Mat row = winetest.rowRange(i, i + 1).clone();
			//cout << row << endl;
			float respose = normalBayes->predict(row);

			if (respose == 1) {
				cout << "1" << endl;
				if (respose == testdata[i].M1) {
					m++;
				}
			}
			if (respose == 2) {
				cout << "2" << endl;
				if (respose == testdata[i].M1) {
					m++;
				}
			}
			else if (respose == 3) {
				cout << "3" << endl;
				if (respose == testdata[i].M1) {
					m++;
				}
			}
		}
		float rightrate, falserate;
		cout << endl;



		rightrate = (float)m / testnum;
		falserate = 1 - rightrate;
		cout << endl << endl << endl;
		cout << "Correct (%)：" << rightrate * 100 << "%" << " ，" << "False(%)：" << falserate * 100 << "%" << endl << endl;

	}
	if (tester == 3) {
		DataRead(traindata, "train.data");
		int m = 0;
		int labels[89];
		train();
		for (int i = 0; i < trainnum; i++) {
			labels[i] = { traindata[i].M1 };
		}

		Mat labelsMat(trainnum, 1, CV_32S, labels);
		Ptr<NormalBayesClassifier> normalBayes = NormalBayesClassifier::create();
		Ptr<TrainData> tData = TrainData::create(winetrain, ROW_SAMPLE, labelsMat);
		normalBayes->train(tData);
		DataReadt(testdata, "test_total.data");
		total();
		cout << endl << "For wine total data" << endl;
		cout << "Result" << "    " << endl;
		for (int i = 0; i < testtotal; i++) {
			Mat row = winetotal.rowRange(i, i+1 ).clone();
			//cout << row << endl;
			float respose = normalBayes->predict(row);

			if (respose == 1) {
				cout << "1" << endl;
				if (respose == testdata[i].M1) {
					m++;
				}
			}
			if (respose == 2) {
				cout << "2" << endl;
				if (respose == testdata[i].M1) {
					m++;
				}
			}
			else if (respose == 3) {
				cout << "3" << endl;
				if (respose == testdata[i].M1) {
					m++;
				}
			}
		}
		float rightrate, falserate;
		cout << endl;



		rightrate = (float)m / testtotal;
		falserate = 1 - rightrate;
		cout << endl << endl << endl;
		cout << "Correct (%)：" << rightrate * 100 << "%" << " ，" << "False(%)：" << falserate * 100 << "%" << endl << endl;
	}
	if (tester == 4) {
		DataReadr(traindata2, "rantrain.data");
		int m = 0;
		int labels[100];
		rantraindata();
		for (int i = 0; i < trainnum2; i++) {
			labels[i] = { traindata2[i].N1 };
		}

		/*labels[i] = { traindata2[i].N1 };
			cout << traindata2[i].N1 << endl;*/
		

		Mat labelsMat(trainnum2, 1, CV_32S, labels);
		Ptr<NormalBayesClassifier> normalBayes = NormalBayesClassifier::create();
		Ptr<TrainData> tData = TrainData::create(rantrain, ROW_SAMPLE, labelsMat);
		normalBayes->train(tData);
		DataReadr(testdata2, "rantrain.data");
		rantestdata();
		cout << endl << "For random train data" << endl;
		cout << "Result" << endl;
		for (int i = 0; i < testnum2; i++) {
			Mat row = rantest.rowRange(i, i + 1).clone();
			//cout << row << endl;
			float respose = normalBayes->predict(row);
			if (respose == 1) {
				cout << "1" << endl;
				if (respose == testdata2[i].N1) {
					m++;
				}
			}
			else if (respose == 2) {
				cout << "2" << endl;
				if (respose == testdata2[i].N1) {
					m++;
				}
			}
		}
			
		float rightrate, falserate;
		cout << endl;



		rightrate = (float)m / testnum2;
		falserate = 1 - rightrate;
		cout << endl << endl << endl;
		cout << "Correct (%)：" << rightrate * 100 << "%" << " ，" << "False(%)：" << falserate * 100 << "%" << endl << endl;

	}
	if (tester == 5) {
		DataReadr(traindata2, "rantrain.data");
		int m = 0;
		int labels[100];
		rantraindata();
		for (int i = 0; i < trainnum2; i++) {
			labels[i] = { traindata2[i].N1 };
		}

			/*labels[i] = { traindata2[i].N1 };
			cout << traindata2[i].N1 << endl;*/
		

		Mat labelsMat(trainnum2, 1, CV_32S, labels);
		Ptr<NormalBayesClassifier> normalBayes = NormalBayesClassifier::create();
		Ptr<TrainData> tData = TrainData::create(rantrain, ROW_SAMPLE, labelsMat);
		normalBayes->train(tData);
		DataReadr(testdata2, "rantest.data");
		rantestdata();
		cout << endl << "For random test data" << endl;
		cout << "Result"<<endl;
		for (int i = 0; i < testnum2; i++) {
			Mat row = rantest.rowRange(i, i + 1).clone();
			//cout << row << endl;
			float respose = normalBayes->predict(row);
			if (respose == 1) {
				cout << "1" << endl;
				if (respose == testdata2[i].N1) {
					m++;
				}
			}
			else if (respose == 2) {
				cout << "2" << endl;
				if (respose == testdata2[i].N1) {
					m++;
				}
			}
	
		}

		float rightrate, falserate;
		cout << endl;



		rightrate = (float)m / testnum2;
		falserate = 1 - rightrate;
		cout << endl << endl << endl;
		cout << "Correct (%)：" << rightrate * 100 << "%" << " ，" << "False(%)：" << falserate * 100 << "%" << endl << endl;
	

	}
	if (tester == 6) {
		DataReadr(traindata2, "rantrain.data");
		int m = 0;
		int labels[100];
		rantraindata();
		for (int i = 0; i < trainnum2; i++) {
			labels[i] = { traindata2[i].N1 };
		}
		Mat labelsMat(trainnum2, 1, CV_32S, labels);
		Ptr<NormalBayesClassifier> normalBayes = NormalBayesClassifier::create();
		Ptr<TrainData> tData = TrainData::create(rantrain, ROW_SAMPLE, labelsMat);
		normalBayes->train(tData);
		DataReadrt(testdata2, "totalran.data");
		totalran();
		cout <<endl<< "For total random data" << endl;
		cout << "Result" << endl;
		for (int i = 0; i < testtotal2; i++) {
			Mat row = rantotal.rowRange(i, i + 1).clone();
			float respose = normalBayes->predict(row);
			if (respose == 1) {
				cout << "1" << endl;
				if (respose == testdata2[i].N1) {
					m++;
				}
			}
			else if (respose == 2) {
				cout << "2" << endl;
				if (respose == testdata2[i].N1) {
					m++;
				}
			}

		}

		float rightrate, falserate;
		cout << endl;
		rightrate = (float)m / testtotal2;
		falserate = 1 - rightrate;
		cout << endl << endl << endl;
		cout << "Correct (%)：" << rightrate * 100 << "%" << " ，" << "False(%)：" << falserate * 100 << "%" << endl << endl;

	}
	else if (tester == 7) {
		float rightrate, falserate;
		cout << endl;
		cout << "For wine data" << endl;
		cout << "Result" << "    " << "Probability1" << "          " << "Probability2" << "          " << "Probability3" << "           " << "Maximum" << endl;
		DataRead(traindata, "train.data");
		Prior();
		cov_mean();
		DataRead(testdata, "test.data");
		winetester();
		rightrate = (float)m / 89;
		falserate = 1 - rightrate;
		cout << endl << endl << endl;

		cout << "Correct (%)：" << rightrate * 100 << "%" << " ，" << "False(%)：" << falserate * 100 << "%" << endl << endl;
		system("pause");
		DataReadr(traindata2, "rantrain.data");
		cov_mean();
		cout << "For random data" << endl;
		cout << "Result" << "    " << "Probability1" << "          " << "Probability2" << "           " << "Maximum" << endl;
		DataReadr(testdata2, "rantest.data");
		randomtest();
		rightrate = (float)n / 100;
		falserate = 1 - rightrate;
		cout << endl << endl << endl;
		cout << "Correct (%)：" << rightrate * 100 << "%" << " ，" << "False(%)：" << falserate * 100 << "%" << endl;

	}

	system("PAUSE");
	return 0;
}