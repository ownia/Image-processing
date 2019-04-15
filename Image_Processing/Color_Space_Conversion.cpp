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

	//判断图像是否加载成功
	if (!srcImage.data)
	{
		cout << "load failed" << endl;
		return false;
	}
	else
		cout << "load success" << endl;

	//显示原图像
	imshow("Original", srcImage);

	//RGB2GRAY
	//Mat grayImage;
	//cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);     //将图像转换为灰度图
	//namedWindow("灰度图", WINDOW_AUTOSIZE);
	//imshow("灰度图", grayImage);



	//RGB2YUV
	//Mat YUVImage;
	//cvtColor(srcImage, YUVImage, COLOR_RGB2YUV);
	//std::vector<Mat> YUVchannels;
	//split(YUVImage, YUVchannels);

	//imshow("YUV-Y", YUVchannels[0]);
	//imshow("YUV-U", YUVchannels[1]);
	//imshow("YUV-V", YUVchannels[2]);

	//U: colormap_u = np.array([[[i,255-i,0] for i in range(256)]],dtype=np.uint8)
	//V: colormap_v = np.array([[[0,255-i,i] for i in range(256)]],dtype=np.uint8)
	//Mat Y, U, V;
	//cvtColor(channels[0], Y, COLOR_GRAY2RGB);
	//cvtColor(channels[1], U, COLOR_GRAY2RGB);
	//cvtColor(channels[2], V, COLOR_GRAY2RGB);
	//imshow("Y", Y);
	//imshow("U", U);//trans
	//imshow("V", V);//trans

	//RGB2HSI
	Mat HSIImage(srcImage.rows, srcImage.cols, srcImage.type());;
	float r, g, b, h, s, i;
	for (int i = 0; i < srcImage.rows; i++)
	{
		for (int j = 0; j < srcImage.cols; j++)
		{
			b = srcImage.at<Vec3b>(i, j)[0];
			g = srcImage.at<Vec3b>(i, j)[1];
			r = srcImage.at<Vec3b>(i, j)[2];

			i = (b + g + r) / 3;

			int min_val = 0;
			min_val = std::min(r, std::min(b, g));

			s = 1 - 3 * (min_val / (b + g + r));
			if (s < 0.00001)
			{
				s = 0;
			}
			else if (s > 0.99999) {
				s = 1;
			}
			if (s != 0)
			{
				h = 0.5 * ((r - g) + (r - b)) / sqrt(((r - g)*(r - g)) + ((r - b)*(g - b)));
				h = acos(h);
				if (b <= g)
				{
					h = h;
				}
				else {
					h = ((360 * 3.14159265) / 180.0) - h;
				}
			}

			HSIImage.at<Vec3b>(i, j)[0] = (h * 180) / 3.14159265;
			HSIImage.at<Vec3b>(i, j)[1] = s * 100;
			HSIImage.at<Vec3b>(i, j)[2] = i;
		}
	}
	imshow("HSIImage", HSIImage);


	
	//std::vector<Mat> HSIchannels;
	//split(HSIImage, HSIchannels);

	//imshow("HSI-H", HSIchannels[0]);
	//imshow("HSI-S", HSIchannels[1]);
	//imshow("HSI-I", HSIchannels[2]);

	//RGB2HSV
	//Mat HSVImage;
	//cvtColor(srcImage, HSVImage, COLOR_RGB2HSV);
	//std::vector<Mat> HSVchannels;
	//split(HSVImage, HSVchannels);

	//imshow("HSV-H", HSVchannels[0]);
	//imshow("HSV-S", HSVchannels[1]);
	//imshow("HSV-V", HSVchannels[2]);
	



	waitKey(0);

	return 0;
}