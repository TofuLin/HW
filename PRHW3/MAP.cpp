#include <iostream>                              
#include <sstream>                               
#include <fstream>                                                                             ¡@                               
#include "MAP.h"      
#include<opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<math.h>
#include<stdio.h>
#include <opencv2/core/mat.hpp>
using namespace std;          
using namespace cv;
double R[3];                                     
int m=0,n=0;
vector<oridata> testdata;                 
vector<oridata> traindata;        
vector<oridata2> testdata2;
vector<oridata2> traindata2;
ifstream   file1;                   
Mat wine1(30, 13, CV_64F);
Mat wine2(35, 13, CV_64F);
Mat wine3(24, 13, CV_64F);
Mat winetest(89, 13, CV_64F);
Mat rantest(100, 20, CV_64F);
Mat cov,cov2,cov3, mu,mu2,mu3, covr1, covr2;
double cova, cova2, cova3, covra1, covra2;
Mat wm1, wm2, wm3, wm1t, wm2t, wm3t;
Mat mean = (Mat_<double>(20, 1) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
Mat invcov1, invcov2, invcov3, invcovr1, invcovr2;
double P[89],O[89],Q[89],p[100],q[100];
double a, b, c, d, e;

void DataRead(vector<oridata> &data, const char* fileName)   
{
	file1.open(fileName);                                        
	int s=89;
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
	oridata2 Ttrainrandom;
	for (int a = 0; a < s; a++)
	{
		file1 >> line;
		while (line.find(',') > 0 && line.find(',') < line.length())
		{
			line[line.find(',')] = ' ';
		}
		istringstream stream(line);
		stream >> Ttrainrandom.N1 >> Ttrainrandom.N2 >> Ttrainrandom.N3 >> Ttrainrandom.N4 >> Ttrainrandom.N5 >> Ttrainrandom.N6 >> Ttrainrandom.N7 >> Ttrainrandom.N8 >>
			Ttrainrandom.N9 >> Ttrainrandom.N10 >> Ttrainrandom.N11 >> Ttrainrandom.N12 >> Ttrainrandom.N13 >> Ttrainrandom.N14 >> Ttrainrandom.N15 >> Ttrainrandom.N16 >> 
			Ttrainrandom.N17 >> Ttrainrandom.N18 >> Ttrainrandom.N19 >> Ttrainrandom.N20>> Ttrainrandom.N21;
		data.push_back(Ttrainrandom);
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
				wine2.at<double>(i-30, j) = traindata[i].M3;
			}
			if (j = 2) {
				wine2.at<double>(i-30, j) = traindata[i].M4;
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
			wine3.at<double>(i-65, j) = traindata[i].M2;
			if (j = 1) {
				wine3.at<double>(i-65, j) = traindata[i].M3;
			}
			if (j = 2) {
				wine3.at<double>(i-65, j) = traindata[i].M4;
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
			
			wm1.at<double>(i,j) = wine1.at<double>(i, j)-mu.at<double>(0,j);
			
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

	covr1 = (Mat_<double>(20, 20) << 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768, 0.205891, 0.185302, 0.166772, 0.150095,0.135085,
		0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768, 0.205891, 0.185302, 0.166772, 0.150095,
		0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768, 0.205891, 0.185302, 0.166772,
		0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768, 0.205891, 0.185302,
		0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768, 0.205891,
		0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243, 0.254187, 0.228768,
		0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243,0.254187,
		0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811, 0.28243,
		0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 0.313811,
		0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742, 0.348678, 
		0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467, 0.38742,
		0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441, 0.478297, 0.430467,
		0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049, 0.531441,0.478297,
		0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049,0.531441,
		0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561, 0.59049,
		0.205891, 0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729, 0.6561,
		0.185302, 0.205891, 0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81, 0.729,
		0.166772, 0.185302, 0.205891, 0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9, 0.81,
		0.150095, 0.166772, 0.185302, 0.205891, 0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9, 1, 0.9,
		0.135085, 0.150095, 0.166772, 0.185302, 0.205891, 0.228768, 0.254187, 0.28243, 0.313811, 0.348678, 0.38742, 0.430467, 0.478297, 0.531441, 0.59049, 0.6561, 0.729, 0.81, 0.9,1);

	covr2 = (Mat_<double>(20, 20) <<  1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,0.001953,0.000977,0.000488,0.000244,0.000122,0.000061,0.000031,0.000015,0.000008,0.000004,0.000002,
		0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,0.001953,0.000977,0.000488,0.000244,0.000122,0.000061,0.000031,0.000015,0.000008,0.000004,
		0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,0.001953,0.000977,0.000488,0.000244,0.000122,0.000061,0.000031,0.000015,0.000008,
		0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,0.001953,0.000977,0.000488,0.000244,0.000122,0.000061,0.000031,0.000015,
		0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,0.001953,0.000977,0.000488,0.000244,0.000122,0.000061,0.000031,
		0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,0.001953,0.000977,0.000488,0.000244,0.000122,0.000061,
		0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,0.001953,0.000977,0.000488,0.000244,0.000122,
		0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,0.001953,0.000977,0.000488,0.000244,
		0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,0.001953,0.000977,0.000488,
		0.001953,0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,0.001953,0.000977,
		0.000977,0.001953,0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,0.001953,
		0.000488,0.000977,0.001953,0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,0.003906,
		0.000244,0.000488,0.000977,0.001953,0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,0.007813,
		0.000122,0.000244,0.000488,0.000977,0.001953,0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,0.015625,
		0.000061,0.000122,0.000244,0.000488,0.000977,0.001953,0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,0.03125,
		0.000031,0.000061,0.000122,0.000244,0.000488,0.000977,0.001953,0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,0.0625,
		0.000015,0.000031,0.000061,0.000122,0.000244,0.000488,0.000977,0.001953,0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,0.125,
		0.000008,0.000015,0.000031,0.000061,0.000122,0.000244,0.000488,0.000977,0.001953,0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,0.25,
		0.000004,0.000008,0.000015,0.000031,0.000061,0.000122,0.000244,0.000488,0.000977,0.001953,0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1,0.5,
		0.000002,0.000004,0.000008,0.000015,0.000031,0.000061,0.000122,0.000244,0.000488,0.000977,0.001953,0.003906,0.007813,0.015625,0.03125,0.0625,0.125,0.25,0.5,1

	);
	covra1 = abs(determinant(covr1));
	covra2= abs(determinant(covr2));
	invcov1 = cov.inv();
	invcov2 = cov2.inv();
	invcov3 = cov3.inv();
	invcovr1 = covr1.inv();
	invcovr2 = covr2.inv();

}
void test() {


for (int i = 0; i < 89; i++) {

	for (int j = 0; j <13; j++) {
		winetest.at<double>(i, j) = testdata[i].M2;
		if (j = 1) {
			winetest.at<double>(i, j) = testdata[i].M3;
		}
		if (j = 2) {
			winetest.at<double>(i, j) = testdata[i].M4;
		}
		if (j = 3) {
			winetest.at<double>(i, j) = testdata[i].M5;
		}
		if (j = 4) {
			winetest.at<double>(i, j) = testdata[i].M6;
		}
		if (j = 5) {
			winetest.at<double>(i, j) = testdata[i].M7;
		}
		if (j = 6) {
			winetest.at<double>(i, j) = testdata[i].M8;
		}
		if (j = 7) {
			winetest.at<double>(i, j) = testdata[i].M9;
		}
		if (j = 8) {
			winetest.at<double>(i, j) = testdata[i].M10;
		}
		if (j = 9) {
			winetest.at<double>(i, j) = testdata[i].M11;
		}
		if (j = 10) {
			winetest.at<double>(i, j) = testdata[i].M12;
		}
		if (j = 11) {
			winetest.at<double>(i, j) = testdata[i].M13;
		}
		if (j = 12) {
			winetest.at<double>(i, j) = testdata[i].M14;
		}
	}
}
wm1  =winetest.clone();
wm2 = winetest.clone();
wm3 = winetest.clone();

/*a = 0.5*log(cova)-log(R[0]);
b = 0.5*log(cova2)-log(R[1]);
c = 0.5*log(cova3)-log(R[2]);
*/
a = log(R[0]);
b = log(R[1]);
c = log(R[2]);

for (int i = 0; i < winetest.rows; i++) {

	for (int j = 0; j < winetest.cols; j++) {

		wm1.at<double>(i, j) = winetest.at<double>(i, j) - mu.at<double>(0, j);
		wm2.at<double>(i, j) = winetest.at<double>(i, j) - mu2.at<double>(0, j);
		wm3.at<double>(i, j) = winetest.at<double>(i, j) - mu3.at<double>(0, j);

	}

}
wm1t = wm1.t();
wm2t = wm2.t();
wm3t = wm3.t();
double p1, p2, p3, max;

for (int i = 0; i < 89; i++) {
	for (int j = 0; j < 13; j++) {
		//P[i] = 0.5*determinant(wm1t.at<double>(j, i)*invcov1*wm1.at<double>(i, j));
		P[i] = 0.5*determinant(-log(determinant(cov))+ (wm1t.at<double>(j, i)*invcov1*wm1.at<double>(i, j)));
		//O[i] = 0.5*determinant(wm2t.at<double>(j, i)*invcov2*wm2.at<double>(i, j));
		O[i] = 0.5*determinant(-log(determinant(cov2)) + (wm2t.at<double>(j, i)*invcov2*wm2.at<double>(i, j)));
		//Q[i] = 0.5*determinant(wm3t.at<double>(j, i)*invcov3*wm3.at<double>(i, j));
		Q[i] = 0.5*determinant(-log(determinant(cov3)) + (wm3t.at<double>(j, i)*invcov3*wm3.at<double>(i, j)));
		}
	p1 =-( P[i] + a);
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
		rantest.at<double>(i, j) = testdata2[i].N2;
		if (j = 1) {
			rantest.at<double>(i, j) = testdata2[i].N3;
		}
		if (j = 2) {
			rantest.at<double>(i, j) = testdata2[i].N4;
		}
		if (j = 3) {
			rantest.at<double>(i, j) = testdata2[i].N5;
		}
		if (j = 4) {
			rantest.at<double>(i, j) = testdata2[i].N6;
		}
		if (j = 5) {
			rantest.at<double>(i, j) = testdata2[i].N7;
		}
		if (j = 6) {
			rantest.at<double>(i, j) = testdata2[i].N8;
		}
		if (j = 7) {
			rantest.at<double>(i, j) = testdata2[i].N9;
		}
		if (j = 8) {
			rantest.at<double>(i, j) = testdata2[i].N10;
		}
		if (j = 9) {
			rantest.at<double>(i, j) = testdata2[i].N11;
		}
		if (j = 10) {
			rantest.at<double>(i, j) = testdata2[i].N12;
		}
		if (j = 11) {
			rantest.at<double>(i, j) = testdata2[i].N13;
		}
		if (j = 12) {
			rantest.at<double>(i, j) = testdata2[i].N14;
		}
		if (j = 13) {
			rantest.at<double>(i, j) = testdata2[i].N15;
		}
		if (j = 14) {
			rantest.at<double>(i, j) = testdata2[i].N16;
		}
		if (j = 15) {
			rantest.at<double>(i, j) = testdata2[i].N17;
		}
		if (j = 16) {
			rantest.at<double>(i, j) = testdata2[i].N18;
		}
		if (j = 17) {
			rantest.at<double>(i, j) = testdata2[i].N19;
		}
		if (j = 18) {
			rantest.at<double>(i, j) = testdata2[i].N20;
		}
		if (j = 19) {
			rantest.at<double>(i, j) = testdata2[i].N21;
		}
	}
}

	wm1 = rantest.clone();
	wm2 = rantest.clone();

	d = 0.5*log(covra1) - log(0.5);
	e = 0.5*log(covra2) - log(0.5);

	for (int i = 0; i < rantest.rows; i++) {

		for (int j = 0; j < rantest.cols; j++) {

			wm1.at<double>(i, j) = rantest.at<double>(i, j);
			wm2.at<double>(i, j) = rantest.at<double>(i, j);

		}

	}
	wm1t = wm1.t();
	wm2t = wm2.t();
	double p1, p2,  max;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 20; j++) {
			p[i] = 0.5*determinant(wm1t.at<double>(j, i)*invcovr1*wm1.at<double>(i, j));
			q[i] = 0.5*determinant(wm2t.at<double>(j, i)*invcovr2*wm2.at<double>(i, j));
		}
		p1 = (p[i] + d);
		p2 = (q[i] + e);
		max = p1 > p2 ? p1 : p2;
		if (max <= p1) {

			cout << 1 << "	   " << p1 << "		   " << p2 << "		   "  << max << endl;
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

int  main()
{
	double rightrate, falserate;
	cout << endl;
	cout << "For wine data" << endl;
	cout << "Result" << "    " << "Probability1" << "          " << "Probability2" << "          " << "Probability3" << "           " << "Maximum" << endl;
	DataRead(traindata, "train.data");
	Prior();
	cov_mean();

	DataRead(testdata, "train.data");
	test();
	rightrate = (double)m / 89;
	falserate = 1 - rightrate;
	cout << endl << endl << endl;
	cout << "Correct (%)¡G" << rightrate * 100 << "%" << " ¡A" << "False(%)¡G" << falserate * 100 << "%" << endl<<endl;
	
	DataReadr(traindata2,"rantrain.data");
	cov_mean();
	cout << "For random data" << endl;
	cout << "Result" << "    " << "Probability1" << "          " << "Probability2"  << "           " << "Maximum" << endl;
	DataReadr(testdata2, "rantest.data");
	randomtest();
	rightrate = (double)n / 100;
	falserate = 1 - rightrate;
	cout << endl << endl << endl;
	cout << "Correct (%)¡G" << rightrate * 100 << "%" << " ¡A" << "False(%)¡G" << falserate * 100 << "%" << endl;

	system("PAUSE");
}