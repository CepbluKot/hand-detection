#include "modules/camera.h"
#include "modules/handsDetector.h"
#include "src/algorithms/algorithms.h"
#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>


std::string algorithmName = "FrameDifference"; // выбор алгоритма отделения объектов от фона


int main(int argc, char **argv)
{
    USBCamera *cam1 = new USBCamera(0);
    cameraAbstraction cameraClient(cam1);
    cameraClient.open();


    testHandsDetection *contoursDetection = new testHandsDetection();
    handsDetectionAbstraction contoursDetectionClient(contoursDetection);



    cv::Mat src, src_bilateral, src_bilateral_backSub, output;
    auto bgs = BGS_Factory::Instance()->Create(algorithmName);

    while (1)
    {
        src = cameraClient.getFrame();
        output = src;

        bilateralFilter(src, src_bilateral, 9, 95, 95);
        // cvtColor(src, src_bilateral, COLOR_BGR2GRAY);
       src_bilateral_backSub = bgs->apply(src_bilateral);

       contoursDetectionClient.detect(src_bilateral_backSub, output);

        imshow("outp", output);
        cv::waitKey(1);
    }
    return 0;
}
