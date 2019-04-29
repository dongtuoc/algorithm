#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	Mat src = imread("C:\\Users\\Administrator\\Desktop\\C++_AI\\riceblurred.png");
	imshow("source image", src);

	/* color space transform: BGRת��Ϊ�Ҷ�ͼ */
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	imshow("gray", gray);
	
	/*����㷨��ֵ��,���Ҷ�ͼת��Ϊ��ֵͼ��*/
	Mat bw3,bw_otsu;
	double rt;
	//rt = threshold(gray, bw3, 0, 255, THRESH_TRIANGLE);
	//cout << rt << endl;
	rt = threshold(gray, bw_otsu, 0, 255, THRESH_OTSU);
	cout << rt << endl;
	//imshow("triangle", bw3);
	imshow("otsu", bw_otsu);

	//��̬ѧȥ������ ��������߱�����ȥ������
	//shape:MORPH_CROSS ʮ���� 
	Mat element = getStructuringElement(MORPH_CROSS, Size(3, 3));
	morphologyEx(bw_otsu, bw_otsu, MORPH_OPEN, element);//������
	//morphologyEx(bw_otsu, bw_otsu, MORPH_CLOSE, element);//������
	imshow("after_noise", bw_otsu);

	//ͼ��ָ�
	Mat seg = bw_otsu.clone();
	vector<vector<Point>> cnts; //��άvecotr��һϵ�е�
	findContours(seg, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);//RETR_EXTERNAL ֻ��������� CHAIN_APPROX_SIMPLE�洢���ݶԽ���������Ϣ

	double area = 0;
	int count = 0;
	vector<double> lenth;
	vector<double> eareeee;
	double ermsum = 0;

	for (int i = cnts.size() - 1; i >= 0; --i)
	{
		vector<Point> c = cnts[i];

		double area = contourArea(c);//������� ʹ��Green Formula ���ֹ�ʽ����
		if (area < 10) 
			continue;

		double len = arcLength(c, 0);
		cout << "lenth of contour: " << len << "\n";
		
		lenth.push_back(len);
		ermsum += area;
		eareeee.push_back(area);

		++count;//ͳ����������
		cout << "Rice[" << i <<"]"<< " area is:" << area << "\n";
		Rect rect = boundingRect(c); //���ư�Χ����,��Ǳ��
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
	cout << "Rice Sum��" << count << "\n";

	double sum = 0;
	double accum = 0;
	double earsss = 0;
	double meaneare = ermsum / count;
	cout << "Mean of Rice Area��" << meaneare << "\n";

	for_each(eareeee.begin(), eareeee.end(), [&](const double p) {earsss += (p - meaneare)*(p - meaneare); });
	double earedev = sqrt((earsss / eareeee.size() - 1));
	cout << "RSME of Rice area��" << earedev << "\n";

	for (vector<double>::iterator it = lenth.begin(); it != lenth.end(); ++it)
	{
		sum += *it;
	}
	double mean = sum / lenth.size();
	cout << "Mean of Rice Lenth��" << mean << "\n";

	for_each(lenth.begin(), lenth.end(), [&](const double p) {accum += (p - mean)*(p - mean); });

	double dev = sqrt((accum / lenth.size() - 1));
	cout << "RSME of Rice Lenth��" << dev << "\n";

	waitKey(0);
	return 0;
}