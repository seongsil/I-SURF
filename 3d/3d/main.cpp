#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Global variables
Mat src, src_gray, src_blur,src_threshold,src_contours;


void main()
{
	src = imread("hand3.jpg", 1); //�̹����� ���ȭ�ؼ� �ҷ���
	imshow("original image", src); //���ȭ�� �����͸� �̹����� ������
	waitKey(0); //�ƹ�Ű�� �Է��ϱ� ���� â�� ������ �ʰ��ϴ� �Լ�

	cvtColor(src, src_gray, CV_BGR2GRAY); //bgr�̹����� gray scale�� ��ȯ
	imshow("gray image", src_gray);//�̹����� gray�� �ٲ� ������
	waitKey(0);

	//������ ���̱� ���� ��ó��
	bilateralFilter(src_gray, src_blur, 9, 75, 75, 4);
	imshow("blur image", src_blur);
	waitKey(0);

	//�̹��� ����ȭ
	threshold(src_blur, src_threshold, 245, 255, THRESH_BINARY_INV);
	imshow("threshold image", src_threshold);
	waitKey(0);

}