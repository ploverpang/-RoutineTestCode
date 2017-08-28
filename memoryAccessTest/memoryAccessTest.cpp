#include "stdio.h"
#include <string>


#include <opencv2/opencv.hpp>

const int looptime = 1000;

int testAccessTime(cv::Mat &img)
{
    int loopcnt =0;
    int64_t start_time = cv::getCPUTickCount();
    while(loopcnt<looptime)
    {
        for(int y=1; y<img.rows+1;y++)
        {
            uchar *p = img.ptr(y)-1;
            for(int x=img.cols-1; x>=0; x--, p--)
                (*p)++;
        }
        loopcnt++;
    }
    double spendtime = ((double)(cv::getCPUTickCount()-start_time)/cv::getTickFrequency())/1000;
    printf("point -- speedtime is %d ms\n", spendtime);


    loopcnt = 0;
    start_time = cv::getCPUTickCount();
    while(loopcnt<looptime)
    {
        for(int y=0; y<img.rows;y++)
        {
            uchar *p = img.ptr(y);
            for(int x=0; x<img.cols; x++, p++)
                (*p)++;
        }
        loopcnt++;
    }
    spendtime = ((double)(cv::getCPUTickCount()-start_time)/cv::getTickFrequency())/1000;
    printf("point ++ speedtime is %d ms\n", spendtime);

}

int main(int argc, char* argv[] )
{
    if(not argc==2)
    {
        printf("please input img path]\n");
        return -1;
    }

    std::string imgPath = std::string(argv[1]);
    cv::Mat img = cv::imread(imgPath);
    cv::imshow("img", img);
    cv::waitKey();


    testAccessTime(img);

    return 0;

}
