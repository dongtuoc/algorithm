#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;

using namespace cv;

int main()
{
	Mat img, gray;

	img = imread("C:\\Users\\86132\\Desktop\\data\\right14.jpg");
	
	//ת��Ϊ�Ҷ�ͼ  Harris�ǵ���ԭ��Ϊ�ԻҶ���Ϣ���д���
	cvtColor(img, gray, COLOR_BGR2GRAY);

	Mat HarrisRes;
	cornerHarris(gray, HarrisRes, 2, 3, 0.04);
	//�õ�����һ�鱻��⵽�Ľǵ�ĻҶ�ֵ����ϣ�ֵ��С��ֱ����ʾ�����޷��ֱ�

	//��ȡharris�ǵ��е����ֵ����Сֵ  �Ҷ�ֵ
	double min_tmp, max_tmp;
	minMaxLoc(HarrisRes, &min_tmp, &max_tmp);

	//��ֵȡ���ֵ��0.03 ����ֵ
	Mat shredImg, normalImage;
	threshold(HarrisRes, shredImg, max_tmp *0.03, 255, CV_THRESH_BINARY);
	imshow("��ֵ��", shredImg);
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

	imshow("ԭͼ+�ǵ�", img);

	waitKey(0);
	return 0;
}