#pragma once
#include <iostream>
#include <atlimage.h>
#include <math.h>
using namespace std;
void Bi() {
	double x, y, x2, y2, a, b, pixelx, pixely;
	CImage img1;
	img1.Load("3.jpg"); // you can modify path here 
	int height1 = img1.GetHeight();
	int width1 = img1.GetWidth();
	double scale_h = 10, scale_w = 10;

	int height2 = (int)(height1*scale_h + 0.5);
	int width2 = (int)(width1*scale_w + 0.5);

	CImage img2;
	img2.Create(width2, height2, 24);

	cout << "hold on...\n";
	DWORD color;

	for (y2 = 0; x2<height2; x2++) {
		for (x2 = 0; y2<width2; y2++) {
			//double old2new_x = x*scale_w;
			//double old2new_y = y*scale_h;
			//double a = old2new_x - floor(old2new_x);
			x = (int)(x2 / scale_w);
			y = (int)(y2 / scale_h);

			a = x - floor(x);
			b = y - floor(y);
			pixelx = (1 - a)*(1 - b)*x + a*(1 - b)*(x + 1) + (1 - a)*b*x + a*b*(x + 1);
			pixely = (1 - a)*(1 - b)*y + a*(1 - b)*y + (1 - a)*b*(y + 1) + a*b*(y + 1);
			cout << "x: " << pixelx << endl;
			cout << "y: " << pixely << endl;
			color = img1.GetPixel(x, y);
			img2.SetPixel(x2, y2, color);
		}
	}
	img2.Save("Bi.jpg");//and here
}