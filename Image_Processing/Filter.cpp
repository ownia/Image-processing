#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	//select srcImageFile
	string file = "ExperimentImage/NoisePattern/bmp/Image45.bmp";

	//read the srcImage and check it
	Mat srcImage = imread(file);
	if (srcImage.empty())
	{
		cout << "Could not open or find the image" << endl;
		cin.get();
		return -1;
	}
	imshow("Original", srcImage);

	//https://docs.opencv.org/4.1.0/d4/d86/group__imgproc__filter.html

	Mat MedianImage;
	medianBlur(srcImage, MedianImage, 3);
	imshow("MedianImage", MedianImage);

	Mat BlurImage;
	blur(srcImage, BlurImage, Size(3, 3), Point(-1, -1));//anchor = Point(-1,-1), is central
	imshow("BlurImage", BlurImage);

	Mat GaussianImage;
	GaussianBlur(srcImage, GaussianImage, Size(5, 5), 0, 0);
	imshow("GaussianImage", GaussianImage);

	Mat SobelImage;
	Mat x1, y1, s_x1, s_y1;
	Sobel(srcImage, x1, CV_16S, 1, 0, 3);
	convertScaleAbs(x1, s_x1);
	Sobel(srcImage, y1, CV_16S, 0, 1, 3);
	convertScaleAbs(y1, s_y1);
	addWeighted(s_x1, 0.5, s_y1, 0.5, 0, SobelImage);
	//imshow("SobelImage", SobelImage);

	Mat PrewittImage;
	Mat Kernelx, Kernely;
	Kernelx = (Mat_<double>(3, 3) << 1, 1, 1, 0, 0, 0, -1, -1, -1);
	Kernely = (Mat_<double>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
	Mat x2, y2, s_x2, s_y2;
	filter2D(srcImage, x2, CV_16S, Kernelx, Point(-1, -1));
	convertScaleAbs(x2, s_x2);
	filter2D(srcImage, y2, CV_16S, Kernely, Point(-1, -1));
	convertScaleAbs(y2, s_y2);
	addWeighted(s_x2, 0.5, s_y2, 0.5, 0, PrewittImage);
	//imshow("PrewittImage", PrewittImage);

	//g[i, j] = {{f[i , j] - f[i + 1, j + 1]} ^ 2 + {f[i + 1, j] - f[i, j + 1] ^2}} ^ d0.5
	Mat RobertsImage;
	Mat RobertsGray;
	cvtColor(srcImage, RobertsGray, COLOR_BGR2GRAY);
	Mat dstImage = RobertsGray.clone();
	int nRows = dstImage.rows;
	int nCols = dstImage.cols;
	for (int i = 0; i < nRows - 1; i++)
	{
		for (int j = 0; j < nCols - 1; j++)
		{
			int t1 = (RobertsGray.at<uchar>(i, j) - RobertsGray.at<uchar>(i + 1, j + 1)) * (RobertsGray.at<uchar>(i, j) - RobertsGray.at<uchar>(i + 1, j + 1));
			int t2 = (RobertsGray.at<uchar>(i + 1, j) - RobertsGray.at<uchar>(i, j + 1)) * (RobertsGray.at<uchar>(i + 1, j) - RobertsGray.at<uchar>(i, j + 1));
			dstImage.at<uchar>(i, j) = (uchar)sqrt(t1 + t2);
		}
	}
	convertScaleAbs(dstImage, RobertsImage);
	//imshow("RobertsImage", RobertsImage);

	//https://docs.opencv.org/4.1.0/d6/ddf/samples_2cpp_2laplace_8cpp-example.html
	Mat LaplaceImage;
	Mat Laplace;
	Laplacian(GaussianImage, Laplace, CV_16S, 3);//InputArray use GaussianImage
	convertScaleAbs(Laplace, LaplaceImage, (5 + 1)*0.25);//(GaussianImage.sigma + 1)*0.25
	//imshow("LaplaceImage", LaplaceImage);

	Mat B_Sobel, B_Prewitt, B_Roberts, B_Laplace;
	threshold(SobelImage, B_Sobel, 110, 255, 0);
	threshold(PrewittImage, B_Prewitt, 90, 255, 0);
	threshold(RobertsImage, B_Roberts, 70, 255, 0);
	threshold(LaplaceImage, B_Laplace, 90, 255, 0);

	imshow("B_Sobel", B_Sobel);
	imshow("B_Prewitt", B_Prewitt);
	imshow("B_Roberts", B_Roberts);
	imshow("B_Laplace", B_Laplace);

	waitKey(0);

	return 0;
}