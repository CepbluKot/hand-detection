#include "modules/camera.h"
#include "modules/handsDetector.h"
#include "src/algorithms/algorithms.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>


// ##### config ######
int sensetivity = 100; //чувствительность
std::string algorithmName = "FrameDifference"; // выбор алгоритма отделения объектов от фона
// ##################


int main(int argc, char **argv)
{
    cv::Mat src, src_backSub, output;
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(13, 13), cv::Point(-1, -1));


    USBCamera *cam1 = new USBCamera(0);
    cameraAbstraction cameraClient(cam1);
    cameraClient.open();


    testHandsDetection *contoursDetection = new testHandsDetection(sensetivity);
    handsDetectionAbstraction contoursDetectionClient(contoursDetection);



    auto bgs = BGS_Factory::Instance()->Create(algorithmName);

    while (1)
    {
        src = cameraClient.getFrame();
        output = src;
        

        cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
        cv::equalizeHist(src, src);
        cv::cvtColor(src, src, cv::COLOR_GRAY2BGR);
        cv::GaussianBlur(src, src, cv::Size(13,13), 0,0);

        
        src_backSub = bgs->apply(src);
        cv::erode(src_backSub, src_backSub, kernel, cv::Point(-1,-1), 1);

        contoursDetectionClient.detect(src_backSub, output);

        cv::imshow("output", output);
        cv::imshow("detect", src_backSub);
        cv::waitKey(1);
    }
    return 0;
}
