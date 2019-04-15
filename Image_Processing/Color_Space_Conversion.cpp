#include <iostream>

#include <opencv2/imgproc/types_c.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

int main()
{
	Mat srcImage = imread("airplane.tiff");

	//�ж�ͼ���Ƿ���سɹ�
	if (!srcImage.data)
	{
		cout << "load failed" << endl;
		return false;
	}
	else
		cout << "load success" << endl << endl;

	//��ʾԭͼ��
	namedWindow("ԭͼ��", WINDOW_AUTOSIZE);
	imshow("ԭͼ��", srcImage);

	//RGB2GRAY
	//Mat grayImage;
	//cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);     //��ͼ��ת��Ϊ�Ҷ�ͼ
	//namedWindow("�Ҷ�ͼ", WINDOW_AUTOSIZE);
	//imshow("�Ҷ�ͼ", grayImage);

	//RGB2HSV
	//Mat HSVImage;
	//cvtColor(srcImage, HSVImage, COLOR_RGB2HSV);
	//namedWindow("HSV", WINDOW_AUTOSIZE);
	//imshow("HSV", HSVImage);

	//RGB2YUV
	Mat YUVImage;
	cvtColor(srcImage, YUVImage, COLOR_RGB2YUV);
	//cvtColor(srcImage, YUVImage, COLOR_BGR2YUV);

	std::vector<Mat> channels;
	split(YUVImage, channels);

	imshow("gY", channels[0]);
	imshow("gU", channels[1]);
	imshow("gV", channels[2]);

	//U: colormap_u = np.array([[[i,255-i,0] for i in range(256)]],dtype=np.uint8)
	//V: colormap_v = np.array([[[0,255-i,i] for i in range(256)]],dtype=np.uint8)
	//Mat Y, U, V;
	//cvtColor(channels[0], Y, COLOR_GRAY2RGB);
	//cvtColor(channels[1], U, COLOR_GRAY2RGB);
	//cvtColor(channels[2], V, COLOR_GRAY2RGB);
	//imshow("Y", Y);
	//imshow("U", U);//trans
	//imshow("V", V);//trans

	waitKey(0);

	return 0;
}