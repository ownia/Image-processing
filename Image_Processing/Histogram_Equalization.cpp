#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/imgproc_c.h>

using namespace std;
using namespace cv;

/*https://docs.opencv.org/4.1.0/d6/dc7/group__imgproc__hist.html
 *void cv::calcHist(const Mat * 			images,
 *					int 					nimages,
 *					const int * 			channels,
 *					InputArray 				mask,
 *					OutputArray 			hist,
 *					int 					dims,
 *					const int * 			histSize,
 *					const float ** 			ranges,
 *					bool 					uniform = true,
 *					bool 					accumulate = false
 *)
 */

class Histogram
{
private:
	int histSize = 256;
	int channels[2] = { 0, 1 };
	float range[2] = { 0, 256 };
	const float* ranges[1] = { range };

public:
	Mat get_histogram(const Mat &srcImage)
	{
		MatND hist;
		calcHist(&srcImage, 1, channels, Mat(), hist, 1, &histSize, ranges, true, false);

		//https://docs.opencv.org/4.1.0/dc/d84/group__core__basic.html
		//void 	cv::minMaxLoc (const SparseMat &a, double *minVal, double *maxVal, int *minIdx=0, int *maxIdx=0)
		double max = 0.0f;
		double min = 0.0f;
		minMaxLoc(hist, &min, &max);

		Mat histImg(histSize, histSize, CV_8U, Scalar(255));
		int hpt = static_cast<int>(0.9 * histSize);
		for (int h = 0; h < histSize; h++)
		{
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int>(binVal * hpt / max);
			line(histImg, Point(h, histSize), Point(h, histSize - intensity), Scalar::all(0));
		}
		return histImg;
	}
};

int main()
{
	//select srcImageFile
	string file = "ExperimentImage/Grayscale/bmp/peppers.bmp";

	//read the srcImage and check it
	Mat srcImage = imread(file);
	if (srcImage.empty())
	{
		cout << "Could not open or find the image" << endl;
		cin.get();
		return -1;
	}
	imshow("Original", srcImage);

	//equalize the histogram
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	Mat equalizationImage;
	equalizeHist(srcImage, equalizationImage);
	imshow("Euqlization", equalizationImage);

	//histogram image
	Histogram hist1, hist2;
	Mat histogram1 = hist1.get_histogram(srcImage);
	imshow("hist1", histogram1);
	Mat histogram2 = hist2.get_histogram(equalizationImage);
	imshow("hist2", histogram2);

	waitKey(0);

	return 0;
}