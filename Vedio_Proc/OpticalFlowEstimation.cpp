#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int labelTargets(Mat &src, Mat &mask, int thresh = 10);

const int Max_Count = 20;

int main()
{
	const char *url = "C:\\Users\\Administrator\\Desktop\\C++_AI\\vtest.avi";

	VideoCapture  cap;
	Mat source, result, gray, lastGray;
	vector<Point2f> points[2], temp;
	vector<uchar> status;
	vector<float> err;

	cap.open(url);
	if (!cap.isOpened())
	{
		cout << "cannot open vedio" << endl;
		return 0;
	}

	for (;;)
	{
		cap >> source;
		if (source.empty())
			break;

		cvtColor(source, gray, COLOR_BGR2GRAY);

		if (points[0].size() < 10)
			goodFeaturesToTrack(gray, points[0], Max_Count, 0.01, 20);

		if (lastGray.empty())
			gray.copyTo(lastGray);

		calcOpticalFlowPyrLK(lastGray, gray, points[0], points[1], status, err);

		int counter = 0;
		for (int i = 0; i < points[1].size(); i++)
		{
			double dist = norm(points[1][i] - points[0][i]);
			if (status[i] && dist >= 2.0 && dist <= 20.0)
			{
				points[0][counter] = points[0][i];
				points[1][counter] = points[1][i];
				++counter;
			}
		}

		points[0].resize(counter);
		points[1].resize(counter);

		source.copyTo(result);
		for (int i = 0; i < points[1].size(); i++)
		{
			line(result, points[0][i], points[1][i], Scalar(0, 0, 0xff));
			circle(result,points[1][i],3, Scalar(0, 0xff,0));
		}

		swap(points[0], points[1]);
		swap(lastGray, gray);

		imshow("source image", source);
		imshow("detect result image", result);

		char key = waitKey(100);
		if (key == 27)
			break;
	}

	waitKey(0);
	return 0;
}

