#include <cv.h>
#include <highgui.h>
using namespace std;
int main()
{
	IplImage * test;
	test = cvLoadImage("E:\\opencv\\pic\\001.jpg");//Í¼Æ¬Â·¾¶
	cvNamedWindow("test_demo", 1);
	cvShowImage("test_demo", test);
	cvWaitKey(0);
	cvDestroyWindow("test_demo");
	cvReleaseImage(&test);
	return 0;
}