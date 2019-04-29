#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("C:\\Users\\Administrator\\Desktop\\C++_AI\\riceblurred.png");
	imshow("source image", src);

	/* color space transform: BGR转换为灰度图 */
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);
	
	/*大津算法阈值化,将灰度图转换为二值图像*/
	Mat bw3,bw_otsu;
	double rt;
	//rt = threshold(gray, bw3, 0, 255, THRESH_TRIANGLE);
	//cout << rt << endl;
	rt = threshold(gray, bw_otsu, 0, 255, THRESH_OTSU);
	cout << rt << endl;
	//imshow("triangle", bw3);
	imshow("otsu", bw_otsu);

	//形态学去除噪声 开运算或者闭运算去除噪声
	//shape:MORPH_CROSS 十字型 
	Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
	morphologyEx(bw_otsu, bw_otsu, MORPH_OPEN, element);//开运算
	//morphologyEx(bw_otsu, bw_otsu, MORPH_CLOSE, element);//闭运算
	imshow("after_noise", bw_otsu);

	//图像分割
	Mat seg = bw_otsu.clone();
	vector<vector<Point>> cnts; //二维vecotr的一系列点
	findContours(seg, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//RETR_EXTERNAL 只检测外轮廓 CHAIN_APPROX_SIMPLE存储横纵对角线坐标信息

	double area = 0;
	int count = 0;
	vector<double> lenth;
	vector<double> eareeee;
	double ermsum = 0;

	for (int i = cnts.size() - 1; i >= 0; --i)
	{
		vector<Point> c = cnts[i];

		double area = contourArea(c);//计算面积 使用Green Formula 格林公式计算
		if (area < 10) 
			continue;

		double len = arcLength(c, 0);
		cout << "lenth of contour: " << len << "\n";
		
		lenth.push_back(len);
		ermsum += area;
		eareeee.push_back(area);

		++count;//统计米粒数量
		cout << "Rice[" << i <<"]"<< " area is:" << area << "\n";
		Rect rect = boundingRect(c); //绘制包围矩形,标记标号
		cout << "Rect Left-Up Point" << rect.tl() << "Rect Right-Down Point" << rect.br() << "\n";

		Scalar color(255, 255, 0);
		rectangle(bw_otsu, rect.tl(), rect.br(), color, 1, 1, 0);
		rectangle(src, rect.tl(), rect.br(), color, 1, 1, 0);

		stringstream ss;
		String strcount;
		ss << count;
		ss >> strcount;

		putText(bw_otsu, strcount, Point(rect.x, rect.y), FONT_HERSHEY_PLAIN, 0.5, Scalar(0, 0xff, 0));
		putText(src, strcount, Point(rect.x, rect.y), FONT_HERSHEY_PLAIN, 0.5, Scalar(0, 0xff, 0));
	}

	imshow("Source Image With Rect", src);
	imshow("Otsu Image With Rect", bw_otsu);
	cout << "Rice Sum：" << count << "\n";

	double sum = 0;
	double accum = 0;
	double earsss = 0;
	double meaneare = ermsum / count;
	cout << "Mean of Rice Area：" << meaneare << "\n";

	for_each(eareeee.begin(), eareeee.end(), [&](const double p) {earsss += (p - meaneare)*(p - meaneare); });
	double earedev = sqrt((earsss / eareeee.size() - 1));
	cout << "RSME of Rice area：" << earedev << "\n";

	for (vector<double>::iterator it = lenth.begin(); it != lenth.end(); ++it)
	{
		sum += *it;
	}
	double mean = sum / lenth.size();
	cout << "Mean of Rice Lenth：" << mean << "\n";

	for_each(lenth.begin(), lenth.end(), [&](const double p) {accum += (p - mean)*(p - mean); });

	double dev = sqrt((accum / lenth.size() - 1));
	cout << "RSME of Rice Lenth：" << dev << "\n";

	waitKey(0);
	return 0;
}