#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Global variables
Mat src, src_gray, src_blur,src_threshold,src_contours;


void main()
{
	src = imread("hand3.jpg", 1); //이미지를 행렬화해서 불러옴
	imshow("original image", src); //행렬화된 데이터를 이미지로 보여줌
	waitKey(0); //아무키나 입력하기 전에 창이 닫히지 않게하는 함수

	cvtColor(src, src_gray, CV_BGR2GRAY); //bgr이미지를 gray scale로 변환
	imshow("gray image", src_gray);//이미지를 gray로 바꿔 보여줌
	waitKey(0);

	//잡음을 줄이기 위한 블러처리
	bilateralFilter(src_gray, src_blur, 9, 75, 75, 4);
	imshow("blur image", src_blur);
	waitKey(0);

	//이미지 이진화
	threshold(src_blur, src_threshold, 245, 255, THRESH_BINARY_INV);
	imshow("threshold image", src_threshold);
	waitKey(0);

}