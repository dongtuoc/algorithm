#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;

using namespace cv;

int main()
{
	Mat img, gray;

	img = imread("C:\\Users\\86132\\Desktop\\data\\right14.jpg");
	
	//转换为灰度图  Harris角点检测原理为对灰度信息进行处理
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat HarrisRes;
	cornerHarris(gray, HarrisRes, 2, 3, 0.04);
	//得到的是一组被检测到的角点的灰度值的组合，值很小，直接显示肉眼无法分辨

	//获取harris角点中的最大值和最小值  灰度值
	double min_tmp, max_tmp;
	minMaxLoc(HarrisRes, &min_tmp, &max_tmp);

	//阈值取最大值的0.03 经验值
	Mat shredImg, normalImage;
	threshold(HarrisRes, shredImg, max_tmp *0.03, 255, CV_THRESH_BINARY);
	imshow("阈值化", shredImg);
	printf("%d-%d\n", shredImg.cols, shredImg.rows);

	vector<Point> corner;
	normalize(shredImg, normalImage, 0, 255, 32);
	
	for (int y = 0; y < normalImage.rows; ++ y){
		for (int x = 0; x < normalImage.cols; ++x) {
			if (normalImage.at<float>(y,x) > 15) {
				corner.push_back(Point(x, y));
			}
		}
	}

	for (vector<Point>::iterator it = corner.begin(); it != corner.end(); ++it){
		circle(img, *it, 3, Scalar(255, 0, 0), 1);
	}

	imshow("原图+角点", img);

	waitKey(0);
	return 0;
}