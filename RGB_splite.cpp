#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("C:\\Users\\Administrator\\Desktop\\C++_AI\\butterfly.jpg",1);
	Mat img;
	pyrDown(src,img);
	imshow("source image",img);

	vector<Mat> RGB,mat_with_twozeros;
	split(img, RGB);

	Mat blank_zeros = Mat::zeros(img.size(), CV_8UC1);

	mat_with_twozeros.push_back(RGB[0]);
	mat_with_twozeros.push_back(blank_zeros);
	mat_with_twozeros.push_back(blank_zeros);
	Mat blue;
	merge(mat_with_twozeros, blue);
	imshow("blue", blue);

	mat_with_twozeros.clear();
	mat_with_twozeros.push_back(blank_zeros);
	mat_with_twozeros.push_back(RGB[1]);
	mat_with_twozeros.push_back(blank_zeros);
	Mat green;
	merge(mat_with_twozeros, green);
	imshow("green", green);

	mat_with_twozeros.clear();
	mat_with_twozeros.push_back(blank_zeros);
	mat_with_twozeros.push_back(blank_zeros);
	mat_with_twozeros.push_back(RGB[2]);
	Mat red;
	merge(mat_with_twozeros, red);
	imshow("red", red);

	waitKey(0);
	return 0;
}