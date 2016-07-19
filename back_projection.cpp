#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;

/// ȫ�ֱ���
Mat src; Mat hsv; Mat hue;
int bins = 25;

/// ��������
void Hist_and_Backproj(int, void*);

/** @���� main */
int main(int argc, char** argv)
{
	/// ��ȡͼ��
	src = imread(argv[1], 1);
	/// ת���� HSV �ռ�
	cvtColor(src, hsv, CV_BGR2HSV);

	/// ���� Hue ͨ��
	hue.create(hsv.size(), hsv.depth());
	int ch[] = { 0, 0 };
	mixChannels(&hsv, 1, &hue, 1, ch, 1);

	/// ���� Trackbar ������bin����Ŀ
	char* window_image = "Source image";
	namedWindow(window_image, CV_WINDOW_AUTOSIZE);
	createTrackbar("* Hue  bins: ", window_image, &bins, 180, Hist_and_Backproj);
	Hist_and_Backproj(0, 0);

	/// ��ʵͼ��
	imshow(window_image, src);

	/// �ȴ��û���Ӧ
	waitKey(0);
	return 0;
}


/**
* @���� Hist_and_Backproj
* @��飺Trackbar�¼��Ļص�����
*/
void Hist_and_Backproj(int, void*)
{
	MatND hist;
	int histSize = MAX(bins, 2);
	float hue_range[] = { 0, 180 };
	const float* ranges = { hue_range };

	/// ����ֱ��ͼ����һ��
	calcHist(&hue, 1, 0, Mat(), hist, 1, &histSize, &ranges, true, false);
	normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());

	/// ���㷴��ͶӰ
	MatND backproj;
	calcBackProject(&hue, 1, 0, hist, backproj, &ranges, 1, true);

	/// ��ʾ����ͶӰ
	imshow("BackProj", backproj);

	/// ��ʾֱ��ͼ
	int w = 400; int h = 400;
	int bin_w = cvRound((double)w / histSize);
	Mat histImg = Mat::zeros(w, h, CV_8UC3);

	for (int i = 0; i < bins; i++)
	{
		rectangle(histImg, Point(i*bin_w, h), Point((i + 1)*bin_w, h - cvRound(hist.at<float>(i)*h / 255.0)), Scalar(0, 0, 255), -1);
	}

	imshow("Histogram", histImg);
}