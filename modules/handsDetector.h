#include <opencv2/opencv.hpp>
#include <vector>

class handsDetectionInterface // интерфейс для всех типов определения контуров
{
public:
    virtual void detect(cv::Mat inputBinaryImage, cv::Mat outputImage){}; // возвращает обнаруженные контуры

protected:
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
};


class handsDetectionAbstraction : public handsDetectionInterface // абстракция для всех типов определения контуров
{
public:
    handsDetectionAbstraction(handsDetectionInterface *inputContoursDetectionInterface)
    {
        selectedContoursDetectionInterface = inputContoursDetectionInterface;
    };

    void detect(cv::Mat inputBinaryImage, cv::Mat outputImage)
    {
        selectedContoursDetectionInterface->detect(inputBinaryImage, outputImage);
    };

private:
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    handsDetectionInterface *selectedContoursDetectionInterface;
};


class testHandsDetection : public handsDetectionInterface
{
public:
    testHandsDetection(int inputSensetivity)
    {
        sensetivity = inputSensetivity;
    };

    void detect(cv::Mat inputBinaryImage, cv::Mat outputImage)
    {

        cv::findContours(inputBinaryImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
        for (size_t i = 0; i < contours.size(); i++)
        {
            int area = sensetivity;
            if (contourArea(contours[i]) > area)
            {
                cv::Scalar color = cv::Scalar(255, 255, 255, 0);
                drawContours(outputImage, contours, (int)i, color, 2, cv::LINE_8, hierarchy, 0);
                // int p = arcLength(contours[i], 1);
                // approxPolyDP(contours[i], contours[i], 0.03*p, 1);

                std::cout<<contourArea(contours[i])<<std::endl;
            }
        }
    };

private:
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    int sensetivity = 0;
};
