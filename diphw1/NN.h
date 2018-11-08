#pragma once
#include <iostream>
#include <atlimage.h>
using namespace std;
void NN() {
	int x, y, x2, y2;
	CImage img1; 
	img1.Load("1.jpg"); // you can modify path here 
	int height1 = img1.GetHeight(); 
	int width1 = img1.GetWidth();
	double scale_h = 10, scale_w = 10;
	int height2 = (int)(height1*scale_h + 0.5);
	int width2 = (int)(width1*scale_w + 0.5);
	CImage img2; 
	img2.Create(width2, height2,24); 
	cout << "hold on...\n";
	DWORD color;
	for (y2 = 0; y2<height2; y2++) {
		for (x2 = 0; x2<width2; x2++) {
			x = (int)(x2 / scale_w);
			y = (int)(y2 / scale_h);
			color = img1.GetPixel(x, y);
			img2.SetPixel(x2, y2, color);
		}
	}
	img2.Save("NN.jpg");//and here
}