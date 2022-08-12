/* 
    create interface for cameras 
    create interpretation for cameras (choose which cam to use, maybe multiple cameras)
    create camera class with details
*/

// to-do add remote camera 


#include "opencv4/opencv2/opencv.hpp"
#include <string>


class cameraInterface // просто интерфейс для всех типов камер
{
    public:
        virtual void open() { } // открытие камеры
        virtual cv::Mat getFrame() { } // получение кадра 
};


class cameraAbstraction : public cameraInterface // через эту абстракцию взаимодействуем со всеми камерами
{
    public:
        cameraAbstraction(cameraInterface* input_camera_interface) // просто задаем предпочтительный интерфейс камеры
        {
            selected_camera = input_camera_interface;
        }

        void open() 
        { 
            return selected_camera->open();
        }

        cv::Mat getFrame()
        {
            return selected_camera->getFrame();
        }

    private:
        cameraInterface* selected_camera;
};


class USBCamera : public cameraInterface // детади взаимодейсвия с usb камерой
{
    public:
        USBCamera(int input_camera_id = 0)
        {
            selected_camera_id = input_camera_id;
        }
        
        void open() 
        {
            cameraObject.open(selected_camera_id);
            if (!cameraObject.isOpened())
                std::cerr << "ERROR! Unable to open camera\n";
            
        }

        cv::Mat getFrame()
        {
            if (!cameraObject.isOpened())
                std::cerr << "ERROR! Unable to open camera\n";
            cv::Mat frame;
            cameraObject >> frame;
            return frame;
        }
        
    private:
        int selected_camera_id;
        cv::VideoCapture cameraObject;
};


class IPCamera : public cameraInterface
{
    public:
        IPCamera(std::string address, std::string username, std::string password) // address = ip + port
        {

            // string videoStreamAddress = "rtsp://" + username + ":" + password + "@" + address + "/h264_ulaw.sdp";
            // cout << videoStreamAddress;
        }

        void open()
        {     
            cameraObject.open(videoStreamAddress);

            if (!cameraObject.isOpened())
                std::cerr << "ERROR! Unable to open camera\n";
            
        }

        cv::Mat getFrame()
        {
            cv::Mat frame;
            if (!cameraObject.isOpened())
                std::cerr << "ERROR! Unable to open camera\n";

            cameraObject >> frame;
            return frame;
        }


    private:
        std::string videoStreamAddress = "rtsp://test:test@192.168.100.5:8080/h264_ulaw.sdp";
        cv::VideoCapture cameraObject;
};
