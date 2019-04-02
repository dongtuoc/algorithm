#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int labelTargets(Mat &src, Mat &mask, int thresh)
{
	Mat seg = mask.clone();
	vector<vector<Point>> cnts;

	findContours(seg, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	float area;
	Rect rect;
	int count = 0;
	string strCount;
	for (int i = cnts.size() - 1; i >= 0; --i)
	{
		vector<Point> c = cnts[i];
		area = contourArea(c);
		if (area < thresh)
			continue;

		count++;

		rect = boundingRect(c);
		rectangle(src, rect, Scalar(0, 0, 0xff, 1));

		cout << "area:" <<i<<" : "<< area << "\n";
		cout << "Position:" <<i<< Point(rect.x, rect.y) << "\n";

		stringstream ss;

		ss << count;
		ss >> strCount;
		putText(src, strCount, Point(rect.x, rect.y), FONT_HERSHEY_PLAIN, 0.5, Scalar(0, 0XFF, 0));
	}
	return count;
}
int main()
{
	const char *url = "C:\\Users\\Administrator\\Desktop\\C++_AI\\vtest.avi";

	VideoCapture  cap;
	Mat source, image, foreGround, backGround, fgMask;

	Ptr<BackgroundSubtractor> pBgModel = createBackgroundSubtractorMOG2().dynamicCast<BackgroundSubtractor>();

	cap.open(url);
	if (!cap.isOpened())
		cout << "cannot open video" << endl;

	for (;;)
	{
		cap >> source;
		if (source.empty())
			break;

		resize(source, image, Size(source.cols / 2, source.rows / 2), INTER_LINEAR);
		if (foreGround.empty())
		{
			foreGround.create(image.size(), image.type());
		}

		pBgModel->apply(image, fgMask);//get foregroung mask

		threshold(fgMask, fgMask, 30, 255, THRESH_BINARY);

		foreGround = Scalar::all(0);
		image.copyTo(foreGround, fgMask);

		int nTargets = labelTargets(image, fgMask,10);

		cout << "taegrts num is " << nTargets <<endl;

		pBgModel->getBackgroundImage(backGround);

		imshow("SOURCE", image);
		imshow("BackGround", backGround);
		imshow("Foregroung", foreGround);
		imshow("Foreground Maks", fgMask);// Binary Values

		char key = waitKey(100);
		if (key == 27)
			break;
	}

	waitKey(0);
	return 0;
}

