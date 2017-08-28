#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

void showGray(string &grayImgName, const int nRow, const int nCol)
{
	ifstream ifs;
	ifs.open(grayImgName.c_str());
	int nPixel = nRow*nCol;
	uchar *data = (uchar*)malloc(sizeof(uchar)*nPixel);
	uchar *p = data;

	for(int i=0; i<nPixel; i++)
	{
		int nTmp;
		ifs >> nTmp;
		(*p) = (uchar)(nTmp);
		p++;
	}
	ifs.close();

	cv::Mat grayImg(nRow, nCol, CV_8U, data);
	cv::imshow("grayImg", grayImg);
	cv::waitKey();
	free(data);
}

void show420(string &yuv420ImgName, const int nRow, const int nCol)
{
	ifstream ifs;
	ifs.open(yuv420ImgName.c_str());
	int nPixel = nRow*nCol;
	uchar *data = (uchar*)malloc(sizeof(uchar)*nPixel);
	uchar *p = data;

	for(int i=0; i<nPixel; i++)
	{
		int nTmp;
		ifs >> nTmp;
		nTmp = nTmp >> 4;
		(*p) = (uchar)(nTmp);
		p++;
	}
	ifs.close();

	cv::Mat yuv420Img(nRow, nCol, CV_8U, data);
	cv::imshow("yuv420Img", yuv420Img);
	cv::waitKey();
	free(data);
}
//
//int main()
//{
//	string grayImgName("/home/pangbo/code/IntroductionToAlgorithms/build/28_Matrix/txt/pre_L_gray.txt");
//	showGray(grayImgName, 600, 1280);
//
//	string yuvImgName("/home/pangbo/code/IntroductionToAlgorithms/build/28_Matrix/txt/rec_R_yuv420.txt");
//	show420(yuvImgName,600, 1280);
//}
