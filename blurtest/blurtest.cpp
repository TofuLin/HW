#include "blurtest.h"


int main()
{
	double elapsed;
	double t0 = (double)getTickCount();
	image = imread("test.png");
	if (!image.data) {
		cout << "no image data" << endl;
	}

	test();
	elapsed = ((double)getTickCount() - t0) / getTickFrequency();
	std::cout << "loding image: " << elapsed<<endl;
	double t1 = (double)getTickCount();
	solve();
	elapsed = ((double)getTickCount() - t1) / getTickFrequency();
	std::cout <<"my way: "<< elapsed << endl;
	double t2 = (double)getTickCount();
	opencv();
	elapsed = ((double)getTickCount() - t2) / getTickFrequency();
	std::cout << "opencv with 5,5: " << elapsed << endl;
	double t3 = (double)getTickCount();
	opencv2();
	elapsed = ((double)getTickCount() - t3) / getTickFrequency();
	std::cout <<"opencv with 7,7: "<< elapsed << endl;
	double t4 = (double)getTickCount();
	opencv3();
	elapsed = ((double)getTickCount() - t4) / getTickFrequency();
	std::cout << "opencv with 9,9: " << elapsed << endl;

	waitKey(0);

	return 0;
}