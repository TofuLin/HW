#pragma once
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <cv.h>
#include <highgui.h>
#include <algorithm>
#include <opencv2/highgui/highgui.hpp>
#define M_PI   3.14159265358979323846264338327950288
using namespace std;
using namespace cv;

Mat image;
typedef vector<Vec3b> row;
typedef vector<row> mat;
mat in, tmp, output;
int w, h;
double pi = M_PI;
double kernel[10][10] = { 0 };
double mins=256;
void test()
{
	double n = 5;
	double mid = floor((n + 1) / 2);
	double sigma = 1.0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
		{
			double ttt = ((i - mid)*(i - mid) + (j - mid)*(j - mid)) / (2 * sigma*sigma);
			double t = exp(-(ttt));
			double  a = t / (2 * pi*sigma*sigma);
			if (a<mins)
				mins = a;
			kernel[i][j] = a;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			kernel[i][j] /= mins;
			kernel[i][j] = ceil(kernel[i][j]);
		}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
		}
	}
}
Vec3b guessbour(int x, int y) {
	double sum0 = 0, sum1 = 0, sum2 = 0;
	for (int i = 0; i<5; i++)
		for (int j = 0; j<5; j++) {
			Vec3b  tt = tmp[x - 2 + i][y - 2 + j];
			sum0 += tt[0] * kernel[i + 1][j + 1];
			sum1 += tt[1] * kernel[i + 1][j + 1];
			sum2 += tt[2] * kernel[i + 1][j + 1];
		}
	Vec3b tt;
	tt[0] = sum0*mins;
	tt[1] = sum1*mins;
	tt[2] = sum2*mins;
	return tt;
}
void smooth(int iterations)
{
	tmp.resize(h), output.resize(h);
	for (int i = 0; i<h; i++) {
		tmp[i].resize(w), output[i].resize(w);
		for (int j = 0; j<w; j++) {
			output[i][j] = tmp[i][j] = in[i][j];
		}
	}
	while (iterations--) {
		for (int i = 2; i<h - 2; i++)
			for (int j = 2; j<w - 2; j++)
				output[i][j] = guessbour(i, j);
		for (int i = 0; i<h; i++)
			for (int j = 0; j<w; j++) {
				tmp[i][j] = output[i][j];
			}
	}


}
void solve()
{
	h = image.rows, w = image.cols;
	in.resize(h);
	for (int i = 0; i<h; i++)
	{
		in[i].resize(w);
		for (int j = 0; j<w; j++)
		{
			in[i][j] = image.at<Vec3b>(i, j);
		}
	}
	smooth(1);
	Mat res;
	res.create(h, w, image.type());
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			res.at<Vec3b>(i, j) = output[i][j];
		}
	}
	namedWindow("windowmyself");
	imshow("windowmyself", res);
}
/*void blur() {
	int width = image.row;
	int height = image.cols;
	Mat dst;
	for (int j = 2; j < width - 2; j++) {
		for (int i = 2; i < width - 2; i++) {
			int sum = 0;
			int index = 0;
			for (int m = j - 2; m < j + 3; m++) {
				for (int n = i - 2; n < i + 3; n++) {
					sum += (m*width + n)*index++;
				}
			}
			if (sum > 255)
				sum = 255;
		}
	}
	namedWindow("windowmyself");
	imshow("windowmyself", dst);
}*/
void opencv()
{
	namedWindow("windoworiginal", WINDOW_AUTOSIZE);
	imshow("windoworiginal", image);
	Mat out;
	GaussianBlur(image, out, Size(5, 5), 0, 0);
	namedWindow("windowopencv5", WINDOW_AUTOSIZE);
	imshow("windowopencv5", out);
}
void opencv2()
{
	Mat out2;
	GaussianBlur(image, out2, Size(7, 7), 0, 0);
	namedWindow("windowopencv7", WINDOW_AUTOSIZE);
	imshow("windowopencv7", out2);
}
void opencv3()
{
	Mat out3;
	GaussianBlur(image, out3, Size(9, 9), 0, 0);
	namedWindow("windowopencv9", WINDOW_AUTOSIZE);
	imshow("windowopencv9", out3);
}

