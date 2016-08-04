#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Global variables
Mat src, src_gray, src_blur,src_threshold,src_contours;
int thresh = 245;
vector<vector<Point> > contours; //store as multiplearray vector of point
vector<Vec4i> hierarchy;
RNG rng(12345);

void main()
{
	src = imread("hand3.jpg", 1); //�̹����� ���ȭ�ؼ� �ҷ���
	imshow("original image", src); //���ȭ�� �����͸� �̹����� ������
	waitKey(0); //�ƹ�Ű�� �Է��ϱ� ���� â�� ������ �ʰ��ϴ� �Լ�

	cvtColor(src, src_gray, CV_BGR2GRAY); //bgr�̹����� gray scale�� ��ȯ
	//imshow("gray image", src_gray);//�̹����� gray�� �ٲ� ������
	//waitKey(0);

	//������ ���̱� ���� ��ó��
	bilateralFilter(src_gray, src_blur, 9, 75, 75, 4);
	//imshow("blur image", src_blur);
	//waitKey(0);

	//�̹��� ����ȭ
	threshold(src_blur, src_threshold, thresh, 255, THRESH_BINARY_INV);

	//ħ��
	erode(src_threshold, src_threshold, Mat(3, 3, CV_8U, Scalar(1)), Point(-1, -1), 2);
	imshow("threshold image", src_threshold);
	waitKey(0);

	//findcontours function error??
//	findContours(src_threshold, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Approximate contours to polygons + get bounding rects and circles
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);
		boundRect[i] = boundingRect(Mat(contours_poly[i]));
	}


	/// Draw polygonal contour + bonding rects + circles
	Mat drawing = Mat::zeros(src_threshold.size(), CV_8UC3);
	for (int i = 0; i< contours.size(); i++)
	{
		Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
	}

	/// Show in a window
	namedWindow("Contours", CV_WINDOW_AUTOSIZE);
	imshow("Contours", drawing);
	waitKey(0);
}